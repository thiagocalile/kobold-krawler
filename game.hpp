#include <vector>
#include <format>
#include "entities.hpp"
#include "combat.hpp"

#ifndef GAME_H
#define GAME_H

enum game_state {
  COMBAT,
  REST,
  GOOD_ENDING,
  BAD_ENDING,
};

class Game {

private:
  game_state current_state = COMBAT;
  Player* player;
  std::vector<Enemy*> dungeon;
  int current_room {};

public:

  Game(Player* p, std::vector<Enemy*> d) : dungeon(d), player(p) {};
  
  Combat* start_combat(){
    current_state = COMBAT;
    Combat* combat = new Combat(player, dungeon[current_room]);
    std::cout << std::format("{} está contra {}.", \
			     player->get_name(), dungeon[current_room]->get_name())
	      << std::endl;
    return combat;
  };

  ~Game() {

    for(Enemy* e : dungeon) {delete e;};
    delete player;

  };
  
  void end_combat(){
    if(player->get_current_hp() > 0){
      if(current_room == dungeon.size() - 1){
	current_state = GOOD_ENDING;
      } else {
	current_state = REST;
      }
    } else {
      current_state = BAD_ENDING;
    };
  };

  void end_rest(){

    current_room++;
    current_state = COMBAT;

  };
  
  game_state get_current_state(){return current_state;};
  Player* get_player(){return player;};
  Enemy* get_current_enemy(){return dungeon[current_room];};

};



#endif
