#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <map>
#include <list>


class IlliniBook {
public:

  //Helper


  bool Find(const std::vector<int> &vec, const int &val) const;
  bool FindString(const std::vector<std::string> &vec, const std::string &val) const;
  bool AreEqual(const std::vector<int> &v1, const std::vector<int> &v2) const;
  bool VecContains(const std::vector<std::vector<int>> &big, const std::vector<int> &v2) const;
  std::map<int, std::vector<std::pair<int, std::string>>> GetGraph();


  //Actual Functions

  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  ~IlliniBook();
  IlliniBook &operator=(const IlliniBook &rhs) = delete;

  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;

  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  
  std::vector<int> GetSteps(int uin, int n) const;

  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;
  size_t CountGroups() const;

  std::vector<int> BFS(int uin_1) const;
  int BFSFind(int uin_1, int uin_2) const;
  std::vector<int> BFSVec(int uin_1, const std::vector<std::string> &rel) const;
  std::vector<int> BFSRelations(int uin_1, const std::string &relationship) const;
  std::vector<int> BFSDistance(int uin_1, int n) const;

private:
  std::map<int, std::vector<std::pair<int, std::string>>> graph_;
  size_t size_ = 0;
  std::vector<std::string> relations_;

};

std::string Print(bool input);


#endif
