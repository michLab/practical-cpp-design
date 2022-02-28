#ifndef COMMAND_H_
#define COMMAND_H_

namespace pdCalc
{
class Command
{
  public:
    virtual ~Command(){};

    // Executes the command.
    void execute();

    // Undoes the command.
    void undo();

    // Create a polymorphic copy of the command.
    Command* clone() const;

    // Supplies a shot help message for the command.
    const char* helpMessage() const;

    // Deletes command (this should be overriden only on plugins).
    virtual void deallocate();

  protected:
    Command() {}
    Command(const Command&) {}

  private:
    // This function is not pure virtual because a command that needs no
    // preconditions shouldn't be forced to check for any...thus, this defaults
    // to not throwing.
    virtual void checkPreconditionsImpl() const;

    virtual void executeImpl() noexcept = 0;
    virtual void undoImpl() noexcept = 0;
    virtual Command* cloneImpl() const = 0;

    virtual const char* helpMessageImpl() const noexcept = 0;

    Command(Command&&) = delete;
    Command& operator=(const Command&) = delete;
    Command& operator=(Command&&) = delete;
};

class BinaryCommand : public Command {
  public:
    virtual ~BinaryCommand();
  protected:
    void CheckPreconditionsImpl() const override;
    BinaryCommand() {}
    BinaryCommand(const BinaryCommand&);
  private:
    BinaryCommand(BinaryCommand&&) = delete;
    BinaryCommand& operator=(const BinaryCommand&) = delete;
    BinaryCommand& operator=(BinaryCommand&&) = delete;

    // Takes two elements from the stack, applies the binary operation
    // and returns the result to the stack.
    void executeImpl() noexcept override;

    // Drops the result and returns the oryginal two numbers to the stack.
    void undoImpl() noexcept override;

    virtual double binaryOperation(double next, double top) const noexcept = 0;

    double top_;
    double next_;
};

class UnaryCommand : public Command {
  public:
  virtual ~UnaryCommand() {};
  UnaryCommand() {};

  private:
  // Takes one element from the stack, applies the binary operatrion
  // and returns the result to the stack.
  void executeImpl() noexcept override;

  // Drops the result and returns the oryginal number to the stack.
  void undoImpl() noexcept override;

  virtual double unaryOperation(double top) const noexcept = 0;

  double top_;
};


}  // namespace pdCalc

#endif