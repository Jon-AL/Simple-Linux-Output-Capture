/**
 * @Author: https://github.com/Jon-AL
 * @FileName: command.h
 * @FileContents: the Command class implementation.
 *                Negotiates between MainWindow and the Boost library.
 * @LastUpdated: Oct. 9, 2021
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <utility>
#include <boost/process.hpp>
#include <iostream>

class Command {
private:
    std::string command_input;
private:
    std::string result;
private:
    int return_code;

public:
    explicit Command(std::string command_input);

public:
    Command(const Command &new_command);

public:
    ~Command();

private:
    void setResult(std::string new_result);

public:
    int setCommandInput(std::string new_com);

public:
    std::string getCommandInput();

public:
    int getReturnCode();

public:
    std::string getResult();

public:
    std::string execute();


public:
    std::string generateOutput();

};

#endif //COMMAND_H
