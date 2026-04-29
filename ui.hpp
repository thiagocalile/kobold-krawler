#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"
#include "entities.hpp"

#ifndef UI_H
#define UI_H

enum classes {

  GUERREIRO = 1,
  ATIRADOR,
  MAGO,
  LADINO,

};

class UI {

private:
  Game* game;
  bool is_running = true;
  Player* p;
  int dungeon_size = 5;
  std::vector<Enemy*> dungeon;
  
public:
  UI() : {

    std::cout << "Bem vinde!" << std::endl;
    
  };

  void show_start(){
    
    std::cout << "Esse é o mundo de Kobold Krawler!" << std::endl;
    std::cout << "O seu dragão pediu para coletar mais um objeto de grande valor para sua horda..." << std::endl;
    std::cout << "Ninguém quis te acompanhar nessa missão..." << std::endl;
    std::cout << "Pelo menos, você tem a chance de não ser comido, tudo dando certo..." << std::endl;
    std::cout << "Escolha a sua classe:" << std::endl;

    std::cout << "1) Guerreiro" << std::endl;
    std::cout << "2) Atirador" << std::endl;
    std::cout << "3) Mago" << std::endl;
    std::cout << "4) Ladino" << std::endl;

    int classe = 10; // Arbitrário mesmo, que seja
    
    while(classe < 1 || classe > 4){
      std::cout << "Digite um número: "; 
      std::cin >> classe;
      if(classe < 1 || classe > 4) std::cout << "Escolha um dos números!" << std::endl;
    };
    
    switch(static_cast<classes>(classe)){

    case GUERREIRO:
      p = new Guerreiro;

    case ATIRADOR:
      p = new Atirador;

    case MAGO:
      p = new Mago;

    case LADINO:
      p = new Ladino;

    };

    std::cout << "Agora, escolha um tamanho para a sua caverna (Recomendado é 5).";

    std::cout << "Digite o tamanho em salas: ";

    do{
      std::cin >> dungeon_size;
    } while(dungeon_size < 1; std::cout << "Tamanho mínimo é 1!" << std::endl;);

    game
    
  };
  
  void show_combat(){
  };
  
  void show_rest(){
  };
  
  void show_ending(game_state state){
  };

  bool run() {

    for(;;){

      switch(game.get_current_state()){

      case START:
	show_start();

      case COMBAT:
	show_combat();

      case REST:
	show_rest();

      case BAD_ENDING:
      case GOOD_ENDING:
	show_ending(game.get_current_state());
      }
      
      (is_running) ? continue : break;
      
    };

  }
}

#endif
