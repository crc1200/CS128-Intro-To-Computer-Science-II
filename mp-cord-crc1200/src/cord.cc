s#include "cord.hpp"

#include "cord-utilities.hpp"
#include <stdexcept>

Cord::Cord(const std::string& dat) {
  data_ = dat;
  length_ = dat.length();
}

Cord::Cord(const std::shared_ptr<Cord>& left_cord, const std::shared_ptr<Cord>& right_cord): left_(left_cord), right_(right_cord) {
  length_ = left_cord->Length() + right_cord->Length();
}

size_t Cord::Length() const { return length_; }

std::shared_ptr<Cord> Cord::GetLeft() const { return left_; }

std::shared_ptr<Cord> Cord::GetRight() const { return right_; }

const std::string& Cord::GetData() const { return data_; }

std::string Cord::ToString() const {
    std::string result;
    if (GetLeft() == nullptr && GetRight() == nullptr) {
        return data_;
    }
    if (GetLeft() != nullptr) {
      result += GetLeft()->ToString();
    }
    if (GetRight() != nullptr) {
      result += GetRight()->ToString();
    }
    return result;
}

std::shared_ptr<Cord> Cord::SubString(size_t lower_idx, size_t upper_idx) {
  if (lower_idx < 0 || upper_idx > length_) {
    throw std::invalid_argument("invalid");
  }
  if (length_ == (upper_idx - lower_idx)) {
    return std::shared_ptr<Cord>(this->shared_from_this());
  }
  if (left_== nullptr && right_ == nullptr) {      //Leaf Node
    return std::make_shared<Cord>(data_.substr(lower_idx, (upper_idx - lower_idx)));
  }
  std::shared_ptr<Cord> result;
  if (left_->length_ >= lower_idx) {
    if (left_->length_ >= upper_idx) {
      result = left_->SubString(lower_idx, upper_idx);
    } else {
        result = ConcatCords(left_->SubString(lower_idx, left_->length_), right_->SubString(0, upper_idx - left_->length_));
    }
  } else {
    result = right_->SubString(lower_idx - left_->length_, upper_idx - left_->length_);
  }
  return result;
}

bool Cord::FindBool(const std::string &word) {
  if (GetLeft() == nullptr && GetRight() == nullptr) {
    if (ToString().find(word) != std::string::npos) {
      return true;
    }
  }
  if (GetLeft() != nullptr) { return GetLeft()->FindBool(word); }
  if (GetRight() != nullptr) { return GetRight()->FindBool(word); }
  return false;
}


char Cord::At(size_t idx) const {
  if (idx < 0 || idx >= length_) {
    throw std::invalid_argument("This length is way too big or too small");
  }
  if(GetLeft() == nullptr && GetRight() == nullptr) {
    return data_[idx];
  }
  size_t size = 0;
  if (left_ != nullptr) {
    size = GetLeft()->Length();
    if (GetLeft()->Length() > idx) {
      return GetLeft()->At(idx);
    }
  }
  if (right_ != nullptr) {
    size_t value = GetRight()->Length();
    if (value > idx - size) {
      return GetRight()->At(idx - size);
    }
  }
  return 'm';
}

bool Cord::IsValidCord() const {
  if (GetData().length() != 0 && (GetLeft() != nullptr || GetRight() != nullptr)) {
    return false;
  }
  if (GetLeft() != nullptr && GetRight() != nullptr) {
    if (Length() != (GetLeft()->Length() + GetRight()->Length())) {
      return false;
    }
  }
  return true;
}






    



