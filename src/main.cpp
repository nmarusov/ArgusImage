#include <iostream>
#include <Magick++.h>
#include "cli.h"

using namespace std;
using namespace Magick;

int main(int argc, char **argv)
{
    InitializeMagick(*argv);

    return prompt();
}
