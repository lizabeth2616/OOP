#include "../include/Dragon.hpp"


Dragon::Dragon(const std::string& name, int x, int y)
    : NPC(name, "Dragon", x, y, 50, 30) {}

void Dragon::fight(NPC* opponent, std::vector<std::shared_ptr<Observer>>& observers) {
    if (opponent->get_type() == "Elf") {
        std::string event = name + " kills " + opponent->get_name();
        for (auto& observer : observers) {
            observer->update(event);
        }
    }
}