#ifndef CONSOLEBUFFER_H
#define CONSOLEBUFFER_H

#include <string>

class CommandBuffer
{
public:
    CommandBuffer();
    void print(const std::string& text);
    void clear();
private:
    std::string _current;
};

#endif // CONSOLEBUFFER_H
