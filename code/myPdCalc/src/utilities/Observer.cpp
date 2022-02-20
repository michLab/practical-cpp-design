#include "Observer.h"
#include "Publisher.h"

#include <iostream>

namespace pdCalc
{
Observer::Observer(const std::string& name) : observerName_(name) {}

Observer::~Observer() {}

void Observer::notify(std::shared_ptr<EventData> d) { notifyImpl(d); }

}  // namespace pdCalc