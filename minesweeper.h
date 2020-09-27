#include <string>
#include <vector>

enum Reply {
  NONE = 0,
  ILLEGAL = 1,
  MINE = 2,
  USER_WON = 3,
};

class MineSweeper {

public:
  explicit MineSweeper(unsigned int dim);
  virtual ~MineSweeper() {}
  Reply Move(int i, int j);
  std::string Display() const;

private:
  unsigned int dim;
  std::vector<std::vector<bool>> board;
  std::vector<std::vector<int>> neighbors;
  std::vector<std::vector<bool>> revealed;
};
