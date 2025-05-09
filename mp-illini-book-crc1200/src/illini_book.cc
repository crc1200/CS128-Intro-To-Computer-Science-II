#include "illini_book.hpp"
#include "utilities.hpp"
#include<fstream>
#include<queue>
#include<string>
#include<vector>
#include<list>
#include<set>
#include<map>

//Helper Functions
bool IlliniBook::Find(const std::vector<int> &vec, const int &val) const{
    for (int num : vec) {
        if (num == val) {
            return true;
        }
    }
    return false;
}

bool IlliniBook::FindString(const std::vector<std::string> &vec, const std::string &val) const{
    for (const std::string &num : vec) {
        if (num == val) {
            return true;
        }
    }
    return false;
}

bool IlliniBook::AreEqual(const std::vector<int> &v1, const std::vector<int> &v2) const {
    if (v1.size() != v2.size()) {
        return false;
    }
    for (int vals : v1) {
        if (!Find(v2, vals)) {
            return false;
        }
    }
    return true;
}

std::map<int, std::vector<std::pair<int, std::string>>> IlliniBook::GetGraph() {
    return graph_;
}

std::string Print(bool input) {
    if (input) {
    return "True";
    } 
    return "False";
}

bool IlliniBook::VecContains(const std::vector<std::vector<int>> &big, const std::vector<int> &v2) const {
    for (const std::vector<int> &vals : big) {
        if (AreEqual(vals, v2)) {
            return true;
        }
    }
    return false;
}

//Actual Functions

IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::vector<int> names;
    std::map<std::pair<int,int>, std::string> pairs;
    std::ifstream people {people_fpath};
    std::ifstream relations {relations_fpath};
    for(std::string line; std::getline(people, line); line = "") {
        names.push_back(std::stoi(line));
    }
    for(std::string line; std::getline(relations, line); line = "") {
        std::vector<std::string> vals = utilities::Split(line, ',');
        std::pair<int, int> partner;
        partner.first = std::stoi(vals[0]);
        partner.second = std::stoi(vals[1]);
        relations_.push_back(vals[2]);
        pairs.insert({partner, vals[2]});
    }
    for (int i : names) {
        std::vector<std::pair<int, std::string>> name_rel;
        for(auto iter = pairs.begin(); iter != pairs.end(); ++iter) {
            auto keys =  iter->first;
            std::string rel = iter->second;
            if (keys.first == i) {
                std::pair<int, std::string> insert_pair;
                insert_pair.first = keys.second;
                insert_pair.second = rel;
                name_rel.push_back(insert_pair);
            } else if (keys.second == i) {
                std::pair<int, std::string> insert_pair;
                insert_pair.first = keys.first;
                insert_pair.second = rel;
                name_rel.push_back(insert_pair);
            }
        }
        graph_.insert({i, name_rel});
        size_ += 1;
    }
}

IlliniBook::~IlliniBook() = default;

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    std::vector<int> vals = BFS(uin_1);
    return Find(vals, uin_2);
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    if (!FindString(relations_, relationship)) {
        return false;
    }
    std::vector<int> vals = BFSRelations(uin_1, relationship);
    return Find(vals, uin_2);
}
    
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
     if (!AreRelated(uin_1, uin_2)) {
        return -1;
    }
    std::queue<int> q;
    std::vector<int> visit;
    q.push(uin_1);
    //int *array = new int[size_];
    std::map<int, int> dd;
    dd.insert({uin_1, 0});
    visit.push_back(uin_1);
    //array[uin_1] = 0;
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        std::vector<std::pair<int, std::string>> close = graph_.at(front);
        for (const std::pair<int, std::string> &val : close) {
            if (!Find(visit, val.first)) {
                visit.push_back(val.first);
                q.push(val.first);
                dd.insert({val.first, 0});
                dd.at(val.first) = dd.at(front) + 1;
                //array[val.first] = array[front] + 1;
            }
        }
    }
    // int result = array[uin_2];
    // delete [] array;
    // array = nullptr;
    // return result;
    return dd.at(uin_2);
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    if (!AreRelated(uin_1, uin_2, relationship)) {
        return -1;
    }
    if (!FindString(relations_, relationship)) {
        return size_;
    }
    std::queue<int> q;
    std::vector<int> visit;

    std::map<int, int> dd;
    q.push(uin_1);
    //int *array = new int[size_];
    visit.push_back(uin_1);
    //array[uin_1] = 0;
    dd.insert({uin_1, 0});
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        std::vector<std::pair<int, std::string>> close = graph_.at(front);
        for (const std::pair<int, std::string> &val : close) {
            if (!Find(visit,val.first) && val.second == relationship) {
                visit.push_back(val.first);
                q.push(val.first);
                dd.insert({val.first, 0});
                dd.at(val.first) = dd.at(front) + 1;
                //array[val.first] = array[front] + 1;
            }
        }
    }
    // int result = array[uin_2];
    // delete [] array;
    // array = nullptr;
    // return result;
    return dd.at(uin_2);
}

