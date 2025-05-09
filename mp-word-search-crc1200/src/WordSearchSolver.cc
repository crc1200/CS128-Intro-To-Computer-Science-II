#include "WordSearchSolver.hpp"

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle) {
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle[0].size();
  puzzle_ = puzzle;
}

std::vector<CharPositions> WordSearchSolver::Horizontal(const std::string& word) {
    std::vector<CharPositions> chars;
    for (unsigned int row = 0; row < puzzle_height_; row++) {
      for (unsigned int col = 0; col < puzzle_width_; col++) {
        if (puzzle_[row][col] == word.at(0)) {
          if (word.length() == 1) {
            chars.push_back(CharPositions{word.at(0), row, col});
            return chars;
          }
          chars.push_back(CharPositions{word.at(0), row, col});
          for (unsigned int i = 1; i < word.length(); i++) {
            if (col + i < puzzle_width_ && puzzle_[row][col + i] == word.at(i)) {
              chars.push_back(CharPositions{word.at(i), row, col + i});
              if (chars.size() == word.length()) {
                return chars;
              }
            } else {
              chars.clear();
            }
          }
        }
      }
    }
  chars.clear();
  return chars;
}
std::vector<CharPositions> WordSearchSolver::Vertical(const std::string& word) {
std::vector<CharPositions> chars;
    for (unsigned int row = 0; row < puzzle_height_; row++) {
      for (unsigned int col = 0; col < puzzle_width_; col++) {
        if (puzzle_[row][col] == word.at(0)) {
          if (word.length() == 1) {
            chars.push_back(CharPositions{word.at(0), row, col});
            return chars;
          }
          chars.push_back(CharPositions{word.at(0), row, col});
          for (unsigned int i = 1; i < word.length(); i++) {
            if (row + i < puzzle_height_) {
              if (puzzle_[row + i][col] == word.at(i)) {              
                chars.push_back(CharPositions{word.at(i), row + i, col});
                if (chars.size() == word.length()) {
                  return chars;
                }
              } else {
                chars.clear();
              }
            }
          }
        }
      }
    }
  chars.clear();
  return chars;
}
std::vector<CharPositions> WordSearchSolver::LeftDiag(const std::string& word) {
  std::vector<CharPositions> chars;
    for (unsigned int row = 0; row < puzzle_height_; row++) {
      for (unsigned int col = 0; col < puzzle_width_; col++) {
        if (puzzle_[row][col] == word.at(0)) {
          if (word.length() == 1) {
            chars.push_back(CharPositions{word.at(0), row, col});
            return chars;
          }
          chars.push_back(CharPositions{word.at(0), row, col});
          for (unsigned int i = 1; i < word.length(); i++) {
            if ((row + i) < puzzle_height_ && int(col - i) >= 0 && (col - i) < puzzle_width_) {
              if (puzzle_[row + i][col - i] == word.at(i)) {
                chars.push_back(CharPositions{word.at(i), row + i, col - i});
                if (chars.size() == word.length()) {
                  return chars;
                }
              } else {
                chars.clear();
              }
            }
          }
        }
      }
    }
    chars.clear();
    return chars;
}
std::vector<CharPositions> WordSearchSolver::RightDiag(const std::string& word) {
 std::vector<CharPositions> chars;
    for (unsigned int row = 0; row < puzzle_height_; row++) {
      for (unsigned int col = 0; col < puzzle_width_; col++) {
        if (puzzle_[row][col] == word.at(0)) {
          if (word.length() == 1) {
            chars.push_back(CharPositions{word.at(0), row, col});
            return chars;
          }
          chars.push_back(CharPositions{word.at(0), row, col});
          for (unsigned int i = 1; i < word.length(); i++) {
            if (row + i < puzzle_height_ && col + i < puzzle_width_) {
              if (puzzle_[row + i][col + i] == word.at(i)) {
                chars.push_back(CharPositions{word.at(i), row + i, col + i});
                if (chars.size() == word.length()) {
                  return chars;
                }
              } else {
                chars.clear();
              }
            }
          }
        }
      }
    }
  chars.clear();
  return chars;
}



WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {
  if (word.length() == 0) {
    return WordLocation{};
  }
  if (direction == CheckDirection::kHorizontal) {
    return WordLocation{word, Horizontal(word)};
  }

  if (direction == CheckDirection::kVertical) {
    return WordLocation{word, Vertical(word)};
  }

  if (direction == CheckDirection::kRightDiag) {
    return WordLocation{word, RightDiag(word)};
  }

  if (direction == CheckDirection::kLeftDiag) {
    return WordLocation{word, LeftDiag(word)};
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  if (word.length() == 0) {
    return WordLocation{};
  }
  if (!FindWord(word, CheckDirection::kHorizontal).char_positions.empty()) {
    return FindWord(word, CheckDirection::kHorizontal);
  }
  if (!FindWord(word, CheckDirection::kVertical).char_positions.empty()) {
    return FindWord(word, CheckDirection::kVertical);

  }
  if (!FindWord(word, CheckDirection::kLeftDiag).char_positions.empty()) {
    return FindWord(word, CheckDirection::kLeftDiag);

  }
  if (!FindWord(word, CheckDirection::kRightDiag).char_positions.empty()) {
    return FindWord(word, CheckDirection::kRightDiag);
  }
  return WordLocation{};
}