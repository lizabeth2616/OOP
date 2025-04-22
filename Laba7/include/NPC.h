#pragma once
#include "./Observers.hpp"
#include <memory>
#include <string>
#include <cmath>
#include <vector>

class NPC {
public:
    std::string name;
    int x, y;
    std::string type;
    int move_dist;
    int kill_dist;

    NPC(
        const std::string& name, 
        const std::string& type, 
        int x, 
        int y, 
        int move_dist, 
        int kill_dist
    );

    virtual void fight(NPC* opponent, std::vector<std::shared_ptr<Observer>>& observers) = 0;
    double distance_to(NPC* opponent);
    virtual void print() const;
    virtual std::string get_name() const;
    virtual std::string get_type() const;
    virtual std::string serialize() const;
    static std::shared_ptr<NPC> deserialize(const std::string& data);
    virtual ~NPC() = default;
};