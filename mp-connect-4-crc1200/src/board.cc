#include "board.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (unsigned int i = 0; i < Board::kBoardHeight; i++) {
    for (unsigned int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  bool checker = false;
  if (col > Board::kBoardWidth - 1 || col < 0) {
    throw std::runtime_error("Invalid Column");
  }
  for (unsigned int row = 0; row < Board::kBoardHeight; row++) {
    if (b.board[row][col] == DiskType::kEmpty) {
      checker = true;
      b.board[row][col] = disk;
      break;
    }
  }
  if (!checker) {
    throw std::runtime_error("You suck");
  }
}
bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kHorizontal) || SearchForWinner(b, disk, WinningDirection::kVertical) || SearchForWinner(b, disk, WinningDirection::kLeftDiag) || SearchForWinner(b, disk, WinningDirection::kRightDiag);
}


bool HorizontalSearch(Board& b, DiskType disk) {
  for (unsigned int col = 0; col < Board::kBoardWidth - 3; col++) {
      for (unsigned int row = 0; row < Board::kBoardHeight; row++) {
        if (b.board[row][col] == disk && b.board[row][col + 1] == disk && b.board[row][col + 2] == disk && b.board[row][col + 3] == disk) {
          return true;
        }
      }
    }
    return false;
}

bool VerticalSearch(Board& b, DiskType disk) {
  for (unsigned int col = 0; col < Board::kBoardWidth; col++) {
      for (unsigned int row = 0; row < Board::kBoardHeight - 3; row++) {
        if (b.board[row][col] == disk && b.board[row + 1][col] == disk && b.board[row + 2][col] == disk && b.board[row + 3][col] == disk) {
          return true;
        }
      }
    }
    return false; 
}

bool LeftDiagonalSearch(Board& b, DiskType disk) {
  for (unsigned int col = 0; col < Board::kBoardWidth - 3; col++) {
      for (unsigned int row = 3; row < Board::kBoardHeight; row++) {
        if (b.board[row][col] == disk && b.board[row - 1][col + 1] == disk && b.board[row - 2][col + 2] == disk && b.board[row - 3][col + 3] == disk) {
          return true;
        }
      }
    }
    return false;
}

bool RightDiagonalSearch(Board& b, DiskType disk) {
  for (unsigned int col = 0; col < Board::kBoardWidth - 3; col++) {
      for (unsigned int row = 0; row < Board::kBoardHeight - 3; row++) {
        if (b.board[row][col] == disk && b.board[row + 1][col + 1] == disk && b.board[row + 2][col + 2] == disk && b.board[row + 3][col + 3] == disk) {
          return true;
        }
      }

    }
    return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check){
  //horizontal winner
  if (to_check == WinningDirection::kHorizontal) {
    return HorizontalSearch(b, disk);
  }
  //vertical winner
  if (to_check == WinningDirection::kVertical) {
    return VerticalSearch(b, disk);
  }
  //left diagonal winner
  if (to_check == WinningDirection::kLeftDiag) {
    return LeftDiagonalSearch(b, disk);
  }
  //right diagonal winner
  if (to_check == WinningDirection::kRightDiag) {
    return RightDiagonalSearch(b,disk);
  }
  return false;
}

bool BoardLocationInBounds(int row, int col){
  return (row < Board::kBoardHeight && row >= 0 && col < Board::kBoardWidth && col >= 0);
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}