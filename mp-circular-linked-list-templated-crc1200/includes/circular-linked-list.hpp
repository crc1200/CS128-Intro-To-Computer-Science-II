#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();
  void Ascending(Node<T>* walker1, const T& data);
  void Descending(Node<T>* walker1, const T& data);
  void InsertInOrder(const T& data);
  void Reverse();
  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr) {
    node_order_ = Order::kASC;
    head_ = tail_ = nullptr;
    return;
  } 
  if (source.head_->next == nullptr) {
    auto insert = new Node<T>(source.head_->data);
    head_ = tail_ = insert;
    tail_->next = head_;
  } else {
  node_order_ = source.node_order_;
  auto walk = source.head_;
  while (walk->next != source.head_) {
    this->InsertInOrder(walk->data);
    walk = walk->next;
  }
  this->InsertInOrder(source.tail_->data);
  tail_->next = head_;
  }
}

template <typename T>
void CircularLinkedList<T>::Descending(Node<T>* walker1, const T& data) {
  if (walker1->next == head_) {    //only one element
        if (walker1->data > data) {       //inserting smaller element
          head_->next = tail_ = new Node<T>(data);
          walker1->next->next = tail_->next = head_;
        } else {
          auto h = head_;
          head_ = new Node<T>(data);
          head_->next = h;
          tail_->next = head_;
        }
        return;
    }
      auto walker = head_;
      while (walker->next != head_ && walker->next->data >= data) {
        walker = walker->next;
      }
      if (walker == head_) {
          if (head_->data >= data) {   //Fist element smaller than insertion but insertion smaller than next
            auto head_next = head_->next;
            head_->next = new Node<T>(data);
            head_->next->next = head_next;
          } else {
            auto h = head_;
            head_ = new Node<T>(data);
            head_->next = h;
            tail_->next = head_;
          }
      } else if (walker->next == head_) {
          walker->next = tail_ = new Node<T>(data);;
          tail_->next = head_;
      } else {
          auto next = walker->next;
          walker->next  = new Node<T>(data);
          walker->next->next = next;
      }
}

template <typename T>
void CircularLinkedList<T>::Ascending(Node<T>* walker1, const T& data) {
  if (node_order_ == Order::kASC) { //ascending order
      if (walker1->next == head_) {    //only one element
        if (walker1->data <= data) {       //inserting bigger element
          head_->next = tail_ = new Node<T>(data);
          walker1->next->next = tail_->next = head_;
        } else {
          auto h = head_;
          head_ = new Node<T>(data);
          head_->next = h;
          tail_->next = head_;
        }
        return;
      }
      auto walker = head_;
      while(walker->next != head_ && walker->next->data <= data) {
        walker = walker->next;
      }
      if (walker == head_) {
          if (head_->data <= data) {   //Fist element smaller than insertion but insertion smaller than next
            auto head_next = head_->next;
            head_->next = new Node<T>(data);
            head_->next->next = head_next;
          } else {
            auto h = head_;
            head_ = new Node<T>(data);
            head_->next = h;
            tail_->next = head_;
          }
      } else if (walker->next == head_) {
          walker->next = tail_ = new Node<T>(data);
          tail_->next = head_;
      } else {
          auto next = walker->next;
          walker->next  = new Node<T>(data);
          walker->next->next = next;
      }
  } 

}
  
template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
if (head_ == nullptr) {
    return;
  }
  tail_->next = nullptr;
  while(head_ != nullptr) {
      Node<T>* tmp = head_->next;
      delete head_;
      head_ = tmp;
   }
   head_ = tail_ = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {     //empty list
    head_ = tail_ = new Node<T>(data);
    tail_->next = head_;
    return;
  }
  auto walker1 = head_;
  if (node_order_ == Order::kASC) { //ascending order
    Ascending(walker1, data);
  } else {  
    Descending(walker1,data);
    }
}

template <typename T> 
void CircularLinkedList<T>::Reverse() {
  //toggle orders
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr) {
        return;
  }
  auto prev = tail_->next;
  auto current = head_->next;
  Node<T>* next = nullptr;
  while (current != head_) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
  }
  //fix the end fellas
  tail_ = current;
  tail_->next = prev;
  head_ = prev;
}

template <typename T> 
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (&source == this) {
    return *this;
  }
  this->~CircularLinkedList();
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    node_order_ = Order::kASC;
    head_ = nullptr;
    tail_ = nullptr;
    return *this;
  }
  if (source.head_->next == nullptr) {
    auto insert = new Node<T>(source.head_->data);
    head_ = tail_ = insert;
    tail_->next = head_;
    return *this;
  }
  auto walk = source.head_;
  while (walk->next != source.head_) {
    this->InsertInOrder(walk->data);
    walk = walk->next;
  }
  this->InsertInOrder(source.tail_->data);
  tail_->next = head_;
  return *this;
}

#endif

