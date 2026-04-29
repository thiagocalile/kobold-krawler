#include <vector>
#include <format>

#ifndef GAME_H
#define GAME_H

enum game_state {

  START,
  COMBAT,
  REST,
  GOOD_ENDING,
  BAD_ENDING,

};

class Game {

private:
  game_state current_state = START;
  Player* player;
  std::vector<Enemy*> dungeon;
  int current_room {};

public:

  Game(Player* p, std::vector<Enemy*> d) : dungeon(d), player(p) {};
  
  Combat* start_combat(){
    current_state = COMBAT;
    Combat* combat = new Combat(player, dungeon[current_room]);
    std::cout << std::format("{} está contra {}.",
			     player->get_name(), dungeon[current_room]) << std::endl;
    return combat;
  };
  
  void end_combat(){
    if(player->get_current_hp()){
      if(current_room == dungeon.size() - 1){
	current_state = GOOD_ENDING;
      } else {
	current_state = REST;
      }
    } else {
      current_state = BAD_ENDING;
    };
  };

  game_state get_current_state(){return current_state;};
  Player* get_player(){return player;};
  Enemy* get_current_enemy(){return dungeon[current_room];};

};

#endif
