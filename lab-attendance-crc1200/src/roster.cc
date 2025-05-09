#include <iostream>

#include "roster.hpp"

Roster::Roster(const Student& student) {
  auto *rost = new RosterEntry(student, nullptr);
  head_ = std::unique_ptr<RosterEntry>(rost);
}

void Roster::AddStudent(const Student& student) {
  if (head_ == nullptr) {
    auto *insert = new RosterEntry(student, nullptr);
    head_ = std::unique_ptr<RosterEntry>(insert);
    return;
  }
  if (head_->student > student) {
    auto *insert = new RosterEntry(student, head_.release());
    auto new_un = std::unique_ptr<RosterEntry>(insert);
    head_.swap(new_un);
    return;
  }
  auto *walk = head_.get();
  while (walk != nullptr && walk->next != nullptr && walk->next->student < student) {
    walk = walk->next.get();
  }
  auto *insert = new RosterEntry(student, walk->next.release());
  auto new_un = std::unique_ptr<RosterEntry>(insert);
  walk->next = std::move(new_un);
}

Roster::Iterator Roster::begin() const { 
  return Iterator(head_.get()); 
}

Roster::Iterator Roster::end() const { 
  return Iterator(); 
}
