#include "minesweeper.h"

#include <iostream>

int main (int argc, char *argv[]) {
  int dim;
  std::cout << "Please enter the size of the board: \n";
  std::cin >> dim;
  MineSweeper m(dim);
  std::cout << m.Display();
  while (true) {
    std::cout << "Make a move on: (i, j) -> \n";
    int i, j;
    std::cin >> i >> j;
    Reply reply = m.Move(i, j);
    if (reply == ILLEGAL) {
      std::cout << "That move is not valid!\n";
      continue;
    }
    std::cout << m.Display();
    if (reply == MINE) {
      std::cout << "Sorry, you lost\n";
      break;
    }
    if (reply == USER_WON) {
      std::cout << "Congrats! you have revealed all the squares without stepping on a mine!\n";
      break;
    }
  }
}
