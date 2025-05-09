#include "solution.hpp"

#include <iostream>
#include <queue>
#include <map>
#include<vector>
#include <queue>

Solution::Solution(const std::vector<std::pair<std::string, std::string>>& prerequisites) {
  for (auto items : prerequisites) {
      adj_[items.first].push_back(items.second);
  }
}

int Solution::Solve(const std::string& start, const std::string& dest) {
    std::queue<std::string> q;
    std::vector<std::string> visit;
    q.push(start);
    std::map<std::string, int> dd;
    dd.insert({start, 0});
    visit.push_back(start);
    while(!q.empty()) {
        std::string front = q.front();
        q.pop();
        if (GetAdjacencyList(front).size() < INT32_MAX) {
            for (const auto &val : GetAdjacencyList(front)) {
                if (!FindString(visit, val)) {
                    visit.push_back(val);
                    q.push(val);
                    dd[val] = dd[front] + 1;
                }
            }
        }
    }
    if (dd[dest] == 0 && dest != start) {
        return -1;
    }
    return dd.at(dest);
}

bool Solution::FindString(const std::vector<std::string> &vec, const std::string &val) {
    for (const std::string &num : vec) {
        if (num == val) {
            return true;
        }
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////
//Provide function definitions (uncomment to use!)                          //
/////////////////////////////////////////////////////////////////////////////

// void Solution::AddVertex(const std::string& vertex) {
//   if (VertexInGraph(vertex))
//     throw std::runtime_error("vertex already in graph.");
//   adj_.insert(std::pair(vertex, std::list<std::string>()));
// }

std::list<std::string>& Solution::GetAdjacencyList(const std::string& vertex) {
  return adj_.find(vertex)->second;
}

bool Solution::VertexInGraph(const std::string vertex) {
  if (adj_.find(vertex) != adj_.end())
    return true;
  else
    return false;
}

std::ostream& operator<<(std::ostream& os, const Solution& sol) {
  os << "Contents:" << std::endl;

  for (const auto& pair : sol.adj_) {
    os << "  " << pair.first << ": [ ";

    for (const auto& list_entry : pair.second) {
      os << list_entry << " ";
    }

    os << "]" << std::endl;
  }

  return os;
}