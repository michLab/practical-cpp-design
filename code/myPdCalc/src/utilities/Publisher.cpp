#include "Publisher.h"
#include "Exception.h"
#include "Observer.h"

#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::ostringstream;
using std::set;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

namespace pdCalc
{
class Publisher::PublisherImpl
{
    using ObserversList = std::unordered_map<string, unique_ptr<Observer>>;
    using Events = std::unordered_map<string, ObserversList>;

  public:
    PublisherImpl();
    ~PublisherImpl();

    void attach(const string& eventName, unique_ptr<Observer> observer);
    unique_ptr<Observer> detach(const string& eventName,
                                const string& observerName);
    void notify(const string& eventName, shared_ptr<EventData> d);
    void registerEvent(const std::string& eventName);
    void registerEvents(const std::vector<std::string>& eventNames);
    set<string> listEvents() const;
    set<string> listEventObservers(const string& eventName) const;

    Events::const_iterator findCheckedEvent(const string& eventName) const;
    Events::iterator findCheckedEvent(const string& eventName);

  private:
    Events events_;
};

Publisher::PublisherImpl::PublisherImpl() {}

Publisher::PublisherImpl::~PublisherImpl() {}

Publisher::PublisherImpl::Events::const_iterator
Publisher::PublisherImpl::findCheckedEvent(const string& eventName) const
{
    auto ev = events_.find(eventName);
    if (ev == events_.end()) {
        ostringstream oss;
        oss << "Publisher does not suppor event '" << eventName << "'";
        throw Exception(oss.str());
    }
    return ev;
}

Publisher::PublisherImpl::Events::iterator
Publisher::PublisherImpl::findCheckedEvent(const string& eventName)
{
    auto ev = events_.find(eventName);
    if (ev == events_.end()) {
        ostringstream oss;
        oss << "Publisher does not suppor event '" << eventName << "'";
        throw Exception(oss.str());
    }
    return ev;
}

void Publisher::PublisherImpl::attach(const string& eventName,
                                      unique_ptr<Observer> observer)
{
    auto ev = findCheckedEvent(eventName);
    auto& obsList = ev->second;

    auto obs = obsList.find(observer->name());
    if (obs != obsList.end()) {
        throw Exception("Observer already attached to publisher");
    }
    obsList.insert(std::make_pair(observer->name(), std::move(observer)));
}

unique_ptr<Observer> Publisher::PublisherImpl::detach(
    const string& eventName, const string& observerName)
{
    auto ev = findCheckedEvent(eventName);
    auto& obsList = ev->second;

    auto obs = obsList.find(observerName);
    if (obs == obsList.end()) {
        throw Exception("Cannot detach observer because observer not found");
    }
    auto tmp = std::move(obs->second);
    obsList.erase(obs);

    return tmp;
}

void Publisher::PublisherImpl::notify(const string& eventName,
                                      shared_ptr<EventData> d)
{
    auto ev = findCheckedEvent(eventName);
    auto& obsList = ev->second;

    for (const auto& obs : obsList) {
        obs.second->notify(d);
    }
}

void Publisher::PublisherImpl::registerEvent(const std::string& eventName)
{
    auto i = events_.find(eventName);
    if (i != events_.end()) {
        throw Exception("Event already registred");
    }
    events_[eventName] = ObserversList();
}

void Publisher::PublisherImpl::registerEvents(
    const std::vector<std::string>& eventNames)
{
    for (auto i : eventNames) {
        registerEvent(i);
    }
}

set<string> Publisher::PublisherImpl::listEvents() const
{
    set<string> tmp;
    for (const auto& e : events_) {
        tmp.insert(e.first);
    }
    return tmp;
}

set<string> Publisher::PublisherImpl::listEventObservers(
    const string& eventName) const
{
    auto e = findCheckedEvent(eventName);

    set<string> tmp;
    for (const auto& i : e->second) {
        tmp.insert(i.first);
    }
    return tmp;
}

Publisher::Publisher() { publisherImpl_ = std::make_unique<PublisherImpl>(); }

Publisher::~Publisher() {}

void Publisher::attach(const std::string& eventName,
                       std::unique_ptr<Observer> observer)
{
    publisherImpl_->attach(eventName, std::move(observer));
}

std::unique_ptr<Observer> Publisher::detach(const std::string& eventName,
                                            const std::string& observerName)
{
    return publisherImpl_->detach(eventName, observerName);
}

std::set<std::string> Publisher::listEvents() const
{
    return publisherImpl_->listEvents();
}

std::set<std::string> Publisher::listEventObservers(
    const std::string& eventName) const
{
    return publisherImpl_->listEventObservers(eventName);
}

void Publisher::raise(const std::string& eventName,
                      std::shared_ptr<EventData> d) const
{
    publisherImpl_->notify(eventName, d);
}

void Publisher::registerEvent(const std::string& eventName)
{
    publisherImpl_->registerEvent(eventName);
}

void Publisher::registerEvents(const std::vector<std::string>& eventNames)
{
    publisherImpl_->registerEvents(eventNames);
}

}  // namespace pdCalc