#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL();
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;

  Node* BllOrNext(Node* node) const;

  void SetAt(size_t idx, char dat);
  void SetHelper(size_t idx, char dat, size_t& current);



  void Join(size_t idx, BLL* list);
  void JoinHelper(size_t idx, BLL* list, size_t& current);

  std::string ToString() const;
  size_t Size() const;
  void Clear();
  void Clear(Node* node);

private:
  Node* head_ = nullptr;
  bool IsBLLAcyclic() const;
};

#endif
