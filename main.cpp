#include <QApplication>
#include <QPushButton>
#include <QPlainTextEdit>
#include <iostream>
#include "fileHandler.h"
#include <string>
#include <QString>
#include <QGridLayout>
#include <QLayout>
#include <QLineEdit>
#include <QObject>
#include "mainwindow.h"



int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    MainWindow window;
    window.show();
    
    return app.exec();
}