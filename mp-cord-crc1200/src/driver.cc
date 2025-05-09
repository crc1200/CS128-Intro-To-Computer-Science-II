#include <cassert>
#include <iostream>

#include "cord-utilities.hpp"
#include "cord.hpp"

int main() {

  // auto cord4 = std::make_shared<Cord>("8 is awe");
  // auto cord5 = std::make_shared<Cord>("some");
  // auto cord2 = std::make_shared<Cord>("CS12");
  // auto cord3 =ConcatCords(cord4,cord5);
  // auto cord1 = ConcatCords(cord2, cord3);

  
  // auto a1 = std::make_shared<Cord>("sse");
  // auto a2 = std::make_shared<Cord>("ssion");
  // auto a3 = std::make_shared<Cord>("po");
  // auto a4 = std::make_shared<Cord>("pre");
  // auto a5 = ConcatCords(a1,a2);
  // auto a6 = ConcatCords(a3,a5);
  // auto a = ConcatCords(a4, a6);

  // auto b1 = std::make_shared<Cord>("nonpo");
  // auto b2 = std::make_shared<Cord>("ssession");
  // auto b = ConcatCords(b1,b2);

  // auto c = std::make_shared<Cord>("possession");

  // auto d1 = std::make_shared<Cord>("fe");
  // auto d2 = std::make_shared<Cord>("ssion");
  // auto d3 = ConcatCords(d1,d2);
  // auto d4 = std::make_shared<Cord>("pro");
  // auto d = ConcatCords(d4,d3);

  // cs128::ReferenceList<std::shared_ptr<Cord>> cords = {a, b, c, d};

  // ReduceCords(cords);

  // std::cout << b->ToString() << std::endl;
  // std::cout << b->GetLeft()->ToString() << std::endl;
  // std::cout << b->GetRight()->GetRight()->ToString() << std::endl;
  // std::cout << b->GetRight()->GetLeft()->ToString() << std::endl;

  // std::cout << c->ToString() << std::endl;
  // std::cout << c->GetLeft()->ToString() << std::endl;
  // std::cout << c->GetRight()->GetLeft()->ToString() << std::endl;

  //std::cout << d->ToString() << std::endl;
  //std::cout << d->GetLeft()->ToString() << std::endl;
  // std::cout << b->GetRight() << std::endl;
  // std::cout << a5 << std::endl;
  //std::cout << d->GetRight()->GetRight()->ToString() << std::endl;

  auto cord1 = std::make_shared<Cord>("he");
  auto cord2 = std::make_shared<Cord>("llo");
  auto cord3 = std::make_shared<Cord>("wor");
  auto cord4 = std::make_shared<Cord>("ld");

  auto cord5 = ConcatCords(cord1, cord2);
  auto cord6 = ConcatCords(cord3,cord4);

  auto cord_fin = ConcatCords(cord5,cord6);




  // auto checker12 = cord1->SubString(0, 1);
  // std::cout << "Answer 12 " << checker12->ToString() << std::endl;
  // std::cout << checker12->GetLeft()->ToString() << std::endl;
  // std::cout << checker12->GetRight()->ToString() << std::endl;
  // std::cout << "Answer 12 " << checker12->Length() << std::endl;


  // auto checker1 = cord5->SubString(0, 5);
  // std::cout << "Answer 12 " << checker1->ToString() << std::endl;
  // std::cout << "Answer 12 " << checker1->GetLeft()->ToString() << std::endl;
  // std::cout << "Answer 12 " << checker1->GetRight()->ToString() << std::endl;




  auto checker1 = cord_fin->SubString(0, 5);
  std::cout << "Answer 12 " << checker1->ToString() << std::endl;
  std::cout << "Answer 12 " << checker1->GetLeft()->ToString() << std::endl;
  std::cout << "Answer 12 " << checker1->GetRight()->ToString() << std::endl;


  

  // auto checker12 = a->SubString(0, 12);
  // std::cout << "Answer 12 " << checker12->ToString() << std::endl;
  // std::cout << checker12->GetLeft()->ToString() << std::endl;
  // std::cout << checker12->GetRight()->ToString() << std::endl;
  // std::cout << "Answer 12 " << checker12->Length() << std::endl;
  


  // auto checker = cord_fin->SubString(2, 9);
  // std::cout << "Answer 1 " << checker->ToString() << std::endl;
  // std::cout << "Answer 1 " << checker->Length() << std::endl;
  // std::cout << checker->GetLeft()->ToString() << std::endl;
  // std::cout << checker->GetRight()->GetLeft()->ToString() << std::endl;
  // std::cout << checker->GetRight()->GetRight()->ToString() << std::endl;


  //auto checker9 = cord_fin->SubString(0, 5);
  // std::cout << "Answer 9 " << checker9->ToString() << std::endl;

  // auto checker2 = cord_fin->SubString(1, 7);
  // std::cout << "Answer 2 " << checker2->ToString() << std::endl;
  // std::cout << "Answer 2 " << checker2->Length() << std::endl;

  // auto checker3 = cord_fin->SubString(2, 7);
  // std::cout << "Answer 3 " << checker3->ToString() << std::endl;
  // std::cout << "Answer 3 " << checker3->Length() << std::endl;

  // auto checker4 = cord_fin->SubString(0, 1);
  // std::cout << "Answer 4 " << checker4->ToString() << std::endl;
  // std::cout << "Answer 4 " << checker4->Length() << std::endl;

  // auto checker5 = cord_fin->SubString(3, 6);
  // std::cout << "Answer 5 " << checker5->ToString() << std::endl;
  // std::cout << "Answer 5 " << checker5->Length() << std::endl;

  // auto checker10 = cord_fin->SubString(3, 5);
  // std::cout << "Answer 10 " << checker10->ToString() << std::endl;
  // std::cout << "Answer 10 " << checker10->Length() << std::endl;
  // std::cout << checker10->ToString()<< std::endl;
  // std::cout << checker10->ToString() << std::endl;


  // auto checker11 = cord1->SubString(0, 1);
  // std::cout << "Answer 10 " << checker11->ToString() << std::endl;
  // std::cout << "Answer 10 " << checker11->Length() << std::endl;



  
  return 0;
}
