#include "CommandRepository.h"
#include <sstream>
#include <unordered_map>
#include "Command.h"
#include "utilities/Exception.h"

using std::set;
using std::string;
using std::unordered_map;

namespace pdCalc
{
class CommandRepository::CommandRepositoryImpl
{
  public:
    CommandRepositoryImpl();
    void registerCommand(const string& name, CommandPtr c);
    CommandPtr deregisterCommand(const string& name);

    size_t getNumberCommands() const { return repository_.size(); }
    CommandPtr allocateCommand(const string& name) const;

    bool hasKey(const string& name) const;
    set<string> getAllCommandNames() const;

    void printHelp(const string& command, std::ostream& os);

    void clearAllCommands();

  private:
    using Repository = unordered_map<string, CommandPtr>;
    Repository repository_;
};

CommandRepository::CommandRepositoryImpl::CommandRepositoryImpl() {}

void CommandRepository::CommandRepositoryImpl::registerCommand(
    const string& name, CommandPtr c)
{
    if (hasKey(name)) {
        std::ostringstream oss;
        oss << "Command " << name << " already registered";
        throw Exception{oss.str()};
    } else {
        repository_.emplace(name, std::move(c));
    }
}

CommandPtr CommandRepository::CommandRepositoryImpl::deregisterCommand(
    const string& name)
{
    if (hasKey(name)) {
        auto i = repository_.find(name);
        auto tmp = MakeCommandPtr(i->second.release());
        repository_.erase(i);
        return tmp;
    } else {
        return MakeCommandPtr();
    }
}

CommandPtr CommandRepository::CommandRepositoryImpl::allocateCommand(
    const string& name) const
{
    if (hasKey(name)) {
        const auto& command = repository_.find(name)->second;
        return MakeCommandPtr(command->clone());
    } else {
        MakeCommandPtr(nullptr);
    }
}

bool CommandRepository::CommandRepositoryImpl::hasKey(const string& name) const
{
    return repository_.find(name) != repository_.end();
}

set<string> CommandRepository::CommandRepositoryImpl::getAllCommandNames() const
{
    set<string> tmp;
    for (auto i = repository_.begin(); i != repository_.end(); ++i) {
        tmp.insert(i->first);
    }
    return tmp;
}

void CommandRepository::CommandRepositoryImpl::printHelp(const string& command,
                                                         std::ostream& os)
{
    auto it = repository_.find(command);
    if (it != repository_.end()) {
        os << command << ": " << it->second->helpMessage();
    } else {
        os << command << ": no help entry found";
    }
}

void CommandRepository::CommandRepositoryImpl::clearAllCommands()
{
    repository_.clear();
}

CommandRepository::CommandRepository() : pimpl_{new CommandRepositoryImpl} {}

CommandRepository::~CommandRepository() {}

void CommandRepository::registerCommand(const std::string& name, CommandPtr c)
{
    pimpl_->registerCommand(name, std : move(c));
}

CommandPtr CommandRepository::deregisterCommand(const std::string& name)
{
    return pimpl_->deregisterCommand(name);
}

size_t CommandRepository::getNumberCommands() const
{
    return pimpl_->getNumberCommands();
}

CommandPtr CommandRepository::allocateCommand(const std::string& name) const
{
    return pimpl_->allocateCommand(name);
}

bool CommandRepository::hasKey(const std::string& name) const
{
    return pimpl_->hasKey(name);
}

std::set<std::string> CommandRepository::getAllCommandNames() const
{
    return pimpl_->getAllCommands();
}

void CommandRepository::printHelp(const std::string& name, std::ostream&) const
{
    return pimpl_->printHelp(command, os);
}

void CommandRepository::clearAllCommands();
{
    pimpl_->clearAllCommands();
}

}  // namespace pdCalc
