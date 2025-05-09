#include "news_agent.hpp"

// no need to modify this function
Location::Location(std::string name): name_(name) {}

// no need to modify this function
std::string Location::GetName() const { return name_; }

void Location::AddAgent(NewsAgent* agent) {
  agents_.push_back(agent);
  // TODO : implement
}

void Location::RemoveAgent(NewsAgent* agent) {
  for (unsigned long i = 0; i < agents_.size(); i++) {
    if (agents_[i] == agent) {
      agents_.erase(agents_.begin() + i);
    }
  }
}

void Location::Event(std::string date,
                     std::string subject,
                     std::string action) {
  for (auto observ : agents_) {
    observ->NotifyNews(date, subject, action);
  }
}
