#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

#include "types.h"
class Command
{
public:
    Command(const std::string& commandTemplate);
    Command(const Command& command) = default;
    sz getVariableCount() const;
    const std::string& getVariable(sz index) const;
    void setVariable(sz index, const std::string& value);
    std::string getCommand() const;
    std::string getCommand(sz selectedIndex) const;
private:
    std::string _command;
    std::vector<sz> _variablePos;
    std::vector<std::string> _variables;
};

#endif // COMMAND_H
