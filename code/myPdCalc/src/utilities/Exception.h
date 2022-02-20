#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>

namespace pdCalc
{
class Exception
{
  public:
    explicit Exception(const std::string& msg) : msg_(msg) {}
    const std::string& what() const { return msg_; }

  private:
    std::string msg_;
};
}  // namespace pdCalc

#endif