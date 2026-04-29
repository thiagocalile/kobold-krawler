#include <iostream>
#include <string>
#include <format>
#include <random>

#include "combat.hpp"

#ifndef ENTITIES_HPP
#define ENTITIES_HPP

/* Vamos fazer ao estilo D&D: 10 é médio
 *
 *
 *
 *
 */

struct entity_sheet {

  int hitpoints{};
  int strength {};
  int defense {};
  int speed {};
  
};

class Entity {

protected:
  struct entity_sheet sheet;
  std::string name;
  int current_hp {};
  // https://en.cppreference.com/cpp/numeric/random/uniform_int_distribution
  std::random_device random_device;
  std::mt19937 gen{random_device()};
    
public:
  Entity(std::string n, struct entity_sheet init_sheet) :
    name(n), sheet(init_sheet) {
    current_hp = sheet.hitpoints;
    };

  // Ataque normal, na base da porrada
  int attack(){

    int damage {};
    std::uniform_int_distribution<> distribution(0, strength + 2);

    if(damage == 0){
      std::cout <<
	std::format("{} errou o ataque!", name)
		<< std::endl;
    } else if(damage > 0 && damage <= strength) {
      std::cout <<
	std::format("{} atacou!", name)
		<< std::endl;
    } else {
      std::cout << std::format("{} fez um ataque crítico!", name) << std::endl;
    }

    return damage;
  };
  
  Entity* defend(int damage){

    int defended_damage = damage - sheet.defense;

    if(defended_damage){
    std::cout <<
      std::format("{} defendeu {} do dano infligido!", name, sheet.defense)
	      << std::endl;
    } else {
      std::cout <<
	std::format("{} defendeu todo o dano infligido!", name)
		<< std::endl;
    };
    
    current_hp = (defended_damage > current_hp) ? 0 : current_hp -= defended_damage;

    // É um jeito meio estranho, mas ela:
    // * Retorna nullptr se ninguém morreu
    // * Retorna Entity* da entidade que morreu
    
    return (current_hp > 0) ? nullptr : this;
    
  };

  // Pode ser mágico, pode ser um super ataque, use a criatividade :D
  virtual int ability() = 0;

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

public:
  action_type choose_action(){

    std::uniform_int_distribution<> distribution(0,1);

    if(distribution(gen)) {return ATTACK;} else {return USE_ABILITY;};

  }
  
};

class Player : public Entity {

  using Entity::Entity;

  int level {};

public:
  bool heal() {

    int healing_amount {};

    std::uniform_int_distribution<> distribution(2, sheet.hitpoints);

    if(current_hp == sheet.hitpoints){
      std::cout <<
	std::format("Nada a curar. HP: {}, que é o máximo de {}", current_hp, name)
		<< std::endl;
      return false;
    } else {

      healing_amount = distribution(gen);

      if(current_hp + healing_amount > sheet.hitpoints){
	healing_amount -= sheet.hitpoints;
      };

      current_hp += healing_amount;

      std::cout <<
	std::format("{} curou {} de {} HP máximo", name, healing_amount, sheet.hitpoints)
		<< std::endl;
      
      return true;
    }
    
  };

  void level_up(){
    level++;
    sheet.hitpoints++;
    sheet.strength++;    
  };

};

class Vermin : public Enemy {

private:
  std::string ability_name;
  
public:
  Vermin(std::string n, std::string a) :
    Enemy(n, {}), ability_name(a) {

    sheet.hitpoints = 10;
    sheet.strength = 6;
    sheet.defense = 2;
    sheet.speed = 2;

    std::uniform_int_distribution<> distribution(-2, 2);
    sheet.hitpoints += distribution(gen);
    sheet.strength += distribution(gen);
    sheet.defense += distribution(gen);
    sheet.speed += distribution(gen);

    current_hp = sheet.hitpoints;
  };

  int ability(){

    std::cout << std::format("{} {}", name, ability_name) << std::endl;

    std::uniform_int_distribution<> distribution(2, 4);
    
    return distribution(gen);
    
  };

};

class Regular : public Enemy {

private:
  std::string ability_name;
  
public:
  Regular(std::string n, std::string a) :
    Enemy(n, {}), ability_name(a) {

    sheet.hitpoints = 12;
    sheet.strength = 8;
    sheet.defense = 4;
    sheet.speed = 10;

    std::uniform_int_distribution<> distribution(-1, 2);
    sheet.hitpoints += distribution(gen);
    sheet.strength += distribution(gen);
    sheet.defense += distribution(gen);
    sheet.speed += distribution(gen);

    current_hp = sheet.hitpoints;
  };

  int ability(){

    std::cout << std::format("{} {}", name, ability_name) << std::endl;

    std::uniform_int_distribution<> distribution(2, 5);
    
    return distribution(gen);
    
  };

};

class Boss : public Enemy {

private:
  std::string ability_name;
  
public:
  Boss(std::string n, std::string a) :
    Enemy(n, {}), ability_name(a) {

    sheet.hitpoints = 20;
    sheet.strength = 10;
    sheet.defense = 6;
    sheet.speed = 12;
    
    std::uniform_int_distribution<> distribution(-2, 7);
    sheet.hitpoints += distribution(gen);
    sheet.strength += distribution(gen);
    sheet.defense += distribution(gen);
    sheet.speed += distribution(gen);

    current_hp = sheet.hitpoints;
  };

  int ability(){

    std::cout << std::format("{} {}", name, ability_name) << std::endl;

    std::uniform_int_distribution<> distribution(5, 12);
    
    return distribution(gen);
    
  };

};

class Guerreiro : public Player {};

class Atirador : public Player {};

class Mago : public Player {};

class Ladino : public Player {};

#endif
