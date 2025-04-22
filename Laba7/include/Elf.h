#pragma once
#include "NPC.hpp"

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y);
    void fight(NPC* opponent, std::vector<std::shared_ptr<Observer>>& observers) override;
};