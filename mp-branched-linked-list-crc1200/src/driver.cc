#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('h');
  first->PushBack('%');
  first->PushBack('h');
  first->PushBack('%');
  first->PushBack('%');

  std::cout << first->ToString() << std::endl; // hi
  std::cout << first->Size() << std::endl; // 2

  // /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');

  first->Join(0,second);
  std::cout << first->ToString() << std::endl; // hi


  std::cout << second->ToString() << std::endl; // i!@
  std::cout << second->Size() << std::endl; // 3

  // /////////////////////////////////////

  std::cout << first->ToString() << std::endl; // hii!@
  std::cout << first->Size() << std::endl; // 5

  std::cout << second->ToString() << std::endl; // i!@
  std::cout << second->Size() << std::endl; // 3

  /////////////////////////////////////

  BLL* third = new BLL();
  third->PushBack('L');
  third->PushBack('L');
  third->PushBack('L');


  first->Join(1, third);

  std::cout << "AFTER 3 " << std::endl;

  std::cout << first->ToString() << std::endl;
  std::cout << first->Size() << std::endl; 

  first->SetAt(5, '#');
  std::cout << first->ToString() << std::endl;

  BLL* copy = new BLL(*first);
  std::cout << "COPY TEST" << copy->ToString() << std::endl;


  BLL* deleter = new BLL();
  deleter->PushBack('p');
  deleter->PushBack('p');
  deleter->PushBack('p');

  BLL* other = new BLL();
  other->PushBack('p');
  other->PushBack('p');
  other->PushBack('p');

  //BLL* empty = new BLL();

  std::cout << first->Size() << std::endl;
  first->Join(6,other);

  std::cout << "Equal before " << deleter->ToString() << std::endl;

  deleter = first;



  // std::cout << "Equal after " << std::endl;
  // std::cout << deleter->ToString() << std::endl;
  // std::cout << first->ToString() << std::endl;

  // first->~BLL();
  // second->~BLL();
  // third->~BLL();
  // deleter->~BLL();
  // other->~BLL();

  return 0;
}
