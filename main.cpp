#include <iostream>
#include <unistd.h>
#include "console.h"
#include "commandbuffer.h"
#include "command.h"
using namespace std;

int main()
{
    CommandBuffer b;
    Console c({"for {} in {} do; echo ${}; done;", "grep -rn {} {} | less"});
    c.run();
    return 0;
}
