#include <iostream>
#include <unistd.h>
#include "console.h"
#include "commandbuffer.h"
#include "command.h"
using namespace std;

int main()
{
    std::string result;
    {
        Console c({"for {} in {}; do {} ${}; done", "grep -rn {} {} | less"});
        result = c.run();
    }

    system(result.c_str());
    return 0;
}
