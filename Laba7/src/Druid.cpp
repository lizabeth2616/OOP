#include "../include/Druid.hpp"


Druid::Druid(const std::string& name, int x, int y)
    : NPC(name, "Druid", x, y, 10, 10) {}

void Druid::fight(NPC* opponent, std::vector<std::shared_ptr<Observer>>& observers) {
    if (opponent->get_type() == "Dragon") {
        std::string event = name + " kills " + opponent->get_name();
        for (auto& observer : observers) {
            observer->update(event);
        }
    }
}