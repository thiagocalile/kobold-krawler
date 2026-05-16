#include <iostream>
#include <string>
#include <format>
#include <random>

#ifndef ENTITIES_HPP
#define ENTITIES_HPP

// Vamos fazer ao estilo D&D: 10 é médio

enum action_type {
  ATTACK,
  USE_ABILITY,
};

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
    std::uniform_int_distribution<> distribution(0, sheet.strength + 2);

    damage = distribution(gen);
    
    if(damage == 0){
      std::cout <<
	std::format("{} errou o ataque!", name)
		<< std::endl;
    } else if(damage > 0 && damage <= sheet.strength) {
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
    
    if(defended_damage > 0){
    std::cout <<
      std::format("{} defendeu {} do dano infligido!", name, sheet.defense)
	      << std::endl;
    } else {
      std::cout <<
	std::format("{} defendeu todo o dano infligido!", name)
		<< std::endl;
    };
    
    if(defended_damage < 0) defended_damage = 0;

    current_hp -= defended_damage;

    // É um jeito meio estranho, mas ela:
    // * Retorna nullptr se ninguém morreu
    // * Retorna Entity* da entidade que morreu

    // DEBUG
    std::cout << "DEBUG: " << name << " HP: " << current_hp << std::endl;
    //DEBUG


    return (current_hp > 0) ? nullptr : this;
    
  };

  // Pode ser mágico, pode ser um super ataque, use a criatividade :D
  virtual int ability() = 0;

  int get_speed() {return sheet.speed;};

  int get_current_hp() {return current_hp;};

  std::string get_name() {return name;};

  int get_max_hp() {return sheet.hitpoints;};
  
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

  };

  void harden(){
    sheet.hitpoints++;
    sheet.strength++;
    sheet.defense++;
    sheet.speed++;
  };
  
};

class Player : public Entity {

  using Entity::Entity;

protected:
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
	healing_amount = sheet.hitpoints - current_hp;
      };

      current_hp += healing_amount;

      std::cout <<
	std::format("{} curou {} de {} HP máximo", name, healing_amount, sheet.hitpoints)
		<< std::endl;
      
      return true;
    }
    
  };

  virtual void level_up(){
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

    std::cout << std::format("{}... {}", name, ability_name) << std::endl;

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
    sheet.defense = 2;
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
    sheet.defense = 2;
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

class Guerreiro : public Player {

public:
  Guerreiro(std::string n) :
    Player(n, {}) {

    sheet.hitpoints = 12;
    sheet.strength = 8;
    sheet.defense = 3;
    sheet.speed = 5;

    std::uniform_int_distribution<> distribution(-1,1);

    sheet.hitpoints += distribution(gen);
    sheet.strength += distribution(gen);
    sheet.defense += distribution(gen);
    sheet.speed += distribution(gen);;

    current_hp = sheet.hitpoints;

  };

  int ability(){

    std::cout << std::format("{} deu uma estocada com sua espada.", name) << std::endl;

    std::uniform_int_distribution<> distribution(level -1, level + 2);

    int ability_power = distribution(gen);
   
    return sheet.strength + ((ability_power < 0) ? 0 : ability_power);
    
  };

  void level_up() override {
    Player::level_up();
    sheet.hitpoints++;
    sheet.defense++;
  };

};

class Atirador : public Player {

public:
  Atirador(std::string n) :
    Player(n, {}) {

    sheet.hitpoints = 12;
    sheet.strength = 2;
    sheet.defense = 2;
    sheet.speed = 10;

    std::uniform_int_distribution<> distribution(-1,1);

    sheet.hitpoints += distribution(gen);
    sheet.strength += distribution(gen);
    sheet.defense += distribution(gen);
    sheet.speed += distribution(gen);;

    current_hp = sheet.hitpoints;

  };

  int ability(){

    std::uniform_int_distribution<> distribution(level + 1, level + 2);

    int shots = distribution(gen);
    
    std::cout <<
      std::format("{} atirou com sua funda {} vezes.", name, shots)
	       << std::endl;

    return (sheet.strength + sheet.speed) * distribution(gen) / 3;
    
  };

  void level_up() override {
    Player::level_up();
    sheet.speed++;
  };

};

class Mago : public Player {

public:
  Mago(std::string n) :
    Player(n, {}) {

    sheet.hitpoints = 12;
    sheet.strength = 4;
    sheet.defense = 1;
    sheet.speed = 7;

    std::uniform_int_distribution<> distribution(-1,1);

    sheet.hitpoints += distribution(gen);
    sheet.strength += distribution(gen);
    sheet.defense += distribution(gen);
    sheet.speed += distribution(gen);;

    current_hp = sheet.hitpoints;

  };

  int ability(){

    std::uniform_int_distribution<> distribution(level + 1, level + 2);

    int magical_damage = (level * 2 + sheet.speed) * distribution(gen) / 2;
    
    std::cout <<
      std::format("{} entoa vários encantamentos e causa {} de dano.",
		  name, magical_damage)
	       << std::endl;

    return magical_damage;
    
  };

  void level_up() override {
    Player::level_up();
    sheet.speed++;
  };

};

class Ladino : public Player {

public:
  Ladino(std::string n) :
    Player(n, {}) {

    sheet.hitpoints = 8;
    sheet.strength = 4;
    sheet.defense = 0;
    sheet.speed = 15;

    std::uniform_int_distribution<> distribution(-1,1);

    sheet.hitpoints += distribution(gen);
    sheet.strength += distribution(gen);
    sheet.defense += distribution(gen);
    sheet.speed += distribution(gen);;

    current_hp = sheet.hitpoints;

  };

  int ability(){

    std::uniform_int_distribution<> distribution( (level / 2) + 1, level + 2);

    int stabs = (level + (sheet.speed / 2) ) * distribution(gen);

    // Conserta problema das facadas ficarem sempre como 0
    std::cout <<
          std::format("{} esfaqueou {} vezes, totalizando {} de dano.",
	          name, stabs, damage)
	           << std::endl;
    
    // Declarar aqui um novo nome conserta um bug de compilação
    // que eu não estou a fim de descobrir o motivo
    std::uniform_int_distribution<> distrib(0, (sheet.strength / 2));

    int damage {};
    
    for(; stabs > 0; stabs--){
      damage += distrib(gen);
    }
    
    
    return damage;
    
  };

  void level_up() override {
    Player::level_up();
    sheet.speed++;
  };

};

#endif
