#include "entities.hpp"

#ifndef COMBAT_H
#define COMBAT_H

class Combat {

private:
  Player* player;
  Enemy* enemy;
  
public:
  Combat(Player* p, Enemy* e) : player(p), enemy(e) {};

  bool run_action(Entity* first, action_type f_action,
		  Entity* second){

    bool should_stop = false;
    
    switch(f_action) {

    case ATTACK:
      if(second->defend(first->attack())) should_stop = true;
      break;
      
    case USE_ABILITY:
      if(second->defend(first->ability())) should_stop = true;
      break;
    }

    return should_stop;

  };
  
  bool run_turn(Player* p, action_type p_a, Enemy* e){

    action_type e_a = e->choose_action();
    
    // "Borbulha" se deveria parar ou não
    if(p->get_speed() > e->get_speed()){
      return run_action(p, p_a, e);
    } else {
      return run_action(e, e_a, p);
    };

  };
  
};

#endif
