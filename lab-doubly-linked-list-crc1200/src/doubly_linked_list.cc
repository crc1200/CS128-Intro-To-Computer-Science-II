#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <iostream>
using std::endl;
using std::ostream;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;

#include "doubly_linked_list.hpp"
#include "node.hpp"

// Functions provided to you
ostream& operator<<(ostream& os, const DoublyLinkedList& ll) {
  constexpr unsigned int kWidth = 16;
  os << "Doubly Linked List" << endl;
  os << "Head: " << ll.head_ << "\t Tail: " << ll.tail_ << endl;
  os << "Size: " << ll.size_ << endl;
  if (ll.head_ == nullptr) return (os << "Empty" << endl);
  const Node* curr = ll.head_;
  os << "Nodes (accessible from head to tail):" << endl << endl;
  os << setw(kWidth) << setfill(' ') << ' ' << ' ' << Center("prev", kWidth - 1)
     << ' ' << Center("data", kWidth - 1) << ' ' << Center("next", kWidth - 1)
     << endl;
  while (curr != nullptr) {
    ostringstream oss;
    oss << (curr->prev);
    string prev = oss.str();
    oss.str("");
    oss << (curr->next);
    string next = oss.str();
    oss.str("");
    oss << (curr->data);
    string data = oss.str();
    oss.str("");
    oss << curr;
    string address = oss.str();
    os << setw(kWidth) << setfill(' ') << ' ' << '.' << setw(kWidth)
       << setfill('-') << '.' << setw(kWidth) << '.' << setw(kWidth) << '.'
       << endl;
    os << setw(kWidth) << setfill(' ') << Center(address, kWidth - 1) << '|'
       << setw(kWidth - 1) << setfill(' ') << Center(prev, kWidth - 1) << '|'
       << setw(kWidth - 1) << Center(data, kWidth - 1) << '|' << setw(kWidth - 1)
       << Center(next, kWidth - 1) << '|' << endl;
    os << setw(kWidth) << setfill(' ') << ' ' << '\'' << setw(kWidth)
       << setfill('-') << '\'' << setw(kWidth) << '\'' << setw(kWidth) << '\''
       << endl;
    os << endl;
    curr = curr->next;
  }
  return os;
}

std::string Center(const std::string& str, decltype(str.length()) col_width) {
  // quick and easy (but error-prone) implementation
  decltype(str.length()) padl = (col_width - str.length()) / 2;
  decltype(str.length()) padr = (col_width - str.length()) - padl;
  string strf = string(padl, ' ') + str + string(padr, ' ');
  return strf;
}

DoublyLinkedList::DoublyLinkedList(char val): size_(1) {
   Node* node = new Node(val);
   tail_ = node;
   head_ = node;
}

DoublyLinkedList::DoublyLinkedList(const std::vector<char>& values) {
   if (values.empty()) {     
      return;
   }
   for (unsigned int i = 0; i < values.size(); i ++) {
      PushBack(values.at(i));
   }
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& rhs) {
   Node* rhs_cur = rhs.head_;
   while(rhs_cur != nullptr) {
      PushBack(rhs_cur->data);
      rhs_cur = rhs_cur->next;
   }
}
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& rhs) { 
    if (&rhs == this) {
      return *this;
   }
   Node* rhs_cur = rhs.head_;
   while(rhs_cur != nullptr) {
      PushBack(rhs_cur->data);
      rhs_cur = rhs_cur->next;
   }
   return *this;
}
DoublyLinkedList::~DoublyLinkedList() {
   while(head_ != nullptr) {
      Node* tmp = head_->next;
      delete head_;
      head_ = tmp;
   }
   head_ = tail_ = nullptr;
}

char& DoublyLinkedList::Back() {
   if (size_ == 0) {
      throw std::invalid_argument("HEY");
   }
   return tail_->data;
}
char& DoublyLinkedList::Front() {
   if (size_ == 0) {
      throw std::invalid_argument("HEY");
   }
   return head_->data;
}
void DoublyLinkedList::PopBack() {
   if (size_ == 0) {
      throw std::invalid_argument("HEY MAN FIGURE IT OUT");
   } 
   Node* check = tail_->prev;
   if (check != nullptr) {
      check->next = nullptr;
   } else {
      head_ = tail_ = nullptr;
   }
   tail_ = check;
   size_ -= 1;
}


void DoublyLinkedList::PushBack(char val) {
   if (head_ == nullptr) {
      head_ = tail_ = new Node(val);
   } else {
      Node* tmp = new Node (val);
      tail_->next = tmp;
      tmp->prev = tail_;
      tail_ = tmp;
   }
   size_ += 1;
}
void DoublyLinkedList::PushFront(char val) {
   if (head_ == nullptr) {
      head_ = tail_ = new Node(val);
   } else {
   Node* temp = new Node(val);
   head_->prev = temp;
   temp->next = head_;
   head_ = temp;
   }
   size_ += 1;
}

void DoublyLinkedList::InsertAt(size_t idx, char val) {
    if (idx > size_ || idx < 0) {
      throw std::invalid_argument("NO MORE MR NICE GUY");
   }
   if (idx == 0) {
      PushFront(val);
      return;
   } else if (idx == size_) {
      PushBack(val);
      return;
   } else {
      Node* head_loc = head_;
      size_t count = 0;
      while(head_loc != nullptr) {
         if (count == idx) {
            Node* insert = new Node (val);
            head_loc->prev->next = insert;
            insert->prev = head_loc->prev;
            head_loc->prev = insert;
            insert->next = head_loc;
         } 
         head_loc = head_loc->next;
         count += 1;    
      }
   }
   size_ += 1;
}

void DoublyLinkedList::PopFront() {
    if (size_ == 0) {
      throw std::invalid_argument("HEY MAN FIGURE IT OUT");
   } 
   Node* check = head_->next;
   if (check != nullptr) {
      check->prev = nullptr;
   } else {
      head_ = tail_ = nullptr;
   }
   head_ = check;
   size_ -= 1;
}

void DoublyLinkedList::EraseAt(size_t idx) {
   if (size_ == 0 || idx >= size_ || idx < 0) {
      throw std::invalid_argument("NO MORE MR NICE GUY");
   }
   if (idx == 0) {
      PopFront();
      return;
   } else if (idx == size_ - 1) {
      PopBack();
      return;
   } else if (size_ == 1) {
      head_ = tail_ = nullptr;
      return;
   } else {
      Node* head_loc = head_;
      size_t count = 0;
      while(head_ != nullptr) {
         if (count == idx) {
            head_->next->prev = head_->prev;
            head_->prev->next = head_->next;
            delete head_;
            head_ = nullptr;
         } else {
            head_ = head_->next;
            count += 1;    
         }
      }
      head_ = head_loc;
   }
   size_ -= 1;
}

Node* DoublyLinkedList::GetHead() {
   return head_;
}

char& DoublyLinkedList::Find(char val) {
   Node* cur = head_;
   while(cur != nullptr) {
      if (cur->data == val) {
         return cur->data;
      }
      cur = cur->next;
   }
   throw std::invalid_argument("WE DIDNT FIND IT");
}
void DoublyLinkedList::Clear() {
   while(head_ != nullptr) {
      Node* tmp = head_->next;
      delete head_;
      head_ = tmp;
   }
   this->~DoublyLinkedList();
   head_ = tail_ = nullptr;
}

