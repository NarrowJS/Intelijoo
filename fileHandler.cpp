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

    int lineNum = 0;
    int openBraceCount = 0;
    int indentMultiplier = 0;

    FileReader.open(filePath, ios::in);

    if (FileReader.is_open())
    {
        string line;
        while (getline(FileReader, line))
        {
            cout << line << endl;

            lineNum++;

            // remove any spaces at the front of the line to have clean indents
            while (line.substr(0, 1) == " ")
            {
                line = line.substr(1, line.length() - 1);
                cout << "line_"+line << endl;
            }

            // saving the unpadded string state
            string lineTemp = line;
            
            cout << indentMultiplier << endl;

           // update the amount of spaces based on how nested the line is
            for (int i = 0; i<indentMultiplier; i++)
            {
                line = "    " + line;
            }

            cout << "linetemp:"+lineTemp << endl;

            // find instead of == to account for any trailing spaces after the braces
            if (lineTemp.find("{") != -1)
            {
                indentMultiplier++;  
                cout << "increased multiplier" << endl;
            } else if (lineTemp.find("}") != -1)
            {
                indentMultiplier--; 
                cout << "decreased multiplier" << endl;
                
                if (indentMultiplier > 0)
                {
                    for (int i = 0; i<indentMultiplier; i++)
                    {
                        line = "    " + lineTemp;
                    }
                } else {
                    line = lineTemp;
                }
            }

            // save the line
            data+= line + "\n";
            
        }
        FileReader.close();
    }

    return data;
}


int compileFile(string path)
{   
    const string command = "javac "+path;
    int res = system(command.c_str());

    if (res == 0)
        cout << "success" << endl;
    else
        cout << "compile failed" << endl;

    return 0;
}

int runFile(string path)
{   
    const string command = "java "+path;
    int res = system(command.c_str());

    if (res == 0)
        cout << "success" << endl;
    else
        cout << "compile failed" << endl;

    return 0;
}


void createFile(string fileName, string folderPath)
{
    ofstream file;

    string path = folderPath + "\\" + fileName;
    file.open(path);

    if (!file.is_open())
    {
        return;
    }

    file.close();


    
}