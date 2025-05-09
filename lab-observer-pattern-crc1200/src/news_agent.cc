#include "news_agent.hpp"

// no need to modify this function
NewsAgent::NewsAgent(): location_(nullptr) {}

// no need to modify this function
void NewsAgent::ChangeLocation(Location* loc) {
  if (location_) {
    location_->RemoveAgent(this);
  }

  location_ = loc;

  if (location_) {
    location_->AddAgent(this);
  }
}

void NewsAgent::AddNewsChannelClient(NewsChannel* client) {
  channels_.push_back(client);
  // TODO : implement
}

void NewsAgent::RemoveNewsChannelClient(NewsChannel* client) {
  for (unsigned long i = 0; i < channels_.size(); i++) {
    if (channels_[i] == client) {
      channels_.erase(channels_.begin() + i);
    }
  }
}

void NewsAgent::NotifyNews(std::string date,
                           std::string subject,
                           std::string action) {
  News news{location_->GetName(), date, subject, action};
  for (auto chan : channels_) {
    chan->NotifyNews(news);
  }
}