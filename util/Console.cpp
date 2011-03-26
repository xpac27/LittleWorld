#include "Console.h"

using namespace std;

void Console::log(string s)
{
    if (Conf::DEBUG)
    {
        cout << s << endl;
    }
}

