#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::string Base(std::string test);

std::string Check(std::string word);
int ACheck(std::string word);
int ECheck(std::string word);
int ICheck(std::string word);
int OCheck(std::string word);
int UCheck(std::string word);
std::string O(char next);
std::string E(char next);
std::string A(char next);
std::string U(char next);
std::string I(char next);
std::string W(char last, unsigned int index);
std::string Space(std::string word, char next);

#endif