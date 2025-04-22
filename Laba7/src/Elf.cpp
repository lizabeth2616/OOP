#include "../include/Elf.hpp"

Elf::Elf(const std::string& name, int x, int y)
    : NPC(name, "Elf", x, y, 10, 50) {}

void Elf::fight(NPC* opponent, std::vector<std::shared_ptr<Observer>>& observers) {
    if (opponent->get_type() == "Druid") {
        std::string event = name + " kills " + opponent->get_name();
        for (auto& observer : observers) {
            observer->update(event);
        }
    }
}