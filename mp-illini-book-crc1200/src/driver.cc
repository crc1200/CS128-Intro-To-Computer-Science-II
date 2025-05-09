#include "illini_book.hpp"
#include <map>
#include<vector>
#include <iostream>

int main() {
  auto *test = new IlliniBook("./example/persons.csv", "./example/relations.csv");

  int c1 = test->GetRelated(1, 2);	//1
  int c2 = test->GetRelated(3, 2); //2
  int c3 = test->GetRelated(1, 9);	//-1
  int c4 = test->GetRelated(1, 2, "128");	//1
  int c5 = test->GetRelated(1, 2, "124");	//-1
  int c6 = test->GetRelated(1, 6, "128");	//2
  int c7 = test->GetRelated(1, 6, "124");	//1

  std::cout << c1 << std::endl;
  std::cout << c2 << std::endl;
  std::cout << c3 << std::endl;
  std::cout << c4 << std::endl;
  std::cout << c5 << std::endl;
  std::cout << c6 << std::endl;
  std::cout << c7 << std::endl;
  test->~IlliniBook();
  
  return 0;
}

  // std::cout << std::endl;

  // std::cout << g1 << std::endl;
  // std::cout << g2 << std::endl;
  // std::cout << g3 << std::endl;
  // std::cout << g4 << std::endl;
  // std::cout << g5 << std::endl;
  // std::cout << g6 << std::endl;


  // int g1 = test->CountGroups();	//3
  // int g2 = test->CountGroups("128");	//6
  // int g3 = test->CountGroups("124"); //6
  // int g4 = test->CountGroups("173");	//10
  // int g5 = test->CountGroups(std::vector<std::string>{ "128", "173" });	//6
  // int g6 = test->CountGroups(std::vector<std::string>{ "128", "124", "173" });	//3


  // std::cout << Print(v1) << std::endl;
  // std::cout << Print(v2) << std::endl;
  // std::cout << Print(v3) << std::endl;
  // std::cout << Print(v4) << std::endl;
  // std::cout << Print(v5) << std::endl;
  // std::cout << Print(v6) << std::endl;
  // std::cout << Print(v7) << std::endl;

  

    // bool v1 = test->AreRelated(1, 2);	//true
  // bool v2 = test->AreRelated(3, 2);	//true
  // bool v3 = test->AreRelated(1, 9);	//false
  // bool v4 = test->AreRelated(1, 2, "128");	//true
  // bool v5 = test->AreRelated(1, 2, "124"); //false
  // bool v6 = test->AreRelated(1, 6, "128");	//true
  // bool v7 = test->AreRelated(1, 6, "124");	//true
  
  // std::vector<int> vec1 = test->GetSteps(1, 1);	//{ 2, 3, 6 }*
  // std::vector<int> vec2 = test->GetSteps(1, 2);	//{ 7, 8 }*
  // std::vector<int> vec3 = test->GetSteps(1, 3);	//{ }
  // //std::vector<int> vec4 = test->GetSteps(9, 1);	//{ }
  // std::vector<int> vec5 = test->GetSteps(2, 3);	//{ 7, 8 }*

  // for (int val : vec1) {
  //   std::cout << val << ", ";
  // }

  // std::cout << std::endl;

  // for (int val : vec2) {
  //   std::cout << val << ", ";
  // }

  // std::cout << std::endl;

  // for (int val : vec3) {
  //   std::cout << val << ", ";
  // }
  // std::cout << std::endl;
  // // for (int val : vec4) {
  // //   std::cout << val << ", ";
  // // }
  // for (int val : vec5) {
  //   std::cout << val << ", ";
  // }
  // std::cout << std::endl;