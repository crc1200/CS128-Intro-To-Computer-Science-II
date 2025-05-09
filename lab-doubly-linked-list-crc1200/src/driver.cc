#include <iostream>
#include <stdexcept>
#include <vector>

#include "doubly_linked_list.hpp"

using namespace std;

int main() {
    DoublyLinkedList hey;
    hey.PushBack('k');
    hey.PushBack('g');
    hey.PushBack('v');
    hey.PushBack('d');
    hey.PushBack('b');
    

    std::cout << "BEFORE" << std::endl;

    Node* print_before = hey.GetHead();
    while(print_before) {
        std::cout <<print_before->data <<std::endl;
        print_before = print_before->next;
    }

    hey.InsertAt(2, 'X');

    std::cout << "After" << std::endl;

    Node* print_after = hey.GetHead();
    while(print_after) {
        std::cout <<print_after->data <<std::endl;
        print_after = print_after->next;
    }
}
