#include "branched-linked-list.hpp"
#include <iostream>

BLL::BLL() = default;

BLL::BLL(const BLL& to_copy) {
    if (to_copy.head_ == nullptr || to_copy.Size() == 0) {
        head_ = nullptr;
        return;
    }
    int count = 0;
    Node* walk = to_copy.head_;
    while (walk != nullptr) {
        PushBack(walk->data_);
        if (walk->next_bll_ != nullptr) {
            // BLL* list = new BLL(*walk->next_bll_);
            Join (count, walk->next_bll_);
        }
        count += 1;
        walk = walk->next_node_;
    }
}

Node* BLL::PushBack(char dat) {
    Node* walk = head_;
    if (head_ == nullptr) {
        Node* insert = new Node(dat);
        delete head_;
        head_ = nullptr;
        head_ = insert;
        delete insert;
        insert = nullptr;
        return head_;
    }
    while (walk->next_node_ != nullptr) {
        walk = walk->next_node_;
    }
    Node* insert = new Node(dat);
    delete walk->next_node_;
    walk->next_node_ = insert;
    delete insert;
    insert = nullptr;
    return walk->next_node_;
}

std::string BLL::ToString() const {
    std::string result;
    if (head_ == nullptr) {
        return result;
    }
    Node* walk = head_;
    while (walk != nullptr) {
        result += walk->data_;
        if (walk->next_bll_ != nullptr) {
            result += walk->next_bll_->ToString();
        }
        walk = walk->next_node_;
    }
    return result;
}

 BLL& BLL::operator=(const BLL& rhs) {
     if (&rhs == this) {
         return *this;
     }
    this->~BLL();
     int count = 0;
     if (rhs.head_ == nullptr) {
         head_ = nullptr;
         return *this;
     }
        Node* walk = rhs.head_;
        while (walk != nullptr) {
            this->PushBack(walk->data_);
            if (walk->next_bll_ != nullptr) {
                //BLL* list = new BLL(*walk->next_bll_);
                Join(count, walk->next_bll_);
            }
            count += 1;
            walk = walk->next_node_;
    }
    return *this;
 }

size_t BLL::Size() const {
    if (head_ == nullptr) {
        return 0;
    }
    std::string test = this->ToString();
    return test.length();
}

void BLL::Join(size_t idx, BLL* list) {
    BLL* save = this;
    if (idx < 0 || idx >= Size()) {
        throw std::invalid_argument("The index is not valid");
    }
    if (idx == Size() - 1) {
        Node* walking = head_;
        while (walking->next_node_ != nullptr) {
            walking = walking->next_node_;
        }
        if (walking->next_bll_ != nullptr) {
            throw std::invalid_argument("ALREADY A BLL HERE");
        }
        walking->next_bll_ = list;
        return;
    }
    if (idx == 0) {
        if (head_->next_bll_ != nullptr) {
            throw std::invalid_argument("ALREADY HERE BUB");
        } 
        head_->next_bll_ = list;
    }
    size_t cur = 0;
    save->JoinHelper(idx, list, cur);
    if (!(save->IsBLLAcyclic())) {
        throw std::invalid_argument("infinite");
    }
    size_t cur2 = 0;
    JoinHelper(idx, list, cur2);
}

void BLL::JoinHelper(size_t idx, BLL* list, size_t& current) {
    size_t count = current;
    Node* walk = head_;
    while (walk != nullptr) {
        if (walk->next_bll_ != nullptr) {
            count += 1;
            return walk->next_bll_->JoinHelper(idx, list, count);
        }
        if (count == idx) {
            if (walk->next_bll_ != nullptr) {
                throw std::invalid_argument("ALREADY HERE BUB");
            }
            walk->next_bll_ = list;
        }
        walk = walk->next_node_;
        count += 1;
    }
}

void BLL::SetAt(size_t idx, char dat) {
    if (idx >= Size() || idx < 0) {
        throw std::invalid_argument("The index for get is too big");
    }
    Node* walk = head_;
    size_t loc = 0;
    while (walk != nullptr && loc < idx) {
        if (walk->next_bll_ != nullptr) {
            if (loc + walk->next_bll_->Size() >= idx) {
                walk->next_bll_->SetAt(idx - (loc + 1), dat);
                return;
            }
            loc += walk->next_bll_->Size();
        }
        walk = walk->next_node_;
        loc += 1;
    }
    if (walk != nullptr) {
        walk->data_ = dat;
    }
}

// BLL::~BLL() {
//    Clear();
// }

BLL::~BLL() {
   if(head_ != nullptr) {
       Node* cur = head_;
       while (cur != nullptr) {
           Node* next = cur->next_node_;
           delete cur->next_bll_;
           delete cur;
           cur = next;
       }
   }
}

char BLL::GetAt(size_t idx) const {    
    if (idx >= Size() || head_ == nullptr) {
        throw std::invalid_argument("The index for get is too big");
    }
    std::string test = this->ToString();
    return test.at(idx);
}

bool BLL::IsBLLAcyclic() const {
    if (head_ == nullptr) {
        return true;
    }
    Node* slow = head_;
    Node* fast = BllOrNext(head_);
    while (slow != nullptr && fast != nullptr && BllOrNext(fast) != nullptr) {
        if (slow == fast) {
            return false;
        }
        slow = BllOrNext(slow);
        fast = BllOrNext(fast);
        fast = BllOrNext(fast);
    }   
    return true;
}

Node* BLL::BllOrNext(Node* node) const{
    if (node->next_bll_ != nullptr) {
        return node->next_bll_->head_;
    }
    return node->next_node_;
}
