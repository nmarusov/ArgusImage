#include <iostream>
#include "operations.h"
#include "error.h"
#include "storage.h"

using namespace std;

int blur(string from_name, string to_name, int size)
{
    Image orig;

    int err = Storage::getInstance().get(from_name, orig);

    if (err != OK)
    {
        return err;
    }

    Image target(orig);
    target.blur((const double)size, 10.0);
    err = Storage::getInstance().add(to_name, target);

    return err;
}

int resize(string from_name, string to_name, int new_width, int new_height)
{
    Image orig;

    int err = Storage::getInstance().get(from_name, orig);

    if (err != OK)
    {
        return err;
    }

    Image target(orig);
    target.resize(Geometry(new_width, new_height, 0, 0));
    err = Storage::getInstance().add(to_name, target);

    return err;
}
