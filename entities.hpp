#include <iostream>
#include <string>
#include <format>

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
  int current_hp {};

public:
  Entity(std::string n, struct entity_sheet init_sheet) :
    name(n), sheet(init_sheet) {
    current_hp = sheet.hitpoints;
      };

  // Ataque normal, na base da porrada
  //virtual int attack() = 0;
  
  Entity* defend(int damage){

    sheet.hitpoints = (damage > sheet.hitpoints) ? 0 : sheet.hitpoints -= damage;

    // É um jeito meio estranho, mas ela:
    // * Retorna nullptr se ninguém morreu
    // * Retorna Entity* da entidade que morreu
    
    return (sheet.hitpoints > 0) ? nullptr : this;
    
  };

  // Pode ser mágico, pode ser um super ataque, use a criatividade :D
  //virtual ability() = 0;

  int get_speed() {return sheet.speed;};

  int get_current_hp() {return current_hp;};

  std::string get_name() {return name;};
  
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

public:
  bool heal() {};

};

#endif
