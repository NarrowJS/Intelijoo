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
#include <QListWidget>
#include <QMainWindow>
#include <QListWidgetItem>
#include <regex>
#include <QDialog>
#include <QProcess>
#include <QLabel>
#include <QDataStream>
#include <QByteArray>
#include <QVBoxLayout>
#include <QScrollArea>

#include "createfilemodal.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
    
    public slots:
        void onFileListItemClicked(QListWidgetItem *item);
        void updateFileList();
        void runFile();
        void updateTerminal(std::string text);
    
    private:
        QLineEdit *m_pathInput;
        QPlainTextEdit *m_textEdit;
        QString m_folderPath;
        QString m_filePath;
        QString m_fileText;
        QListWidget *m_fileListWidget;
        QGridLayout *gridLayout;
        CreateFileModal *m_newFileDialog;
        QProcess *m_codeProcess;
        QPushButton *m_runFileBtn;
        QLabel *m_terminalWidget;

    
        
};