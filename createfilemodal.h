#ifndef CREATEFILEMODAL_H
#define CREATEFILEMODAL_H



#include <QInputDialog>
#include <QWidget>
#include <QApplication>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>


class CreateFileModal : public QInputDialog {
    Q_OBJECT
    public:
        CreateFileModal(QWidget *parent = nullptr);
        
        
};

#endif