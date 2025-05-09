#include <iostream>

#include "dna_strand.hpp"

int main() {
    

    DNAstrand test2;
    test2.PushBack('c');
    test2.PushBack('t');
    test2.PushBack('a');
    test2.PushBack('t');
    test2.PushBack('a');

    DNAstrand test3;
    test3.PushBack('c');
    test3.PushBack('t');
    test3.PushBack('a');
    test3.PushBack('a');
    test3.PushBack('t');
    test3.PushBack('t');
    test3.PushBack('a');
    test3.PushBack('c');
    test3.PushBack('g');
    test3.PushBack('g');
    test3.PushBack('t');
    test3.PushBack('t');
    test3.PushBack('a');
    test3.PushBack('h');
    test3.PushBack('y');
    test3.PushBack('g');
    test3.PushBack('g');
    test3.PushBack('g');
    test3.PushBack('g');


    // DNAstrand to_insert_2;
    // to_insert_2.PushBack('t');
    // to_insert_2.PushBack('g');
    // to_insert_2.PushBack('a');


    

    // DNAstrand to_insert3;
    // to_insert3.PushBack('p');
    // to_insert3.PushBack('e');
    // to_insert3.PushBack('n');

    //char* pattern = new char[7];
    
    //char pattern2[] = "ta";
    //char pattern3[] =  "tta";
   
   DNAstrand test;
    test.PushBack('c');
    test.PushBack('t');
    test.PushBack('g');
    test.PushBack('a');
    test.PushBack('a');
    test.PushBack('t');
    test.PushBack('t');
    test.PushBack('c');
    test.PushBack('g');

    char pattern[] = "gaattc";
    //char empty[] = "";

    DNAstrand to_insert;
    to_insert.PushBack('t');
    to_insert.PushBack('g');
    to_insert.PushBack('a');
    to_insert.PushBack('t');
    to_insert.PushBack('c');

    test.SpliceIn(pattern, to_insert);
    std::cout << std::endl;

    //test3.SpliceIn(pattern3,to_insert3);

    std::cout << "After" << std::endl;

    Node* help = test.GetHead();
    while (help != nullptr) {
        std::cout << help->data << " ";
        help = help->next;
    }
    std::cout<<std::endl;
    return 0;
}