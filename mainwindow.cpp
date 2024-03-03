/**
 * @Author: https://github.com/Jon-AL
 * @FileName: mainwindow.cpp
 * @FileContents: the MainWindow object, this is the "real" main
 *                Takes care of the input and output from the user.
 *                Enabled: user pressing enter and/or the compute button to submit input.
 *                         user can click (one click, single selection is enabled) on the list widget to immediately display the contents of the (past) command used
 *                         It will not erase nor re-calculate the command, nor input it into the line editor.
 * @LastUpdated: Oct. 9, 2021
 */

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {

    // make "Compute" button
    m_button = new QPushButton("Compute", this);
    // set size and location
    m_button->setGeometry(QRect(QPoint(500, 50), QSize(100, 50)));
    // Connect signal to appropriate slot
    connect(m_button, &QPushButton::released, this, &MainWindow::processInput);

    // make "Command Input" label
    title_label = new QLabel("Command Input", this);
    // set size and location
    title_label->setGeometry(QRect(QPoint(25, 50), QSize(100, 50)));
    // Connect signal to appropriate slot
    title_label->setWordWrap(true);

    // make input panel
    input_panel = new QLineEdit(this);
    // set placeholder text
    input_panel->setPlaceholderText("Input command here, or close the window the exit");
    // set size and location
    input_panel->setGeometry(QRect(QPoint(125, 50), QSize(350, 50)));
    // Focus onto the box. By design, only happens when opening things for the first time.
    input_panel->setFocus();
    // Connect signal to appropriate slot
    connect(input_panel, &QLineEdit::returnPressed, this, &MainWindow::processInput);

    // make the input_instruction label
    input_instruction = new QLabel("press enter or the Compute button to confirm", this);
    // set size and location
    input_instruction->setGeometry(QRect(QPoint(125, 105), QSize(350, 15)));
    // enable wordwrap mode
    input_instruction->setWordWrap(true);

    // make the status_label
    status_label = new QLabel("Exit Status: 0", this);
    // set size and location
    status_label->setGeometry(QRect(QPoint(25, 630), QSize(100, 50)));
    // enable wordwrap mode
    status_label->setWordWrap(true);

    // make display panel
    display = new QTextEdit("", this);
    // set size and location
    display->setGeometry(QRect(QPoint(25, 125), QSize(450, 500)));
    // set as un-editable by the user
    display->setReadOnly(true);


    // make the command_history label
    command_history = new QLabel("History", this);
    // set size and location
    command_history->setGeometry(QRect(QPoint(675, 50), QSize(50, 50)));
    // enable wordwrap mode
    command_history->setWordWrap(true);

    // make the command_instruction label
    command_instruction = new QLabel("Click item to display", this);
    // set size and location
    command_instruction->setGeometry(QRect(QPoint(750, 105), QSize(375, 15)));
    // enable wordwrap mode
    command_instruction->setWordWrap(true);

    // make the display that shows all past commands
    history = new QListWidget(this);
    // set size and location
    history->setGeometry(QRect(QPoint(750, 50), QSize(375, 50)));
    // set to single selection mode
    history->setSelectionMode(QAbstractItemView::SingleSelection);
    // Connect signal to appropriate slot
    connect(history, &QListWidget::itemClicked, this, &MainWindow::historySelected);
    // Connect signal to appropriate slot
    connect(history, &QListWidget::itemSelectionChanged, this, &MainWindow::historySelected);

    // make the back end of the history display panel - where the actual Command objects are stored
    command_vector = new std::vector<Command>();

    // make history display panel
    display_history = new QTextEdit("", this);
    // set size and location
    display_history->setGeometry(QRect(QPoint(675, 125), QSize(450, 500)));
    // set as un-editable by the user
    display_history->setReadOnly(true);

}

/**
 * @brief helper method for processInput method, takes care of the Command object,
 * generates input, and tells the display to update.
 * @param input Pointer to a Command object.
 */
void MainWindow::displayResult(Command *input) {
    QString result = fromString(input->getResult());  // get result as string
    int status = input->getReturnCode();        // get return code
    QString command_input = fromString(input->getCommandInput()); // make return code into QString
    updateStatus(status); // update the status_label QLabel object
    display->clear(); // clears the display before next one is being put in
    display->setPlainText(result); // display result - input result to display as plain text
}

/**
 * @brief helper function for displayResult method. Updates the status_label with status
 * @param status the
 */
void MainWindow::updateStatus(int status) {
    QString str = QString("Exit Status: %1").arg(status);
    status_label->setText(str);
}

/**
 * @brief processInput - invoked when either the compute m_button is pressed
 * or when the "enter" key is pressed during editing of the input field.
 * This method can be triggered even if the input field is empty.
 * makes and handles the input.
 *
 * @note Slot method
 */
void MainWindow::processInput() {
    QString str = input_panel->text();  // requests the text from the input panel
    std::string input = toStd(input_panel->text()); // converts QString to std::string
    command_item = new Command(input); // makes new Command
    std::string output = command_item->execute(); // orders output and executes it.
    addCommand(*command_item);  // adds the new Command into the vector
    str.insert(0, ":  "); // prepares for addition to history
    str.insert(0, QString::number(history->count(), 10));// prepares for addition to history
    listItem = new QListWidgetItem(str, history); // makes new QListWidgetItem with the str QString
    history->scrollToItem(listItem,QAbstractItemView::EnsureVisible); //make sure last input is visible
    // and puts it into history, at the *last* position
    displayResult(command_item); // displays the result in the display_panel
    input_panel->clear();       //clears input panel
    input_panel->setPlaceholderText("Input command here, or close the window the exit"); // gets ready for new input
}

/**
 * @brief historySelected - triggered upon user row selection in the history list object.
 * it then updates the display_history object with the output of the row, containing a past command.
 * @note Slot method
 */
void MainWindow::historySelected() {
    int row_number = history->currentRow(); // gets the row selected
    Command selected = command_vector->at(row_number); //
    Command *item = new Command(selected); // ensures no corruption of the past command
    std::string output_string = item->generateOutput();
    display_history->setPlainText(
            fromString(output_string));
    delete item;
}

/**
 * @brief addCommand - convenience method - puts a command to the back of the vector which stores them.
 *
 * @param new_command  the command that to be added to the command vector
 */
void MainWindow::addCommand(Command &new_command) {
    command_vector->push_back(new_command);
}

/**
 *
 * @brief getCommand - a convenience method - retrieves a command from the vector which stores them,
 * based on it's index.
 * @param number the index of the command
 * @return an object of type Command
 */
Command MainWindow::getCommand(int number) {
    return command_vector->at(number);
}

/**
 *
 * @brief fromString - convenience method - converts strings from std::string to QString
 *
 * @param input a string of type std::string
 * @return a string of type QString
 */
QString MainWindow::fromString(std::string str) {
    QString output = QString::fromStdString(str);
    return output;
}

/**
 * fromInt
 * @brief convenience method - converts integers from int to QString
 *
 * @param num an int
 * @return a string of type QString
 */
QString MainWindow::fromInt(int num) {
    QString output = QString::number(num);
    return output;
}

/**
 * @brief toStd- convenience method - converts strings from QString to std::string
 *
 * @param input a string of type QString
 * @return a string of type std::string
 */
std::string MainWindow::toStd(QString input) {
    std::string output = input.toStdString();
    return output;
}


