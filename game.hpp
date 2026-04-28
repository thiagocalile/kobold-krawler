#include <vector>

#ifndef GAME_H
#define GAME_H

enum game_state {

  START,
  COMBAT,
  REST,

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
    current_state = REST;
  };
};

#endif
