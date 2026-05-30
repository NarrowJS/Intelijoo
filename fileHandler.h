

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include<string>
#include<QString>
#include<QListWidget>
#include <QListWidgetItem>

QString loadFile(std::string filePath);
QListWidget *loadFileList(std::string folderPath);
void saveFile(std::string filePath, std::string data);
std::string autoIndent(std::string filePath);
int compileFile(std::string path);
int runFile(std::string path);
void createFile(std::string name, std::string path);

#endif