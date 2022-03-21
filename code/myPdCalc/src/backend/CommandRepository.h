#ifndef COMMAND_REPOSITORY_H_
#define COMMAND_REPOSITORY_H_

#include <Command.h>
#include <iostream>
#include <memory>
#include <string>

namespace pdCalc
{
class CommandRepository
{
    class CommandRepositoryImpl;

  public:
    // Register a new command for the factory: throws if command with the
    // same name already exists... deregister first to replace a command.
    void registerCommand(const std::string& name, CommandPtr c);

    // Deregister a command: returns the pointer to a command and subsequently
    // removes it from the internal database of commands... returns a nullptr
    // if the command does not exist.
    CommandPtr deregisterCommand(const std::string& name);

    // Returns the number of commands currently registered.
    size_t getNumberCommands() const;

    // Returns a pointer to a command without deregistering the
    // command...returns a nullptr if the command does not exist.
    CommandPtr allocateCommand(const std::string& name) const;

    // Returns true it the command is present, false otherwise.
    bool hasKey(const std::string& name) const;

    // Returns a set of all the commands
    std::set<std::string> getAllCommandNames() const;

    // Prints help for the command.
    void printHelp(const std::string& name, std::ostream&) const;

    // Clears all the commands; mainly for tesing.
    void clearAllCommands();

  private:
    CommandRepository();
    ~CommandRepository();

    CommandRepository(CommandRepository&) = delete;
    CommandRepository(CommandRepository&&) = delete;
    CommandRepository& operator=(CommandRepository&) = delete;
    CommandRepository& operator=(CommandRepository&&) = delete;

    std::unique_ptr<CommandRepositoryImpl> pimpl_;
};
}  // namespace pdCalc

#endif