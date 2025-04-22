#include "./include/NPCFactory.hpp"
#include "./include/NPC.hpp"
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <random>
#include <atomic>
#include <chrono>
#include <vector>
#include <mutex>

namespace GameLogic {

namespace Globals {
    std::vector<std::shared_ptr<NPC>> npc_list;
    std::shared_mutex npc_access;
    std::mutex console_output;
    std::atomic<bool> is_running = true;

    constexpr int MAP_WIDTH = 500;
    constexpr int MAP_HEIGHT = 500;
    constexpr int GAME_DURATION = 30;
}

class RandomEngine {
public:
    RandomEngine() : rng(std::random_device{}()) {}

    int roll_die() const {
        return std::uniform_int_distribution<int>(1, 6)(rng);
    }

    int random_between(int min, int max) const {
        return std::uniform_int_distribution<int>(min, max)(rng);
    }

private:
    mutable std::mt19937 rng;
};

RandomEngine randomGen;

void processNPCMovement() {
    while (Globals::is_running) {
        std::unique_lock lock(Globals::npc_access);
        for (auto& npc : Globals::npc_list) {
            if (npc->serialize().find("dead") == std::string::npos) {
                auto dx = randomGen.random_between(-npc->move_dist, npc->move_dist);
                auto dy = randomGen.random_between(-npc->move_dist, npc->move_dist);

                npc->x = std::clamp(npc->x + dx, 0, Globals::MAP_WIDTH - 1);
                npc->y = std::clamp(npc->y + dy, 0, Globals::MAP_HEIGHT - 1);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void processNPCCombat() {
    while (Globals::is_running) {
        std::unique_lock lock(Globals::npc_access);
        for (size_t i = 0; i < Globals::npc_list.size(); ++i) {
            if (Globals::npc_list[i]->serialize().find("dead") != std::string::npos) continue;

            for (size_t j = i + 1; j < Globals::npc_list.size(); ++j) {
                if (Globals::npc_list[j]->serialize().find("dead") != std::string::npos) continue;

                double distance = Globals::npc_list[i]->distance_to(Globals::npc_list[j].get());
                if (distance <= Globals::npc_list[i]->kill_dist || distance <= Globals::npc_list[j]->kill_dist) {
                    int attack_roll = randomGen.roll_die();
                    int defense_roll = randomGen.roll_die();
                    if (attack_roll > defense_roll) {
                        Globals::npc_list[j]->type += "_dead";
                        std::lock_guard<std::mutex> lock(Globals::console_output);
                        std::cout << Globals::npc_list[i]->get_name() << " убил " << Globals::npc_list[j]->get_name() << "\n";
                    } else if (defense_roll > attack_roll) {
                        Globals::npc_list[i]->type += "_dead";
                        std::lock_guard<std::mutex> lock(Globals::console_output);
                        std::cout << Globals::npc_list[j]->get_name() << " убил " << Globals::npc_list[i]->get_name() << "\n";
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void drawGameMap() {
    while (Globals::is_running) {
        std::vector<std::vector<char>> game_map(Globals::MAP_HEIGHT, std::vector<char>(Globals::MAP_WIDTH, '.'));
        {
            std::shared_lock lock(Globals::npc_access);
            for (const auto& npc : Globals::npc_list) {
                if (npc->serialize().find("dead") == std::string::npos) {
                    game_map[npc->y][npc->x] = npc->get_name()[0];
                }
            }
        }

        {
            std::lock_guard<std::mutex> lock(Globals::console_output);
            std::cout << "\033[2J\033[H";  // очистка экрана
            for (const auto& row : game_map) {
                for (char cell : row) std::cout << cell;
                std::cout << '\n';
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void spawnNPCs() {
    for (int i = 0; i < 50; ++i) {
        int x = randomGen.random_between(0, Globals::MAP_WIDTH - 1);
        int y = randomGen.random_between(0, Globals::MAP_HEIGHT - 1);

        std::string npc_type = (i % 3 == 0) ? "Dragon" :
                                (i % 3 == 1) ? "Druid" : "Elf";

        Globals::npc_list.push_back(NPCFactory::createNPC(npc_type, npc_type + std::to_string(i), x, y));
    }
}

}

int main() {
    GameLogic::spawnNPCs();

    auto npcMover = std::thread(GameLogic::processNPCMovement);
    auto npcCombater = std::thread(GameLogic::processNPCCombat);
    auto mapDrawer = std::thread(GameLogic::drawGameMap);

    std::this_thread::sleep_for(std::chrono::seconds(GameLogic::Globals::GAME_DURATION));
    GameLogic::Globals::is_running = false;

    npcMover.join();
    npcCombater.join();
    mapDrawer.join();

    std::lock_guard<std::mutex> lock(GameLogic::Globals::console_output);
    std::cout << "Игра завершена. NPC, которые выжили:\n";
    {
        std::shared_lock lock(GameLogic::Globals::npc_access);
        for (const auto& npc : GameLogic::Globals::npc_list) {
            if (npc->serialize().find("dead") == std::string::npos) {
                std::cout << npc->get_name() << " (" << npc->x << ", " << npc->y << ")\n";
            }
        }
    }

    return 0;
}