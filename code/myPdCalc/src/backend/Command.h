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
}  // namespace pdCalc

#endif