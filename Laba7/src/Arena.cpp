#include "../include/Arena.hpp"
#include "../include/NPC.hpp"
#include <cmath>
#include <vector>

void Arena::startBattle(std::vector<std::shared_ptr<NPC>>& npcs, std::vector<std::shared_ptr<Observer>>& observers) {
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            NPC* npc1 = npcs[i].get();
            NPC* npc2 = npcs[j].get();

            double distance = npc1->distance_to(npc2);
            if (distance <= npc1->kill_dist || distance <= npc2->kill_dist) {
                npc1->fight(npc2, observers);
                npc2->fight(npc1, observers);
            }
        }
    }
}
