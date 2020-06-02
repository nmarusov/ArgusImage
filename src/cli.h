#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>

using namespace std;

int prompt();

// Команды
int loadCommand(const vector<string> &args);
int storeCommand(const vector<string> &args);
int blurCommand(const vector<string> &args);
int resizeCommand(const vector<string> &args);
int helpCommand(const vector<string> &args);
int quitCommand(const vector<string> &args);

struct CommandStruct
{
    const char *command;
    const char *alias;
    int (*commandHandler)(const vector<string> &args);
};

#endif
