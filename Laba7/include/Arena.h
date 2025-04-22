#pragma once

#include "./NPC.hpp"

class Arena {
public:
    void startBattle(std::vector<std::shared_ptr<NPC>>& npcs, std::vector<std::shared_ptr<Observer>>& observers);
};
