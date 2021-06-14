#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H 

#include "enviro.h"
#include <iostream>
#include <string>
#include <math.h>
#include <elma/elma.h>

namespace
{

using namespace enviro;


// Robot Leader was created as a State Machine with 2 states
// Besides we also implemented a process controler for random events (clicks) we'd like to include
// Coding is working OK, but physics is not good; I tried to implement infinite loop: Robot should turn
// when found block ahead, and go back to liner movement immediate after turn finished. But I could not
// make this idea works in full. 

// Followers need to keep distance from the leader, but leader can smash them if they are in his way.

// "click_screen" will help to move leader to different positions in the screen


class MovingForward : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {}

        void during() {
            
            track_velocity(5, 0);  
            if (sensor_value(0) < 200) {
                track_velocity(3,0);
                emit(Event(Turnaround));
            } 
        }       
                
        void exit(const Event &e) {}

        std::string Turnaround, Wait;
    };

    
class Turn : public State, public AgentInterface
    {
    public:
                
        void entry(const Event &e) {}
                
        void during() {

            if (sensor_value(2) > sensor_value(1)) {
                        track_velocity(10,-10);
                        emit(Event(FinishTurn));
                        } 
                                            
            if (sensor_value(2) <= sensor_value(1)) {
                        track_velocity(10,10);
                        emit(Event(FinishTurn));
                        }           
        
        }

        void exit(const Event &e) {}
    
        std::string FinishTurn;
    };



class LeaderController : public StateMachine, public AgentInterface {

    public:
    LeaderController() : StateMachine(), AgentInterface() {

    set_initial(moving_forward);
    add_transition(Turnaround, moving_forward, turn);
    add_transition(FinishTurn, turn, moving_forward);  

    }

    MovingForward moving_forward;
    Turn turn;

    std::string Turnaround, FinishTurn, Wait;
    

};


class TargetController : public Process, public AgentInterface {

    public:
    TargetController() : Process(), AgentInterface() {}

    void init() {

        watch("screen_click", [this](Event e) {
            teleport(e.value()["x"], e.value()["y"], -angle()+3.4);
        });   
    }
    void start() {}
    void update() {
            emit(Event("leader_position", {
            {"x", position().x},
            {"y", position().y}
        }));
    }
    void stop() {}
 
    double e, x, y, dir;
};

class Leader : public Agent {
    public:
    Leader(json spec, World& world) : Agent(spec, world) {
        add_process(c);
        add_process(d);
    }
    private:
    LeaderController c;
    TargetController d;
};

DECLARE_INTERFACE(Leader);

};

#endif