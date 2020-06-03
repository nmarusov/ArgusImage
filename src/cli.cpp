#include <iostream>
#include "cli.h"
#include "operations.h"
#include "storage.h"
#include "error.h"
#include "utils.h"

#define DELIMITER (' ')

#define TABLE_SIZE (sizeof(commandTable) / sizeof(commandTable[0]))

using namespace std;

static CommandStruct commandTable[] = {
    {"load", "ld", loadCommand},
    {"store", "s", storeCommand},
    {"blur", nullptr, blurCommand},
    {"resize", nullptr, resizeCommand},
    {"help", nullptr, helpCommand},
    {"quit", "q", quitCommand},
    {"exit", nullptr, quitCommand}};

static int dispatch(string input);

int prompt()
{
    string input;

    while (1)
    {
        cout << "> ";
        getline(cin, input);
        int result = dispatch(input);

        switch (result)
        {
        case QUIT:
            cout << "Bye!" << endl;
            return 0;
        case UNKNOWN_COMMAND:
            cout << "Unknown command" << endl;
            break;
        case INVALID_PARAMETER:
            cout << "Invalid parameter" << endl;
            break;
        case RUNTIME_ERROR:
            cout << "Runtime error" << endl;
            break;

        default:
            break;
        }
    }
}

int dispatch(string input)
{
    int (*commandHandler)(const vector<string> &args) = nullptr;
    vector<string> command = split(input, DELIMITER);

    if (command.size() == 0)
    {
        return OK;
    }

    for (unsigned int i = 0; i < TABLE_SIZE; i++)
    {
        if (command.at(0).compare(commandTable[i].command) == 0)
        {
            commandHandler = commandTable[i].commandHandler;
        }
        else if (commandTable[i].alias != nullptr)
        {
            if (command.at(0).compare(commandTable[i].alias) == 0)
            {
                commandHandler = commandTable[i].commandHandler;
            }
        }
        else
        {
            continue;
        }

        if (commandHandler != nullptr)
        {
            try
            {

                return commandHandler(
                    vector<string>(command.begin() + 1, command.end()));
            }
            catch (const exception &e)
            {
                return RUNTIME_ERROR;
            }
        }
    }

    return UNKNOWN_COMMAND;
}

int loadCommand(const vector<string> &args)
{
    if (args.size() < 2)
    {
        return INVALID_PARAMETER;
    }

    cout << "Loading image... ";

    int err = Storage::getInstance().loadFromFile(args.at(0), args.at(1));

    if (err == OK)
    {
        cout << "OK" << endl;
    }
    return err;
}

int storeCommand(const vector<string> &args)
{
    if (args.size() < 2)
    {
        return INVALID_PARAMETER;
    }

    cout << "Saving image... ";
    Storage &storage = Storage::getInstance();

    int err = Storage::getInstance().saveToFile(args.at(0), args.at(1));

    if (err == OK)
    {
        cout << "OK" << endl;
    }
    return err;
}

int blurCommand(const vector<string> &args)
{
    if (args.size() < 3)
    {
        return INVALID_PARAMETER;
    }

    cout << "Blurring... ";

    int err = blur(args.at(0), args.at(1), stoi(args.at(2)));

    if (err == OK)
    {
        cout << "OK" << endl;
    }
    return err;
}

int resizeCommand(const vector<string> &args)
{
    if (args.size() < 4)
    {
        return INVALID_PARAMETER;
    }

    cout << "Resizing... ";

    int err = resize(args.at(0), args.at(1), stoi(args.at(2)), stoi(args.at(3)));

    if (err == OK)
    {
        cout << "OK" << endl;
    }
    return err;
}

int helpCommand(const vector<string> &args)
{
    cout << "Help" << endl;
    return OK;
}

int quitCommand(const vector<string> &args)
{
    return QUIT;
}
