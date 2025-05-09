#include <iostream>

#include "circular-linked-list.hpp"

int main() {

    CircularLinkedList<int> list;
    list.InsertInOrder(10);
    list.InsertInOrder(15);
    list.InsertInOrder(13);
    list.InsertInOrder(11);
    list.InsertInOrder(100);
    list.InsertInOrder(-100);
    list.InsertInOrder(13420);
    list.InsertInOrder(2);


    std::cout << list << std::endl;
    

    
}
