#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// General
std::vector<std::string> CreateVector(std::string path) {
    std::vector<std::string> people_data;
    std::ifstream ifs{path};
    for(std::string line; std::getline(ifs, line); line = "") {
        people_data.push_back(line);
    }
    return people_data;
}

std::vector<std::string> ParseString(std::string input) {
    std::vector<std::string> result;
    std::string temp;
    for (int i = 0; i < (int)input.size(); i++) {
        if (input[i] != ',') {
            temp += input[i];
        } else {
            result.push_back(temp);
            temp = "";
        }
    }
    result.push_back(temp);
    return result;
}

std::string Compare(std::string input, std::string path) {

    int first_max = NumbFirst(input, path);
    int second_max = NumbSecond(input, path);
    int third_max = NumbThird(input, path);
    std::vector<std::string> people = CreateVector(path);
    for(unsigned int i = 1; i < people.size(); i++) {
        std::vector<std::string> people_data = ParseString(people[i]);
        int first_as_int = std::stoi(people_data[1]);
        int second_as_int = std::stoi(people_data[2]);
        int third_as_int = std::stoi(people_data[3]);
        if ((first_max == first_as_int) && (second_max == second_as_int) && (third_max == third_as_int)) {
            return people_data[0];
        }
    }
    return "No Match";
}

//CSV Finders
std::string CsvFirst(std::string path) {
    std::vector<std::string> first_vector = CreateVector(path);
    std::vector<std::string> parsed_line = ParseString(first_vector[0]);
    return parsed_line[1];
}

std::string CsvSecond(std::string path) {
    std::vector<std::string> first_vector = CreateVector(path);
    std::vector<std::string> parsed_line = ParseString(first_vector[0]);
    return parsed_line[2];
}

std::string CsvThird(std::string path) {
    std::vector<std::string> first_vector = CreateVector(path);
    std::vector<std::string> parsed_line = ParseString(first_vector[0]);
    return parsed_line[3];
}


//Amounts 
int NumbFirst(std::string input, std::string path) {
    int count = 0;
    std::string first = CsvFirst(path);
    while (!input.empty()) {
        int temp = 0;
        if (input.find(first) == 0) {
            while (input.find(first) == 0) {
                temp++;
                input = input.substr(first.size());
            }
            if (temp > count) {
                count = temp;
            }
        } else {
        input = input.substr(1);
        }
    }
    return count;
}

int NumbSecond(std::string input, std::string path) {
    int count = 0;
    std::string second = CsvSecond(path);
    while (!input.empty()) {
        int temp = 0;
        if (input.find(second) == 0) {
            while (input.find(second) == 0) {
                temp++;
                input = input.substr(second.size());
            }
            if (temp > count) {
                count = temp;
            }
        } else {
        input = input.substr(1);
        }
    }
    return count;
}

int NumbThird(std::string input, std::string path) {
    int count = 0;
    std::string third = CsvThird(path);
    while (!input.empty()) {
        int temp = 0;
        if (input.find(third) == 0) {
            while (input.find(third) == 0) {
                temp++;
                input = input.substr(third.size());
            }
            if (temp > count) {
                count = temp;
            }
        } else {
        input = input.substr(1);
        }
    }
    return count;
}
