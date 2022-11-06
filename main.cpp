/**
 * @Author: https://github.com/Jon-AL
 * @FileName: main.cpp
 * @FileContents: main control of the application. Does relatively little.
 * @LastUpdated: Oct. 9, 2021
 */


#include <QApplication>
#include "mainwindow.h"

/**
 * main
 * @Description Main function, a wrapper of MainWindow.
 *
 * @param argc no input required
 * @param argv no input required
 * @return     nothing, really
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.showMaximized();
    return app.exec();
}