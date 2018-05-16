#ifndef CONSOLE_H
#define CONSOLE_H
#include "types.h"
#include "command.h"
#include "commandbuffer.h"

class TerminalImpl;
class VirtualKeyMapperImpl;

class Console
{
public:
    Console(const std::vector<std::string>& commands);
    std::string run();
    ~Console();
private:
    TerminalImpl* _termImpl;
    VirtualKeyMapperImpl* _mapperImpl;
    std::vector<Command> _commands;
    CommandBuffer _commandBuf;
    sz _hIndex;
    sz _vIndex;
    bool _stop;
    std::string _result;
};

#endif // CONSOLE_H
