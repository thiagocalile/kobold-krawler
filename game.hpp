#include <vector>

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
  void start_combat(){
    current_state = COMBAT;
    Combat* combat = new Combat(player, dungeon[current_room]);
  };
  
  void end_combat(){
    if(player.get_current_hp()){
      if(current_room == dungeon.size() - 1){
	current_state = GOOD_ENDING;
      } else {
	current_state = REST;
      }
    } else {
      current_state = BAD_ENDING
    };
  };

  game_state get_current_state(){return current_state};
};

#endif
