#include "student.hpp"
#include <ostream>
#include <sstream>
#include<iostream>
#include<fstream>
#include <string>




int main() {
  std::ostringstream ss;
    std::string ans = "Name: Ike South\nUIN: 000000000\nNet Id: ike\nMajor: Undeclared\nCredits: 0\nCourses: \nGraduated: False";
    Student st("Ike South", "000000000", "ike");
    ss << st;
    std::cout << ss.str() << std:: endl;

  return 0;
}
