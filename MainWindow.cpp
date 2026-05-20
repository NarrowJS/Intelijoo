#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {


    std::string filePath = "../code.txt";


    QWidget *container = new QWidget();
    gridLayout = new QGridLayout();

    

    QPushButton *saveFileBtn = new QPushButton("Save");
    saveFileBtn->show();

    m_textEdit = new QPlainTextEdit();
    m_textEdit->show();

    m_pathInput = new QLineEdit();
    m_pathInput->show();

    QPushButton *loadFileBtn = new QPushButton("Load");
    loadFileBtn->show();

    QPushButton *compileFileBtn = new QPushButton("Compile");
    compileFileBtn->show();

    QString loadedText = loadFile(filePath);
    m_textEdit->setPlainText(loadedText);


    QWidget *fileList = new QWidget();

    m_fileListWidget = loadFileList("../");


    gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gridLayout->addWidget(m_pathInput, 0, 1);
    gridLayout->addWidget(loadFileBtn, 0, 2);
    gridLayout->addWidget(saveFileBtn, 0, 3);
    gridLayout->addWidget(compileFileBtn, 0, 4);
    gridLayout->addWidget(m_textEdit, 1, 1, 1, 4);
    gridLayout->addWidget(m_fileListWidget, 0,0, 0, 1);


    // Update folder path variable
    QObject::connect(m_pathInput, &QLineEdit::textChanged, this, [this](const QString &newPath) {
        m_folderPath = newPath;
    });

    // update the file text variable
    QObject::connect(m_textEdit, &QPlainTextEdit::textChanged, this, [this]() {
        m_fileText = m_textEdit->toPlainText();
    });


    // Load file button functionality
    QObject::connect(loadFileBtn, &QPushButton::clicked , this, [this]() {
        QWidget *updatedFileListWidget = new QWidget();
        QListWidget *replacingWidget = loadFileList(m_folderPath.toStdString());
       

        gridLayout->replaceWidget(m_fileListWidget, replacingWidget);
        m_fileListWidget = replacingWidget;

        QObject::connect(m_fileListWidget, &QListWidget::itemClicked, this, onFileListItemClicked);

    });

    // Link the file list item click event to update the current file path
    QObject::connect(m_fileListWidget, &QListWidget::itemClicked, this, onFileListItemClicked);

    // Save file button functionality
    QObject::connect(saveFileBtn, &QPushButton::clicked , this, [this]() {
        saveFile(m_filePath.toStdString(), m_fileText.toStdString());
       
    });

  

    container->setLayout(gridLayout);
    setCentralWidget(container);

}


// Replace old file list with the new one by reloading it 
void MainWindow::onFileListItemClicked(QListWidgetItem *item) {
    std::string itemText = item->text().toStdString();
    m_filePath = QString::fromStdString(m_folderPath.toStdString() + itemText);

    std::cout << m_filePath.toStdString() << std::endl;
    m_textEdit->setPlainText(loadFile(m_filePath.toStdString()));
};