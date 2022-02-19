#ifndef STACH_H_
#define STACH_H_

#include <cstddef>
#include <memory>
#include <vector>

namespace pdCalc {
class Stack {
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