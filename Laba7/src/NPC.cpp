#include "../include/NPC.hpp"
#include <iostream>
#include <sstream>
#include "../include/Dragon.hpp"
#include "../include/Druid.hpp"
#include "../include/Elf.hpp"


NPC::NPC(
    const std::string& name, 
    const std::string& type, 
    int x, 
    int y, 
    int move_dist, 
    int kill_dist
) : name(name), type(type), x(x), y(y), move_dist(move_dist), kill_dist(kill_dist) {}

double NPC::distance_to(NPC* opponent) {
    return std::sqrt(std::pow(x - opponent->x, 2) + std::pow(y - opponent->y, 2));
}

void NPC::print() const {
    std::cout << "NPC Name: " << name << ", Type: " << type << ", Position: (" << x << ", " << y << ")\n";
}

std::string NPC::get_type() const {
    return type;
}

std::string NPC::get_name() const {
    return name;
}

std::string NPC::serialize() const {
    std::ostringstream oss;
    oss << type << " " << name << " " << x << " " << y << " " << move_dist << " " << kill_dist;
    return oss.str();
}

std::shared_ptr<NPC> NPC::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string type, name;
    int x, y, move_range, kill_range;

    iss >> type >> name >> x >> y >> move_range >> kill_range;
    if (type == "Dragon") {
        return std::make_shared<Dragon>(name, x, y);
    } else if (type == "Druid") {   
        return std::make_shared<Druid>(name, x, y);
    } else if (type == "Elf") {
        return std::make_shared<Elf>(name, x, y);
    } else {
        return nullptr;
    }
}