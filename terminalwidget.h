
#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>

class TerminalWidget : public QScrollArea {
    Q_OBJECT
    public:
        TerminalWidget(QWidget *parent = nullptr);
    public slots:
        void setText(QString text);
        QString text();
    private:
        QLabel *terminalText;
};

#endif