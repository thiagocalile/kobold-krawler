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

struct enemy_ability_pair {

  std::string enemy_name;
  std::string ability_name;

};

void harden_monsters(std::vector<Enemy*> dungeon){

  for(Enemy* enemy : dungeon){
    enemy->harden();
  };
  
};

class UI {

private:
  Game* game;
  bool is_running = true;
  Player* p;
  int dungeon_size = 5;
  std::vector<Enemy*> dungeon;
  Combat* current_combat;
  bool is_initializing = true;

  Enemy* generate_enemy(int enemy_type){

      std::random_device rd;
      std::mt19937 gen(rd());
    
    if(enemy_type == 0){

      std::vector<enemy_ability_pair> vermin_names = {
	{"Os ratos amaldiçoados", "mordem!"},
	{"As galinhas atômicas", "bicam sem parar!"},
	{"O enxame de mosquitos egípicios", "picam incessantemente!"},
	{"As samambaias psíquicas", "causam enxaqueca!"},
	{"As carpas mágicas", "pulam sem parar!"},
	{"Os gerbis geneticamente modificados", "pulam freneticamente!"},
	{"Os ovos flamejantes", "atiram fogo!"},
	{"Os livros voadores", "retalham com palavras complicadas!"},
	{"Os monstros indescritíveis", "fazem coisas impronunciáveis!"},
	{"As sombras nas paredes", "contam os piores segredos!"},
	{"As rodas de carroça infernais", "usam ondas mentais!"},
	{"Os cristais brilhantes", "disparam lasers!"},
	{"Os laticiínios em promoção", "causam indigestão!"},
	{"As víboras venenosas", "cospem veneno!"},
	{"Os tomates assassinos", "tentam koboldicídio!"},
      };

      std::uniform_int_distribution<> distrib(0, vermin_names.size() - 1);

      enemy_ability_pair enemy = vermin_names[distrib(gen)];
      
      return new Vermin(enemy.enemy_name, enemy.ability_name);
      
    } else if (enemy_type == 1){

      std::vector<enemy_ability_pair> regular_names = {
	{"O gorila graúdo", "joga pedras!"},
	{"A gosma ácida", "atira meleca!"},
	{"O parasita interdimensional", "grita frequências impossíveis!"},
	{"O espelho mágico", "mostra cenas horripilantes!"},
	{"A aranha do tamanho de um cachorro", "atira teia!"},
	{"As águas-vivas flutuantes", "dão choques elétricos!"},
	{"A espada mágica flutuante", "corta o ar!"},
	{"O cogumelo de chapéu vermelho", "solta esporos irritantes!"},
	{"A caveira risonha", "cospe uma substância vil!"},
	{"A criatura de fumaça", "lufa ar calcinante!"},
	{"A mão do Lich", "conjura magias proibidas!"},
	{"O avestruz encouraçado", "atira com seu arco e flecha!"},
	{"O estrunfo sombrio", "clumba o trembo!"},
	{"O espectro inquieto", "move a mobília!"},
	{"A boneca maldita", "atira bolas de naftalina!"},
      };

      std::uniform_int_distribution<> distrib(0, regular_names.size() - 1);
      
      enemy_ability_pair enemy = regular_names[distrib(gen)];
      
      return new Regular(enemy.enemy_name, enemy.ability_name);
      
    } else {

      std::vector<enemy_ability_pair> boss_names = {
	{"O licantropo", "uiva!"},
	{"O vampiro", "usa seu olhar petrificante!"},
	{"A múmia do faraó", "manda 'devolver a pedra'!"},
	{"O lhurgoyf", "ataca com múltiplos membros!"},
	{"O dragão de plutônio", "cospe radiação!"},
      };

      std::uniform_int_distribution<> distrib(0, boss_names.size() - 1);

      enemy_ability_pair enemy = boss_names[distrib(gen)];
      
      return new Boss(enemy.enemy_name, enemy.ability_name);

    }
    
  };

  Enemy* generate_boss(){
    return generate_enemy(2);
  };
  
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

    std::string nome;

    do{
      std::cout << "Dê um nome para a sua criatura: " << std::endl;

      std::getline(std::cin >> std::ws, nome);

      if(nome.size() > 20){
	std::cout << "Limite o nome para até 20 characteres!" << std::endl;
      }

    } while(nome.size() > 20);
    
    switch(static_cast<classes>(classe)){

    case GUERREIRO:
      p = new Guerreiro(nome);
      break;

    case ATIRADOR:
      p = new Atirador(nome);
      break;
      
    case MAGO:
      p = new Mago(nome);
      break;
      
    case LADINO:
      p = new Ladino(nome);
      break;
      
    };

    std::cout <<
      "Agora, escolha um tamanho para a sua caverna (Recomendado é 5)."
	      << std::endl;
    
    std::cout << "Digite o tamanho em salas: ";

    do{ 
      std::cin >> dungeon_size;
      if(dungeon_size < 1) std::cout << "Tamanho mínimo é 1!" << std::endl;
    } while(dungeon_size < 1);

    int original_dungeon_size = dungeon_size;
    
    for(int monster_type {}; dungeon_size > 0; dungeon_size--){

      if(dungeon_size < (original_dungeon_size / 5) * 3) monster_type = 1;
      
      dungeon.push_back((generate_enemy(monster_type)));
    };

    dungeon.push_back(generate_boss());
    
    game = new Game(p, dungeon);

    std::cout << "A boca da caverna te aguarda..." << std::endl;

    current_combat = game->start_combat();

    is_initializing = false;
    
  };
  
  void show_combat(){

    int prompt {};

    do {
	do {
	  std::cout <<
	    std::format("{} - HP: {}/{}",
			p->get_name(),
			p->get_current_hp(),
			p->get_max_hp()
			) << std::endl;
	    std::cout << "Qual ação você quer tomar?" << std::endl;
	    std::cout << "0) Atacar" << std::endl;
	    std::cout << "1) Usar habilidade" << std::endl;

	    std::cin >> prompt;

	    if(prompt > 1 || prompt < 0) {
	          std::cout << "Escolha uma das opções!" << std::endl;
	    }
	
	} while(prompt > 1 || prompt < 0);

    } while(//Meio confuso, mas veja combat.hpp, Combat->run_turn();
	     !current_combat->run_turn(
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

    p->level_up();

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
        std::format("2) Prosseguir para a próxima sala como {} está agora.",
		    p->get_name()
		    )
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

    game->end_rest();
    current_combat = game->start_combat();
    
  };
  
  void show_ending(game_state state){
    if(state == GOOD_ENDING){
      std::cout <<
	std::format(
	  "Parabéns, {} sobrevieu a todas as criaturas, além do monstro horrível final",
	  p->get_name())
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
	    "Muitos outros kobolds virão depois de {} e também serão esquecidos...",
	    p->get_name())
		<<std::endl;
      
      std::cout << "Mas tal é a vida sob um tirano..." << std::endl;
      
    };
  };

  void run() {

    show_start();
    
    for(;;){

      switch(game->get_current_state()){

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

  };
};

#endif
