#include "entities.hpp"

#ifndef COMBAT_H
#define COMBAT_H

enum action_type = {

  ATTACK,
  HEAL,
  USE_ABILITY,

}

class Combat {

private:
  Player* player;
  Enemy* enemy;
  
public:
  Combat(Player* p, Enemy* e) : player(p), enemy(e) {};

  bool run_action(Entity* first, action_type f_action,
		  Entity* second, action_type s_action){

    bool should_stop = false;
    
    switch(f_action) {

    case ATTACK:
      if(second.defend(first.attack())) should_stop = true;
      break;
      
    case HEAL:
      first.heal();
      break;
      
    case USE_ABILITY:
      if(second.defend(first.ability())) should_stop = true;
      break;
    }

    return should_stop;

  };
  
  void run_turn(Player* p, action_type p_a, Enemy* e, action_type e_a){

    if(p.get_speed() > e.get_speed()){
      run_action(p, p_a, e, e_a);
    } else {
      run_action(e, e_a, p, p_a);
    };

  };
  
};

#endif
