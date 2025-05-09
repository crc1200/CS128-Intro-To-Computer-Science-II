// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Disk Drop", "[drop_disk_to_board]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  REQUIRE(b.board[0][0] == DiskType::kPlayer1);
  REQUIRE(b.board[0][1] == DiskType::kPlayer1);
  REQUIRE(b.board[0][2] == DiskType::kPlayer1);
  REQUIRE(b.board[0][3] == DiskType::kPlayer1);
  REQUIRE(b.board[0][4] == DiskType::kPlayer1);
  REQUIRE(b.board[0][5] == DiskType::kPlayer1);
  REQUIRE(b.board[0][6] == DiskType::kPlayer1);
  
}

TEST_CASE("Disk Drop Overflow", "[drop_disk_to_board]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, 3));
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer2, 3));
}

TEST_CASE("Disk Drop Invalid Location", "[drop_disk_to_board]") {
  Board b;
  InitBoard(b);
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, -1));
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth));
}

TEST_CASE("Board Border Valid", "[valid_board]") {
  Board b;
  InitBoard(b);
  REQUIRE(BoardLocationInBounds(0,0));
  REQUIRE_FALSE(BoardLocationInBounds(6,6));
  REQUIRE_FALSE(BoardLocationInBounds(-4,1));
  REQUIRE_FALSE(BoardLocationInBounds(1,-4));
  REQUIRE_FALSE(BoardLocationInBounds(-1,-1));
  REQUIRE_FALSE(BoardLocationInBounds(10,10));
}

TEST_CASE("Bad Search", "[bad_search]") {
  Board b;
  InitBoard(b);
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
}

TEST_CASE("Check Win Vertical", "[win_vertical]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
}

TEST_CASE("Check Win Vertical Back", "[win_back]") {
  Board b;
  InitBoard(b);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth - 1);
  DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth - 1);
  DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth - 1);
  DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth - 1);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
}

TEST_CASE("Check for winner", "[win]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth - 1);
  DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth - 1);
  DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth - 1);
  DropDiskToBoard(b, DiskType::kPlayer1, Board::kBoardWidth - 1);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("Check Win Vertical Front", "[win_front]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
}

TEST_CASE("Check False Winner Vertical", "[win_false]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
}

TEST_CASE("Search False Winner Vertical", "[search_false]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
}

TEST_CASE("Check Win Vertical Corner", "[win_vertical]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
}

TEST_CASE("Check Win Horizontal top left corner", "[horizontal]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);

  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 0); 

  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("Check Win Horizontal top right corner", "[horizontal]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 3); 

  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("Check top right Diagonal Corner", "[win_rdiag]") {
  Board b;
  InitBoard(b);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);

  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
}

TEST_CASE("Check top left Diagonal Corner", "[win_rdiag]") {
  Board b;
  InitBoard(b);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);

  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);

  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
}

TEST_CASE("Check Win Horizontal bottom left corner", "[horizontal]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}


TEST_CASE("Check Win Horizontal top", "[horizontal]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE("Check Win Horizontal middle", "[horizontal]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("Check Win Horizontal bottom", "[horizontal]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("Check right Diagonal", "[win_rdiag]") {
  Board b;
  InitBoard(b);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
}

TEST_CASE("Check left Diagonal", "[win_ldiag]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
}



TEST_CASE("Check Full Board - No Winners", "[full_none]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);

  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);

  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
}