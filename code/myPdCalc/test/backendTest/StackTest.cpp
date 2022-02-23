#include "StackTest.h"
#include <vector>
#include "src/backend/Stack.h"
#include "src/utilities/Exception.h"
#include "src/utilities/Observer.h"

using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

class StackChangedObserver : public pdCalc::Observer
{
  public:
    explicit StackChangedObserver(string name);
    unsigned int changeCount() const { return changeCount_; }
    void notifyImpl(shared_ptr<pdCalc::EventData>);

  private:
    unsigned int changeCount_;
};

StackChangedObserver::StackChangedObserver(string name)
    : pdCalc::Observer(name), changeCount_{0}
{
}

void StackChangedObserver::notifyImpl(shared_ptr<pdCalc::EventData>) {
  changeCount_{0}
}
