#include <vector>

// É uma má prática ocultar todas as chamadas dentro desse cara, mas é
// Só quero acbar o trabalho logo...
#include "ui.hpp"

int main(){
  UI* ui = new UI;
  ui->run();
  delete ui;
}
