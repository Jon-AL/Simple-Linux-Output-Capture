/**
 * @Author: https://github.com/Jon-AL
 * @FileName: command.cpp
 * @FileContents: the Command class implementation.
 *                Negotiates between MainWindow and the Boost library.
 * @LastUpdated: Oct. 9, 2021
 */

#include "command.h"

using namespace boost::process;
using namespace boost::io;

/**
 * Command class constructor
 * <br><br>
 * processes and handles the Boost library for the MainWindow class
 *
 * @param command_input a string, written as if it typed in the command terminal.
 */
Command::Command(std::string command_input) {

    this->command_input = command_input;
    this->result = "";
    this->return_code = 0;
}

/**
 * Copy constructor<br>
 * <br>
 * Command class - processes and handles the Boost library for the MainWindow class
 * @param other the other Command class to be copied
 */
Command::Command(const Command &other) {
    this->command_input = other.command_input;
    this->result = other.result;
    this->return_code = other.return_code;
}

/**
 * Deconstructor<br><br>
 *
 * undefined (not required as per instructions).
 */
Command::~Command() {
}

/**
 * @deprecated
 * A helper setter function to set the result variable of this object
 * @note private method, not used
 * @param new_result a string, the supposed output of a command.
 */
void Command::setResult(std::string new_result) {
    this->result = new_result;
}

/**
 * A setter function to set the command_input variable of this object
 *
 * @note public method, not used
 * @param new_com std::string, written as if it typed in the command terminal.
 */
int Command::setCommandInput(std::string new_com) {
    command_input = new_com;
    return 0;
}

/**
 * A getter function to get the command_input variable of this object
 *
 * @note public method.
 * @return std::string, the command input.
 */
std::string Command::getCommandInput() {
    return this->command_input;
}

/**
 * A getter function to get the return_code variable of this object
 *
 * @note public method.
 * @return int, the return_code.
 */
int Command::getReturnCode() {
    return return_code;
}

/**
 * A getter function to get the result variable of this object.
 * Result is empty if execute didn't run yet.
 *
 * @note public method.
 * @return std::string, the result.
 */
std::string Command::getResult() {
    return result;
}

/**
 * tells the command to process the requested command. <br>
 * @note: only non-interactive commands (meaning, cd for example won't work, but ls will)
 * @return
 */
std::string Command::execute() {

    if (this->command_input.empty()) {
        result = "Process error: Empty input\n";
        return_code = -1;
        return result;
    }
    try {
        ipstream pipe_stream;
        child c(command_input, (std_out & std_err) > pipe_stream);
        std::string line;
        while (pipe_stream && std::getline(pipe_stream, line) && !line.empty()) {
            result.append(line);
            result.append("\n");
            std::cerr << line << std::endl;
        }
        return_code = 0;
        c.wait();
        return result;
    }
    catch (boost::process::process_error &e) {
        result = "Process error: error in command execution\n";
        return_code = -1;
        return result;
    }
}

/**
 *  A helper function for MainWindow class, it returns the input, return code,
 *  and output, all joined into a single object.<br>
 *  Used by display_history screen
 *
 * @return a single object of type std::string
 */
std::string Command::generateOutput() {  //intended for history screen
    std::string output = "Command: ";
    output = output + command_input + "\n";
    output = output + "Return Code: " + std::to_string(return_code) + "\n";
    output = output + "Result:\n" + result + "\n";
    return output;
}


