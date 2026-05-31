#include "terminalwidget.h";

TerminalWidget::TerminalWidget(QWidget *parent) : QScrollArea(parent) {

    QWidget *terminalContent = new QWidget(this);
    QVBoxLayout *terminalLayout = new QVBoxLayout(terminalContent);
    this->setMinimumSize(500,100);
    this->setWidgetResizable(true);
    terminalContent->setMinimumSize(500,100);
    
    

    terminalText = new QLabel(terminalContent);
    terminalText->setWordWrap(true);
    terminalLayout->addWidget(terminalText);


    this->setWidget(terminalText);
}

void TerminalWidget::setText(QString text)
{
    terminalText->setText(text);
}

QString TerminalWidget::text()
{
    return terminalText->text();
}