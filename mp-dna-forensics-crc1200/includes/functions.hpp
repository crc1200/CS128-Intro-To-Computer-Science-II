#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
#include <string>
#include <vector>

//CSV Functions
std::string CsvFirst(std:: string path);
std::string CsvSecond(std:: string path);
std::string CsvThird(std:: string path);

//Operrators
std::string Compare(std::string input, std::string path);
std::vector<std::string> CreateVector(std::string path);
std::vector<std::string> ParseString(std::string input);

//Finders
int NumbFirst(std::string input, std::string path);
int NumbSecond(std::string input, std::string path);
int NumbThird(std::string input, std::string path);


#endif