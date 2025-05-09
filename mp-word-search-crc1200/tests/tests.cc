// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("Test Right Diagonal") {
    std::vector<std::vector<char>> puzzle{  {'d', 'e', 'a', 'o', 'u'},
                                            {'h', 'e', 'l', 'l', 'o'},
                                            {'c', 'a', 'l', 'o', 'm'},
                                            {'a', 'e', 't', 'a', 'u'},
                                            {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);

    REQUIRE_FALSE(wss.FindWord("hat", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("delau", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("del", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("au", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("lm", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("alm", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("elou", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("ae", CheckDirection::kRightDiag).char_positions.empty());


   

    REQUIRE(wss.FindWord("hattt", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE(wss.FindWord("", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE(wss.FindWord("   ", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE(wss.FindWord("4098309", CheckDirection::kRightDiag).char_positions.empty());
    REQUIRE(wss.FindWord("hatsdlkfjslkfjsdlfslfjsdlfjslkfjsdlkfsjlfkdsjflksj", CheckDirection::kRightDiag).char_positions.empty());


}

TEST_CASE("Test Left Diagonal") {
    std::vector<std::vector<char>> puzzle{  {'d', 'e', 'a', 'o', 'u'},
                                            {'h', 'e', 'l', 'l', 'o'},
                                            {'c', 'a', 'l', 'o', 'm'},
                                            {'a', 'e', 't', 'a', 'u'},
                                            {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);

    REQUIRE_FALSE(wss.FindWord("ullet", CheckDirection::kLeftDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("mat", CheckDirection::kLeftDiag).char_positions.empty());


    
    REQUIRE(wss.FindWord("ootee", CheckDirection::kLeftDiag).char_positions.empty());
    REQUIRE(wss.FindWord("  ", CheckDirection::kLeftDiag).char_positions.empty());
    REQUIRE(wss.FindWord("", CheckDirection::kLeftDiag).char_positions.empty());
    REQUIRE(wss.FindWord("940394820", CheckDirection::kLeftDiag).char_positions.empty());
    REQUIRE(wss.FindWord("mattelhfsdlfsd;jhlksnfsifs;lfhs;fls/fsjhl", CheckDirection::kLeftDiag).char_positions.empty());


}

TEST_CASE("Test Vertical") {
    std::vector<std::vector<char>> puzzle{  {'d', 'e', 'a', 'o', 'u'},
                                            {'h', 'e', 'l', 'l', 'o'},
                                            {'c', 'a', 'l', 'o', 'm'},
                                            {'a', 'e', 't', 'a', 'u'},
                                            {'t', 'e', 't', 'o', 'u'}};

    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("dhcat", CheckDirection::kVertical).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("eeaee", CheckDirection::kVertical).char_positions.empty());

    REQUIRE(wss.FindWord("catt", CheckDirection::kVertical).char_positions.empty());
    REQUIRE(wss.FindWord("405834953805", CheckDirection::kVertical).char_positions.empty());
    REQUIRE(wss.FindWord("", CheckDirection::kVertical).char_positions.empty());
    REQUIRE(wss.FindWord("   ", CheckDirection::kVertical).char_positions.empty());
    REQUIRE(wss.FindWord("eeaeedldjf;lsdkjfs;lfcuxhsfsdl", CheckDirection::kVertical).char_positions.empty());


}

TEST_CASE("Test Horizontal") {
    std::vector<std::vector<char>> puzzle{  {'d', 'e', 'a', 'o', 'u'},
                                            {'h', 'e', 'l', 'l', 'o'},
                                            {'c', 'a', 'l', 'o', 'm'},
                                            {'a', 'e', 't', 'a', 'u'},
                                            {'t', 'e', 't', 'o', 'u'}};

    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("deaou", CheckDirection::kHorizontal).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions.empty());




    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[0].col == 0);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[1].col == 1);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[2].col == 2);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[3].col == 3);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[4].col == 4);

    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[0].row == 1);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[1].row == 1);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[2].row == 1);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[3].row == 1);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions[4].row == 1);


    REQUIRE_FALSE(wss.FindWord("calom", CheckDirection::kHorizontal).char_positions.empty());

    REQUIRE(wss.FindWord("aouuu", CheckDirection::kHorizontal).char_positions.empty());
    REQUIRE(wss.FindWord("    ", CheckDirection::kHorizontal).char_positions.empty());
    REQUIRE(wss.FindWord("", CheckDirection::kHorizontal).char_positions.empty());
    REQUIRE(wss.FindWord("8777686587709", CheckDirection::kHorizontal).char_positions.empty());
    REQUIRE(wss.FindWord("helloddjflksdjfldn;kfhsdfjsf;ksdjfhsd;fjhd;kfusdhfpidsnf;skj", CheckDirection::kHorizontal).char_positions.empty());

}


TEST_CASE("Test Single Arg Function") {
    std::vector<std::vector<char>> puzzle{  {'d', 'e', 'a', 'o', 'u'},
                                            {'h', 'e', 'l', 'l', 'o'},
                                            {'c', 'a', 'l', 'o', 'm'},
                                            {'a', 'e', 't', 'a', 'u'},
                                            {'t', 'e', 't', 'o', 'u'},
                                            {'j', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);

    REQUIRE_FALSE(wss.FindWord("dhcatj").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("eeaeee").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("allttt").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("oloaoo").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("uomuuu").char_positions.empty());

    REQUIRE_FALSE(wss.FindWord("deaou").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("hello").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("calom").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("aetau").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("tetou").char_positions.empty());

    REQUIRE_FALSE(wss.FindWord("j").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("te").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("aet").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("ceto").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("hatou").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("delau").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("elou").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("u").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("oo").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("alm").char_positions.empty());

    REQUIRE_FALSE(wss.FindWord("dhcatj").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("eeaeee").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("allttt").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("oloaoo").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("uomuuu").char_positions.empty());

    REQUIRE_FALSE(wss.FindWord("eae").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("ullet").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("hat").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("uu").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("t").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("u").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("d").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("j").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("a").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("m").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("c").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("h").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("l").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("o").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("tt").char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("dhc").char_positions.empty());
   
    REQUIRE(wss.FindWord("asdlf").char_positions.empty());
    REQUIRE(wss.FindWord("hatlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjknkjhkjhkjhkjhkjhkjhkjhlkjlkj").char_positions.empty());
    REQUIRE(wss.FindWord("jetoulkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjknkjhkjhkjhkjhkjhkjhkjhlkjlkj").char_positions.empty());
    REQUIRE(wss.FindWord("uotlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjknkjhkjhkjhkjhkjhkjhkjhlkjlkj").char_positions.empty());
    REQUIRE(wss.FindWord("allllkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjknkjhkjhkjhkjhkjhkjhkjhlkjlkj").char_positions.empty());
    REQUIRE(wss.FindWord("delkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjlkjknkjhkjhkjhkjhkjhkjhkjhlkjlkj").char_positions.empty());
    REQUIRE(wss.FindWord("").char_positions.empty());
    REQUIRE(wss.FindWord("    ").char_positions.empty());
    REQUIRE(wss.FindWord("ldkfjslfjdlfkjsflkjledjfskfjdlkfjslkfjslfkjsflksjflksdjflksdjflks", CheckDirection::kLeftDiag).char_positions.empty());

}


TEST_CASE("Test Big Words") {
    std::vector<std::vector<char>> puzzle{  {'d', 'e', 'a', 'o', 'u'},
                                            {'h', 'e', 'l', 'l', 'o'},
                                            {'c', 'a', 'l', 'o', 'm'},
                                            {'a', 'e', 't', 'a', 'u'},
                                            {'t', 'e', 't', 'o', 'u'}};

    WordSearchSolver wss(puzzle);
    REQUIRE(wss.FindWord("hat").word == "hat");
    REQUIRE(wss.FindWord("hatasdfasdfasdfasdf").word.empty());
    REQUIRE_FALSE(wss.FindWord("ullet", CheckDirection::kLeftDiag).char_positions.empty());
    REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kHorizontal).char_positions.empty());
    REQUIRE(wss.FindWord("aouuu", CheckDirection::kHorizontal).char_positions.empty());
    REQUIRE(wss.FindWord("8777686587709", CheckDirection::kHorizontal).char_positions.empty());
}





/////////////////////////////////////////////////////////////////////////////////////////////