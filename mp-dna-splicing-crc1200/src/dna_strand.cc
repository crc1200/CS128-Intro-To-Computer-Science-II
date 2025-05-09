#include "dna_strand.hpp"
#include <stdexcept>

Node* DNAstrand::GetHead() {
    return head_;
}

Node* DNAstrand::GetTail() {
    return tail_;
}

void DNAstrand::PushBack(char data) {
    if (head_ == nullptr) {
    head_ = tail_ = new Node(data);
  } else {
    Node* tmp = new Node(data);
    tail_->next = tmp;
    tail_ = tmp;
  }
}

void DNAstrand::NodePush(Node*& node) {
    if (head_ == nullptr) {
    head_ = tail_ = node;
  } else {
    tail_->next = node;
    tail_ = nullptr;
    tail_ = node;
  }
}
int DNAstrand::StrLen(const char* c_str) {
    int count = 0;
    while(c_str[count] != '\0') {
        count += 1;
    }
    return count;
}

void DNAstrand::FindVals(const char* &pattern, int &fin_count, int &end_count, int &count, int pattern_size) {
    Node* start = head_;
    while (start != nullptr) {
        if (start->data == pattern[0]) {
            Node* cur = start;
            int i = 0;
            while(cur != nullptr && i < pattern_size && cur->data == pattern[i]) {
                cur = cur->next;
                i += 1;
                if (i == pattern_size) {
                    fin_count = count;
                    end_count = fin_count + pattern_size + 1;
                }
            }
        }
        start = start->next;
        count += 1;
    }
    delete start;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {

    if (StrLen(pattern) == 0 || to_splice_in.head_ == nullptr || &to_splice_in == this) { 
        return; 
    }

    int count = 0;
    int fin_count = -1;
    int end_count = 0;
    int front_count = 0;

    FindVals(pattern, fin_count, end_count, count, StrLen(pattern));

    if (fin_count == -1) { 
        throw std::invalid_argument("Error"); 
    }

    DNAstrand strand;
    while (head_ != nullptr && front_count < fin_count) {
        strand.NodePush(head_);
        Node* test = head_;
        head_ = head_->next;
        test->next = nullptr;   
        front_count += 1;
    }

    while(to_splice_in.head_ != nullptr) {
        strand.NodePush(to_splice_in.head_);
        Node* test = to_splice_in.head_;
        to_splice_in.head_ = to_splice_in.head_->next;
        test->next = nullptr;   
    }

    int other_guy = fin_count;

    while(head_ != nullptr && other_guy < end_count - 1) {
        Node* test = head_->next;
        delete head_;
        head_ = nullptr;
        head_ = test;
        other_guy += 1;
    }

    while(head_ != nullptr) {
        strand.NodePush(head_);
        Node* test = head_;
        head_ = head_->next;
        test->next = nullptr;   
    }

    this->~DNAstrand();

    while(strand.head_ != nullptr) {
        NodePush(strand.head_);
        Node* test = strand.head_;
        strand.head_ = strand.head_->next;
        test->next = nullptr;
    }
    
 }

DNAstrand::~DNAstrand() {
    while (head_ != nullptr) {
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }
}

