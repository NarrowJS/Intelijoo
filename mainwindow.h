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

class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
    
    public slots:
        void onFileListItemClicked(QListWidgetItem *item);
    
    private:
        QLineEdit *m_pathInput;
        QPlainTextEdit *m_textEdit;
        QString m_folderPath;
        QString m_filePath;
        QString m_fileText;
        QListWidget *m_fileListWidget;
        QGridLayout *gridLayout;

    
        
};