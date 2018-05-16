#include "command.h"
#include <iostream>

static const std::string s_literal = "{}";

#define COLOR_START "\e[38;5;196m"
#define COLOR_END "\e[0m"
Command::Command(const std::string& commandTemplate) :
    _command(commandTemplate)
{
    sz start=0;
    sz ret;
    do
    {
        ret = _command.find(s_literal, start);

        if (ret != std::string::npos)
        {
            _variablePos.push_back(ret);
            start = ret+1;
        }

    } while (ret != std::string::npos);

    _variables.resize(_variablePos.size());
}

sz Command::getVariableCount() const
{
    return _variables.size();
}

const std::string& Command::getVariable(sz index) const
{
    return _variables[index];
}

void Command::setVariable(sz index, const std::string &value)
{
    _variables[index] = value;
}

std::string Command::getCommand() const
{
    std::string finalCom;
    sz last = 0;
    for (sz i=0;i<_variablePos.size();i++)
    {
        finalCom += _command.substr(last, _variablePos[i] - last );
        last = _variablePos[i] + s_literal.size() ;

        finalCom += _variables[i];
    }
    finalCom += _command.substr(last);
    return finalCom;
}

std::string Command::getCommand(sz selectedIndex) const
{
    std::string finalCom;
    sz last = 0;
    for (sz i=0;i<_variablePos.size();i++)
    {
        finalCom += _command.substr(last, _variablePos[i] - last );
        last = _variablePos[i] + s_literal.size() ;
        if (i == selectedIndex)
        {
            finalCom += COLOR_START "{" COLOR_END;
            finalCom += _variables[i];
            finalCom += COLOR_START "}" COLOR_END;
        }
        else
        {
            finalCom += _variables[i];
        }
    }
    finalCom += _command.substr(last);
    return finalCom;
}
