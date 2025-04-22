#pragma once

#include <memory>
#include <string>
#include "./NPC.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y);
};

void save_npc_to_file(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& filename);

std::vector<std::shared_ptr<NPC>> load_npc_from_file(const std::string& filename);