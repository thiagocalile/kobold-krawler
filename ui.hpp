#include <iostream>
#include <string>
#include <vector>
#include <format>

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
  Combat* current_combat;
  
public:
  UI() {

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
      break;

    case ATIRADOR:
      p = new Atirador;
      break;
      
    case MAGO:
      p = new Mago;
      break;
      
    case LADINO:
      p = new Ladino;
      break;
      
    };

    std::cout << "Agora, escolha um tamanho para a sua caverna (Recomendado é 5).";

    std::cout << "Digite o tamanho em salas: ";

    do{ 
      std::cin >> dungeon_size;
      if(dungeon_size < 1) std::cout << "Tamanho mínimo é 1!" << std::endl;
    } while(dungeon_size < 1);

    for(; dungeon_size > 0; dungeon_size--){
      dungeon.push_back((generate_enemy()));
    };

    dungeon.push_back(generate_boss());
    
    game = new Game(p, dungeon);

    std::cout << "A boca da caverna te aguarda..." << std::endl;

    current_combat = game->start_combat();
    
  };
  
  void show_combat(){

    int prompt {};

    do {
	do {
	    std::cout << "Qual ação você quer tomar?" << std::endl;
	    std::cout << "0) Atacar" << std::endl;
	    std::cout << "1) Usar poção" << std::endl;
	    std::cout << "2) Usar habilidade" << std::endl;

	    std::cin >> prompt;

	    if(prompt > 2 || prompt < 0) {
	          std::cout << "Escolha uma das opções!" << std::endl;
	    }
	
	} while(prompt > 2 || prompt < 0);

    } while(//Meio confuso, mas veja combat.hpp, Combat->run_turn();
	     current_combat->run_turn(
	       p, //player
	       static_cast<action_type>(prompt),
	       game->get_current_enemy()
	       )
	    );
      
    game->end_combat();
    
  };
  
  void show_rest(){

    int option {};
    int heal_amount {};

    std::cout <<
      std::format("{} triunfou em combate!", p->get_name())
	      << std::endl;
    std::cout <<
      ((p->get_current_hp() > 1) ?
      std::format("Lhe sobraram {} pontos de vida.", p->get_current_hp()) :
       std::format("Lhe sobrou apenas um mísero ponto de vida."))
	      << std::endl;
    do{
      
      std::cout << "Agora, resta-lhe uma pergunta: " << std::endl;
      std::cout << "1) Descansar, mas os monstros ficam mais fortes."
	        << std::endl;
      std::cout <<
        std::format("2) Prosseguir para a próxima \
                     sala como {} está agora.", p->get_name())
	        << std::endl;

      std::cin >> option;
      
      if(option == 1){
	if(!p->heal()){
	  std::cout << "Nenhum monstro ficou mais forte." << std::endl;
	} else {
	  harden_monsters(dungeon);
	  std::cout << "Os monstros também ficaram mais fortes" << std::endl;
	};
	
      };

      if(option != 1 && option != 2){
	std::cout << "Escolha uma das opções!" << std::endl;
      };
      
    } while(option != 2);
    
  };
  
  void show_ending(game_state state){
    if(state == GOOD_ENDING){
      std::cout <<
	std::format(
		    "Parabéns, {} sobrevieu a todas as criaturas, \
                     além do monstro horrível final", p->get_name())
		         << std::endl;
      std::cout <<
	std::format("Agora, {} volta para casa, para seu dragão.", p->get_name())
		<< std::endl;
      std::cout << "Suas mãos com os espólios da vitória!" << std::endl;

      std::cout <<
	"Mas sua paz é momentânea. Tal é a vida sob um tirano..."
		<< std::endl;
    } else {

      std::cout <<
	std::format("Infelizmente, {} pereceu...", p->get_name())
		<< std::endl;

      std::cout <<
	std::format("Ninguém lembrará de {} além de você...", p->get_name())
		<< std::endl;

      std::cout <<
	std::format(
		    "Muitos outros kobolds virão depois \
                    de {} e também serão esquecidos...", p->get_name())
		<<std::endl;
      
      std::cout << "Mas tal é a vida sob um tirano..." << std::endl;
      
    };
  };

  bool run() {

    for(;;){

      switch(game->get_current_state()){

      case START:
	show_start();
	break;

      case COMBAT:
	show_combat();
	break;

      case REST:
	show_rest();
	break;
	
      case BAD_ENDING:
      case GOOD_ENDING:
	show_ending(game->get_current_state());
	is_running = false;
	break;
      }
      
      if(is_running){ continue; } else{ break; }
      
    };

  }
};

#endif
