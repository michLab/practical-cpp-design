#ifndef PUBLISHER_H_
#define PUBLISHER_H_

// The Publisher class is a class capable of receiving observers. Note that it
// is assumed that a real publisher may publish multiple separate events. These
// are stored by string name in a table. Since each event may have multiple
// observers, the table stores a collection of observers.

// Important: Publishers own the memory for their observers (enforced by
// std::unique_ptr)

#include <memory>
#include <set>
#include <string>

namespace pdCalc
{
class Observer;

class EventData
{
  public:
    virtual ~EventData();
};

class Publisher
{
    class PublisherImpl;

  public:
    Publisher();
    void attach(const std::string& eventName,
                std::unique_ptr<Observer> observer);
    std::unique_ptr<Observer> detach(const std::string& eventName,
                                     const std::string& observerName);

    std::set<std::string> listEvents() const;
    std::set<std::string> listEventObservers(
        const std::string& eventName) const;

  protected:
    ~Publisher();
    void raise(const std::string& eventName, std::shared_ptr<EventData>) const;
    void registerEvent(const std::string& eventName);
    void registerEvents(const std::vector<std::string>& eventNames);

  private:
    std::unique_ptr<PublisherImpl> publisherImpl_;
}
}  // namespace pdCalc
#endif