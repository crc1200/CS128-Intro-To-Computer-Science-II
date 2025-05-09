#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP


#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);
  std::vector<CharPositions> Horizontal(const std::string& word);
  std::vector<CharPositions> LeftDiag(const std::string& word);
  std::vector<CharPositions> RightDiag(const std::string& word);
  std::vector<CharPositions> Vertical(const std::string& word);

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
  
};



#endif