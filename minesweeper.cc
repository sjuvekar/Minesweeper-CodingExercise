#include "minesweeper.h"

#include <queue>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

namespace {

Reply UserWinStatus(const std::vector<std::vector<bool> >& board,
                    const std::vector<std::vector<bool> >& revealed,
                    int dim) {
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (!board[i][j] && !revealed[i][j]) return NONE;
    }
  }
  return USER_WON;
}

}  // namespace

MineSweeper::MineSweeper(unsigned int dim) : dim(dim) {
  board.assign(dim, std::vector<bool>());
  neighbors.assign(dim, std::vector<int>());
  revealed.assign(dim, std::vector<bool>());
  for (int i = 0; i < dim; i++) {
    board[i].assign(dim, false);
    neighbors[i].assign(dim, 0);
    revealed[i].assign(dim, false);
  }
  // Add a few random mines
  int num = dim * dim / 10;
  srand (time(NULL));
  for (int i = 0; i < num; i++) {
    int r = rand() % dim;
    int c = rand() % dim;
    board[r][c] = true;
  }
  // Recalculate neighbors function
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      int nei = 0;
      std::vector<std::pair<int, int>> offsets = {
        {i-1, j}, {i+1, j}, {i, j-1}, {i, j+1},
        {i-1, j-1}, {i-1, j+1}, {i+1, j-1}, {i+1, j+1}
      };
      for (const auto& p : offsets) {
        int new_i = p.first;
        int new_j = p.second;
        if (new_i >= 0 && new_j >= 0 &&
            new_i < dim && new_j < dim &&
            board[new_i][new_j]) {
          nei++;
        }
      }
      neighbors[i][j] = nei;
    }
  }
}

std::string MineSweeper::Display() const {
  std::string ret;
  for (int i = 0; i < dim; i++) {
    ret += "--";
  }
  ret += "\n";
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (revealed[i][j]) {
        if (board[i][j]) {
          ret += "|*";
        } else {
          if (neighbors[i][j] == 0) {
            ret += "|#";
          } else {
            ret += "|" + std::to_string(neighbors[i][j]);
          }
        }
      } else {
        ret += "| ";
      }
    }
    ret += "|\n";
    for (int i = 0; i < dim; i++) {
      ret += "--";
    }
    ret += "\n";
  }
  return ret;
}

Reply MineSweeper::Move(int i, int j) {
  if (i < 0 || j < 0 || i >= dim || j >= dim) {
    return ILLEGAL;
  }
  if (board[i][j]) {
    revealed[i][j] = true;
    return MINE;
  }
  if (revealed[i][j]) {
    return ILLEGAL;
  }
  revealed[i][j] = true;
  if (neighbors[i][j] != 0) {
    return UserWinStatus(board, revealed, dim);
  }
  std::queue<std::pair<int, int>> q;
  q.push(std::make_pair(i, j));
  while (!q.empty()) {
    const auto curr = q.front();
    q.pop();
    int cur_i = curr.first;
    int cur_j = curr.second;
    std::vector<std::pair<int, int>> offsets = {
      {cur_i-1, cur_j}, {cur_i+1, cur_j},
      {cur_i, cur_j-1}, {cur_i, cur_j+1},
      {cur_i-1, cur_j-1}, {cur_i-1, cur_j+1},
      {cur_i+1, cur_j-1}, {cur_i+1, cur_j+1}
    };
    for (const auto& p : offsets) {
      int new_i = p.first;
      int new_j = p.second;
      if (new_i >= 0 && new_j >= 0 &&
          new_i < dim && new_j < dim &&
          !board[new_i][new_j] && !revealed[new_i][new_j]) {
        revealed[new_i][new_j] = true;
        if (neighbors[new_i][new_j] == 0) {
          q.push(std::make_pair(new_i, new_j));
        }
      }
    }
  }
  return UserWinStatus(board, revealed, dim);
}
