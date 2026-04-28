#include <vector>

#include "entities.hpp"

int main(){

  struct entity_sheet placeholder = {0, 0, 0};

  Entity* enemy = new Enemy("Nefarious Enemy", placeholder);
  Entity* pc = new Player("Good Guy", placeholder);

  std::vector<Entity*> entities = {enemy, pc};

  for(Entity* entity : entities){

    std::cout << *entity << std::endl;

  }

}
