#include <unistd.h>
#include <termios.h>
#include <string.h>

#include "functions.h"

#include "types.h"
#include "console.h"

class VirtualKeyMapperImpl
{
public:
    enum State
    {
        Normal,
        Escaped,
        EscapedSB
    };
    VirtualKeyMapperImpl(FuncOnVirtualKey onVirtualKey) :
        _onVirtualKey(onVirtualKey)
    {
        _state = Normal;
    }
    void push(int key)
    {

        switch (_state)
        {
        case Normal:
        {
            if (key == '\e')
            {
                _state = Escaped;
            }
            else if (key == 127)
            {
                _onVirtualKey(VirtualKey::BACKSPACE, key);
            }
            else if (key == 10)
            {
                _onVirtualKey(VirtualKey::RETURN, key);
            }
            else if (key == 27)
            {
                _onVirtualKey(VirtualKey::ESCAPE, key);
            }
            else
            {
                _onVirtualKey(VirtualKey::LETTER, key);
            }
            break;
        }
        case Escaped:
        {
            if (key == '[')
            {
                _state = EscapedSB;
            }
            else
            {
                _state = Normal; // error
            }
            break;
        }
        case EscapedSB:
        {
            if (key == 'A')
            {
                _onVirtualKey(VirtualKey::ARROW_UP, 'U');
            }
            else if (key == 'B')
            {
                _onVirtualKey(VirtualKey::ARROW_DOWN, 'D');
            }
            else if (key == 'C')
            {
                _onVirtualKey(VirtualKey::ARROW_RIGHT, 'R');
            }
            else if (key == 'D')
            {
                _onVirtualKey(VirtualKey::ARROW_LEFT, 'L');
            }

            _state = Normal;

            break;
        }
        }



    }
private:
    FuncOnVirtualKey _onVirtualKey;
    State _state;
};

class TerminalImpl
{
public:
    TerminalImpl(FuncOnError onError) :
        _onError(onError)
    {
        if (tcgetattr(0, &_oldConfig) < 0)
            _onError("tcsetattr()");
        _oldConfig.c_lflag &= ~CAST_UI(ICANON);
        _oldConfig.c_lflag &= ~CAST_UI(ECHO);
        _oldConfig.c_cc[VMIN] = 1;
        _oldConfig.c_cc[VTIME] = 0;

        if (tcsetattr(0, TCSANOW, &_oldConfig) < 0)
            _onError("tcsetattr ICANON");
    }

    int getNextChar()
    {
        return getchar();
    }

    ~TerminalImpl()
    {
        _oldConfig.c_lflag |= ICANON;
        _oldConfig.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &_oldConfig) < 0)
        {
            _onError("tcsetattr ~ICANON");
        }
        _onError("done");
    }
private:

    struct termios _oldConfig = {};
    FuncOnError _onError;
};

Console::Console(const std::vector<std::string>& commands)
{
    FuncOnError onError =
        [&](const std::string& error) -> void
        {
            printf("err: %s\n", error.c_str());
        };
    FuncOnVirtualKey onVKey =
        [&](VirtualKey vkey, int key) -> void
        {

            switch (vkey)
            {
            case VirtualKey::ARROW_UP:
            {
                _vIndex = 0;
                _hIndex = (_hIndex + _commands.size() -1) % _commands.size();
                _commandBuf.clear();
                _commandBuf.print(_commands[_hIndex].getCommand(_vIndex));
                break;
            }
            case VirtualKey::ARROW_DOWN:
            {
                _vIndex = 0;
                _hIndex = (_hIndex + _commands.size() +1) % _commands.size();
                _commandBuf.clear();
                _commandBuf.print(_commands[_hIndex].getCommand(_vIndex));
                break;
            }
            case VirtualKey::ARROW_LEFT:
            {
                sz varCount = _commands[_hIndex].getVariableCount();
                _vIndex = (_vIndex + varCount -1) % varCount;
                _commandBuf.clear();
                _commandBuf.print(_commands[_hIndex].getCommand(_vIndex));
                break;
            }
            case VirtualKey::ARROW_RIGHT:
            {
                sz varCount = _commands[_hIndex].getVariableCount();
                _vIndex = (_vIndex + varCount +1) % varCount;
                _commandBuf.clear();
                _commandBuf.print(_commands[_hIndex].getCommand(_vIndex));
                break;
            }
            case VirtualKey::BACKSPACE:
            {
                std::string var = _commands[_hIndex].getVariable(_vIndex);
                if (!var.empty())
                {
                    var.pop_back();
                }
                _commands[_hIndex].setVariable(_vIndex, var );
                _commandBuf.clear();
                _commandBuf.print(_commands[_hIndex].getCommand(_vIndex));
                break;
            }
            case VirtualKey::LETTER:
            {
                std::string var = _commands[_hIndex].getVariable(_vIndex);
                _commands[_hIndex].setVariable(_vIndex, var + (char)key);
                _commandBuf.clear();
                _commandBuf.print(_commands[_hIndex].getCommand(_vIndex));
                break;
            }
            default:
                break;
            }
        };

    _termImpl = new TerminalImpl(onError);
    _mapperImpl = new VirtualKeyMapperImpl(onVKey);

    for (auto& command : commands)
    {
        _commands.push_back(Command(command));
    }
}

void Console::run()
{
    while (1)
    {
        int a = _termImpl->getNextChar();
        _mapperImpl->push(a);
    }
}

Console::~Console()
{
    delete _termImpl;
    delete _mapperImpl;
}
