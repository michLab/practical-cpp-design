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
    void push(double, bool suppressChangeEvent = false);
    double pop(bool suppressChangeEvent = false);
    void swapTop();
    void getElements(size_t n, std::vector<double>&) const;
    std::vector<double> getElements(size_t n);

    using Publisher::attach;
    using Publisher::detach;

    size_t size() const;
    void clear() const;

    static const std::string StackChanged;
    static const std::string StackError;

  private:
    Stack();
    ~Stack();

    // Appropriate blocking of copying, assign, moving.
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack& operator=(const Stack&&) = delete;

    std::unique_ptr<StackImpl> pimpl_;
};
}  // namespace pdCalc

#endif