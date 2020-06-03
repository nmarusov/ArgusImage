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
    {"help", "h", helpCommand},
    {"quit", "q", quitCommand},
    {"exit", nullptr, quitCommand}};

const char *HELP = R"(
Справка по интерактивном интерфейсу:
load, ld        Загрузка изображения в формате JPG
    Параметры:
                <name> - имя изображения, по имени оно доступно в других командах
                <filename> - имя файла для загрузки

store, s        Сохранение изображения в формате jpg
    Параметры:
                <name> - имя изображения
                <filename> - имя файла для сохранениея

blur            Сглаживание изображение
    Параметры:
                <from_name> - имя изображения
                <to_name> - имя изображения
                <size> - размер сглаживаемой области

resize          Изменение размера изображения
    Параметры:
                <from_name> - имя изображения
                <to_name> - имя изображения
                <new_width>
                <new_height>

help, h         Выводит справку о поддерживаемых командах

exit, quit, q   Выход)";

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
            cout << "До свидания!" << endl;
            return 0;
        case UNKNOWN_COMMAND:
            cout << "Неизвестная команда" << endl;
            break;
        case INVALID_PARAMETER:
            cout << "Неправильный параметр" << endl;
            break;
        case RUNTIME_ERROR:
            cout << "Ошибка времени исполнения" << endl;
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

    cout << "Загрузка изображения... ";

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

    cout << "Сохранение изображения... ";
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

    cout << "Размытие... ";

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

    cout << "Изменение размера... ";

    int err = resize(args.at(0), args.at(1), stoi(args.at(2)), stoi(args.at(3)));

    if (err == OK)
    {
        cout << "OK" << endl;
    }
    return err;
}

int helpCommand(const vector<string> &args)
{
    cout << HELP << endl;
    return OK;
}

int quitCommand(const vector<string> &args)
{
    return QUIT;
}
