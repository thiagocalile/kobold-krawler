#include <iostream>
#include <string>

#ifndef ENTITIES_HPP
#define ENTITIES_HPP

struct entity_sheet {

  int hitpoints{};
  int defense {};
  int speed {};
  
};

class Entity {

private:
  struct entity_sheet sheet;
  std::string name;

public:
  Entity(std::string n, struct entity_sheet init_sheet) :
    name(n), sheet(init_sheet) {};

  friend std::ostream& operator<<(std::ostream &os, const Entity &e){

    os << "+-----------+" << std::endl;
    os << "Name: " << e.name << std::endl;
    os << "HP: " << e.sheet.hitpoints << std::endl;
    os << "Defense: " << e.sheet.defense << std::endl;
    os << "Speed: " << e.sheet.speed << std::endl;
    os << "+-----------+" << std::endl;
    
    return os;

  } 
};

class Enemy : public Entity {

  using Entity::Entity;
  
};

class Player : public Entity {

  using Entity::Entity;

};

#endif
