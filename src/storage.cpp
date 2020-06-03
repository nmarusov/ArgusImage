#include <iostream>
#include "storage.h"
#include "error.h"

int Storage::loadFromFile(string name, string filename)
{
    pair<map<string, Image>::iterator, bool> result;

    try
    {
        result = images.emplace(name, Image(filename));
    }
    catch (Exception &error_)
    {
        cout << "Cannot read image from file " << filename << ": " << error_.what() << endl;
        return RUNTIME_ERROR;
    }

    if (!result.second)
    {
        cout << "Image with name " << name << " already exists: not loaded" << endl;
        return RUNTIME_ERROR;
    }

    return OK;
}

int Storage::saveToFile(string name, string filename)
{
    auto it = images.find(name);

    if (it == images.end())
    {
        cout << "Image with name " << name << " is absent" << endl;
        return RUNTIME_ERROR;
    }

    try
    {
        it->second.write(filename);
    }
    catch (Exception &error_)
    {
        cout << "Cannot write image to file " << filename << ": " << error_.what() << endl;
        return RUNTIME_ERROR;
    }

    return OK;
}

int Storage::get(string name, Image &image)
{
    auto it = images.find(name);

    if (it == images.end())
    {
        cout << "Image with name " << name << " is absent" << endl;
        return RUNTIME_ERROR;
    }

    image = it->second;

    return OK;
}

int Storage::add(string name, const Image &image)
{
    pair<map<string, Image>::iterator, bool> result;

    result = images.emplace(name, move(image));

    if (!result.second)
    {
        cout << "Image with name " << name << " already exists: not loaded" << endl;
        return RUNTIME_ERROR;
    }

    return OK;
}

int Storage::del(string name)
{
    if (images.erase(name) > 0)
    {
        return OK;
    };

    cout << "Image with name " << name << " is absent" << endl;
    return RUNTIME_ERROR;
}
