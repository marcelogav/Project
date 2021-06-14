#ifndef __FOLLOWER_AGENT__H
#define __FOLLOWER_AGENT__H 

#include "enviro.h"
#include <iostream>
#include <string>
#include <math.h>
#include <elma/elma.h>

using namespace enviro;

// Follower robots have been as a process controler. They will be activated by doing "click_agent"
// over each of them individually, and they will try to follow the position of the leader immediatelly.
// they will reduce velocity proportinally as the distance between them and leader reduces, and 
// logic will consider also that they have to be away a certain distance from themselves as well
// using the frontal sensor information.


class FollowerController : public Process, public AgentInterface {

    public:
    FollowerController() : Process(), AgentInterface(), goal_x(0), goal_y(0) {}

    void init() {
        watch("agent_click", [this](Event t) {
            if ( t.value()["id"] == id() ) {
                std::cout << "Follower n." << id() << " activated!!\n";

                watch("leader_position", [this](Event e) {
                    goal_x = e.value()["x"];
                    goal_y = e.value()["y"];
                }); 
            };
        }); 
    }

    void start() {
        goal_x = position().x;
        goal_y = position().y;
    }
       
    void update() {      
        
        distance = sqrt ( (position().x - goal_x)*(position().x - goal_x) + (position().y - goal_y)*(position().y - goal_y) );
        
        if (distance > 50 && sensor_value(0) > 30) {
            move_toward(goal_x, goal_y, distance);
            } 
                else {
                    track_velocity (0, 0);
                    }   
        
    }
    void stop() {}

    double goal_x, goal_y, distance,turn_direction;

};

class Follower : public Agent {
    public:
    Follower(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    FollowerController c;
};

DECLARE_INTERFACE(Follower)

#endif