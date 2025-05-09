#include "cord-utilities.hpp"

std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord, std::shared_ptr<Cord> right_cord) {
  if (!left_cord->IsValidCord() || !right_cord->IsValidCord()) {
    throw std::invalid_argument("This is wrong");
  }
  auto *result = new Cord(left_cord, right_cord);
  auto share_res = std::shared_ptr<Cord>(result);
  if (!share_res->IsValidCord()) {
    throw std::invalid_argument("no way jose");
  }
  left_cord = nullptr;
  right_cord = nullptr;
  return share_res;
}

void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords) {
  std::map<std::string, std::shared_ptr<Cord>> map;
  for (std::shared_ptr<Cord> &cord : cords) {
    ReduceHelper(cord, map);
  } 
}

void ReduceHelper(std::shared_ptr<Cord> &cord, std::map<std::string, std::shared_ptr<Cord>> &result) {
  if (result.count(cord->ToString()) != 0u) {
    cord = result.at(cord->ToString());
  } else {
    result.insert({cord->ToString(), cord});
  }
  if (cord->GetLeft() != nullptr) {
    ReduceHelper(cord->left_, result);
  }
  if (cord->GetRight() != nullptr) {
    ReduceHelper(cord->right_, result);
  }
}