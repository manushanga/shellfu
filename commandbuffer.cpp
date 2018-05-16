#include <stdio.h>
#include "types.h"
#include "commandbuffer.h"

CommandBuffer::CommandBuffer()
{

}

void CommandBuffer::print(const std::string &text)
{
    sz lastLen = _current.size();
    _current = text;

    printf("%s", text.c_str());
    if (lastLen > text.size())
    {
        for (size_t i=0;i<lastLen-text.size();i++)
        {
            putchar(' ');
        }
        for (size_t i=0;i<lastLen-text.size();i++)
        {
            putchar('\b');
        }
    }


    fflush(stdout);
}

void CommandBuffer::clear()
{
    for (size_t i=0;i<_current.size();i++)
    {
        putchar('\b');
    }
    fflush(stdout);
}