size_t IlliniBook::CountGroups() const {
    std::vector<std::vector<int>> checks;
    for (const auto& [k, x] : graph_) {
        std::vector<int> inner_rel = BFS(k);
        if (!VecContains(checks, inner_rel)) {
            checks.push_back(inner_rel);
        }
    }
    return checks.size();
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::vector<std::vector<int>> checks;
    for (const auto& [k, x] : graph_) {
        std::vector<int> inner_rel = BFSRelations(k, relationship);
        if (!VecContains(checks, inner_rel)) {
            checks.push_back(inner_rel);
        }
    }
    return checks.size();
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::vector<std::vector<int>> checks;
    for (const auto& [k, x] : graph_) {
        std::vector<int> inner_rel = BFSVec(k, relationships);
        if (!VecContains(checks, inner_rel)) {
            checks.push_back(inner_rel);
        }
    }
    return checks.size();
}

std::vector<int> IlliniBook::BFS(int uin_1) const {
    std::queue<int> q;
    std::vector<int> visit;
    std::vector<int> result;
    result.push_back(uin_1);
    q.push(uin_1);
    visit.push_back(uin_1);
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        std::vector<std::pair<int, std::string>> close = graph_.at(front);
        for (const std::pair<int, std::string> &val : close) {
            if (!Find(visit, val.first)) {
                visit.push_back(val.first);
                q.push(val.first);
                result.push_back(val.first);
            }
        }
    }
    return result;
}

std::vector<int> IlliniBook::BFSRelations(int uin_1, const std::string &relationship) const {
    std::queue<int> q;
    std::vector<int> visit;
    std::vector<int> result;
    result.push_back(uin_1);
    q.push(uin_1);
    visit.push_back(uin_1);
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        std::vector<std::pair<int, std::string>> close = graph_.at(front);
        for (const std::pair<int, std::string> &val : close) {
                if (!Find(visit, val.first) && val.second == relationship) {
                visit.push_back(val.first);
                q.push(val.first);
                result.push_back(val.first);
            }
        }
    }
    return result;
}

std::vector<int> IlliniBook::BFSVec(int uin_1, const std::vector<std::string> &rel) const {
    std::queue<int> q;
    std::vector<int> visit;
    std::vector<int> result;
    result.push_back(uin_1);
    q.push(uin_1);
    visit.push_back(uin_1);
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        std::vector<std::pair<int, std::string>> close = graph_.at(front);
        for (std::pair<int, std::string> &val : close) {
                if (!Find(visit, val.first) && FindString(rel, val.second)) {
                visit.push_back(val.first);
                q.push(val.first);
                result.push_back(val.first);
            }
        }
    }
    return result;
}

std::vector<int> IlliniBook::GetSteps(int uin_1, int n) const {
   std::queue<int> q;
   std::vector<int> visit;
   q.push(uin_1);
   std::map<int, int> dd;
   visit.push_back(uin_1);
   dd.insert({uin_1, 0});
   while(!q.empty()) {
       int front = q.front();
       q.pop();
       std::vector<std::pair<int, std::string>> close = graph_.at(front);
       for (const std::pair<int, std::string> &val : close) {
           if (!Find(visit, val.first)) {
               visit.push_back(val.first);
               q.push(val.first);
               dd.insert({val.first, 0});
               dd.at(val.first) = dd.at(front) + 1;
            }
       }
   }
   std::vector<int> rs;
   for (const auto& [k, x] : dd) {
       if (x == n) {
           rs.push_back(k);
       }
    }
   return rs;
}
