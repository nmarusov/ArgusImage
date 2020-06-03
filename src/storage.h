#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <map>
#include <Magick++.h>

using namespace std;
using namespace Magick;

class Storage
{
private:
    Storage(){};
    ~Storage(){};
    Storage(const Storage &other) = delete;
    void operator=(const Storage &) = delete;

    map<string, Image> images;

public:
    static Storage &getInstance()
    {
        static Storage singleton_;
        return singleton_;
    };

    int loadFromFile(string name, string filename);
    int saveToFile(string name, string filename);
    int get(string name, Image &image);
    int add(string name, const Image &image);
    int del(string name);
};

#endif
