#include <iostream>
#include "operations.h"
#include "error.h"

using namespace std;

int blur(string from_name, string to_name, int size)
{
    cout << from_name << endl;
    cout << to_name << endl;
    cout << size * 2 << endl;

    return OK;
}

int resize(string from_name, string to_name, int new_width, int new_height)
{
    cout << from_name << endl;
    cout << to_name << endl;
    cout << new_width * 2 << endl;
    cout << new_height * 2 << endl;

    return OK;
}
