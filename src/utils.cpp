#include <sstream>
#include "utils.h"

using namespace std;

vector<string> split(const string &input, char delimeter)
{
    vector<string> collection;
    stringstream ss(input);
    string token;

    while (getline(ss, token, delimeter))
    {
        if (token.length() != 0)
        {
            collection.push_back(token);
        }
    }

    return collection;
}
