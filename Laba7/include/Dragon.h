#pragma once
#include "./NPC.hpp"

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y);
    void fight(NPC* opponent, std::vector<std::shared_ptr<Observer>>& observers) override;
};