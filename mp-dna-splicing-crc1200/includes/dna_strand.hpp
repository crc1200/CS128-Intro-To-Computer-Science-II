#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  int StrLen(const char* c_str);
  void PushBack(char data);
  Node* GetHead();
  Node* GetTail();
  void FindVals(const char* &pattern, int &fin_count, int &end_count, int &count, int pattern_size);
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void End(int back, int end_count, DNAstrand &result);
  void NodePush(Node*& node);



private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif