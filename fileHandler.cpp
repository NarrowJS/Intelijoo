#include "fileHandler.h"
#include <fstream>
#include <string>
#include <iostream>
#include <QString>
#include <QListWidgetItem>
#include <QListWidget>
#include <filesystem>
#include <regex>

using namespace std;

QString loadFile(string filePath)
{
    QString data = "";
    fstream FileReader;
    FileReader.open(filePath, ios::in);

    if (FileReader.is_open())
    {
        string line;
        while (getline(FileReader, line))
        {
            cout << line << endl;
            data += line + "\n";
        }
        FileReader.close();
    }

    return data;
}

QListWidget *loadFileList(string folderPath)
{
    QListWidget *fileList = new QListWidget();



    for (const auto & entry : filesystem::directory_iterator(folderPath))
    {
        std::cout << entry.path() << std:: endl;
        QListWidgetItem *fileItem = new QListWidgetItem();
        string fileTitle = entry.path().string();

        fileItem->setText(QString::fromStdString((fileTitle.substr(folderPath.length()))));
        fileList->addItem(fileItem);
    }

    return fileList;
}


void saveFile(string filePath, string data)
{
    fstream FileWriter;
    FileWriter.open(filePath, ios::out);

    if (FileWriter.is_open())
    {
        FileWriter << data;
    }
}





string autoIndent(string filePath)
{
    string data = "";
    fstream FileReader;

    int indentMultiplier = 0;
    FileReader.open(filePath, ios::in);

    if (FileReader.is_open())
    {
        string line;
        while (getline(FileReader, line))
        {
            cout << line << endl;

           
           if (line == "{")
           {
            indentMultiplier++;
           } else if (line == "}")
           {
            indentMultiplier--;
           }

           for (int i = 0; i<indentMultiplier; i++)
            {
                line = "   " + line;
            }

            data+= line + "\n";
            
        }
        FileReader.close();
    }

    return data;
}


