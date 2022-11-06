/**
 * @Author: https://github.com/Jon-AL
 * @FileName: mainwindow.h
 * @FileContents: the header eeefor the MainWindow object, this is the "real" main
 *                Takes care of the input and output from the user.
 *                Enabled: user pressing enter and/or the compute button to submit input.
 *                         user can click (one click, single selection is enabled) on the list widget to immediately display the contents of the (past) command used
 *                         It will not erase nor re-calculate the command, nor input it into the line editor.
 * @LastUpdated: Oct. 9, 2021
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QListWidgetItem>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "command.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QPushButton *m_button;
private:
    QLineEdit *input_panel;
private:
    QTextEdit *display_history;
private:
    QLabel *title_label;
private:
    QLabel *side_note;
private:
    QLabel *status_label;
private:
    QLabel *command_history;
private:
    QLabel *command_instruction;
private:
    QLabel *input_instruction;
private:
    QTextEdit *display;
private:
    QListWidget *history;
private:
    QListWidgetItem *listItem;
private:
    QString *q_str;
private:
    std::vector <Command> *command_vector;
private:
    Command *command_item;


private
    slots:
            void updateStatus(int
    status);

private
    slots: void displayResult(Command * input);
private
    slots:
            void processInput();
private
    slots:
            void historySelected();


private:
    void addCommand(Command &new_command);

private:
    Command getCommand(int number);

private:
    QString fromString(std::string str);

private:
    QString fromInt(int num);

private:
    std::string toStd(QString input);

};

#endif // MAINWINDOW_H
