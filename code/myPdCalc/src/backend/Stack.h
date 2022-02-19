#ifndef STACH_H_
#define STACH_H_

#include <cstddef>
#include <memory>
#include <vector>
#include "../utilities/Publisher.h"

namespace pdCalc
{
class StackEventData : public EventData
{
  public:
    enum class ErrorConditions { Empty, TooFewArguments };
    explicit StackEventData(ErrorConditions e) : err_(e){};

    static const char* Message(ErrorConditions ec);
    const char* message() const;
    ErrorConditions error() const { return err_; }

  private:
    ErrorConditions err_;
};

class Stack : private Publisher
{
    class StackImpl;

  public:
    static Stack& Instance();
    void push(double);
    double pop();
    void swapPop();
    void getElements(size_t n, std::vector<double>&) const;
    std::vector<double> getElements(size_t n);

  private:
    Stack();
    ~Stack();

    // Appropriate blocking of copying, assign, moving.
    std::unique_ptr<StackImpl> pimpl_;
};
}  // namespace pdCalc

#endif