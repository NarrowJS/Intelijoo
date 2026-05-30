#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {


    std::string filePath = "../code.txt";


    QWidget *container = new QWidget();
    gridLayout = new QGridLayout();

    

    QPushButton *saveFileBtn = new QPushButton("Save");

    m_textEdit = new QPlainTextEdit();

    m_pathInput = new QLineEdit();

    QPushButton *loadFileBtn = new QPushButton("Load");

    QPushButton *indentFileBtn = new QPushButton("Indent");

    QPushButton *compileFileBtn = new QPushButton("Compile");

    QPushButton *runFileBtn = new QPushButton("Run");


    QPlainTextEdit *newFileNameInput = new QPlainTextEdit("");
    QPushButton *createFileBtn = new QPushButton("+");

    m_newFileDialog = new CreateFileModal();



    QString loadedText = loadFile(filePath);
    m_textEdit->setPlainText(loadedText);
    m_textEdit->setMinimumSize(500,400);


    // go back one directory
    QPushButton *navigateBackBtn = new QPushButton("<");


    QWidget *fileList = new QWidget();

    m_fileListWidget = loadFileList("../");


    gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gridLayout->addWidget(navigateBackBtn, 0, 1);
    gridLayout->addWidget(createFileBtn, 0, 2);
    gridLayout->addWidget(indentFileBtn, 0, 3);
    gridLayout->addWidget(m_pathInput, 0, 4);
    gridLayout->addWidget(loadFileBtn, 0, 5);
    gridLayout->addWidget(saveFileBtn, 0, 6);
    gridLayout->addWidget(compileFileBtn, 0, 7);
    gridLayout->addWidget(runFileBtn, 0, 8);
    gridLayout->addWidget(m_textEdit, 1, 1, 1,8);
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
        updateFileList();

    });

    // Indent file button functionality
    QObject::connect(indentFileBtn, &QPushButton::clicked , this, [this]() {
        std::string data = autoIndent(m_filePath.toStdString());
        m_textEdit->setPlainText(QString::fromStdString(data));

        saveFile(m_filePath.toStdString(), m_fileText.toStdString());

    });

    // Link the file list item click event to update the current file path
    QObject::connect(m_fileListWidget, &QListWidget::itemClicked, this, onFileListItemClicked);

    // Save file button functionality
    QObject::connect(saveFileBtn, &QPushButton::clicked , this, [this]() {
        saveFile(m_filePath.toStdString(), m_fileText.toStdString());
       
    });

    QObject::connect(compileFileBtn, &QPushButton::clicked , this, [this]() {
        compileFile(m_filePath.toStdString());
        updateFileList();
    });

    QObject::connect(runFileBtn, &QPushButton::clicked , this, [this]() {
        compileFile(m_filePath.toStdString());
    });

    QObject::connect(createFileBtn, &QPushButton::clicked , this, [this]() {
        m_newFileDialog->show();
    });

    QObject::connect(navigateBackBtn, &QPushButton::clicked , this, [this]() {

       // remove the last folder from the path
        std::string path = m_folderPath.toStdString();
        m_folderPath = QString::fromStdString(path.substr(0,path.find_last_of('\\')));
        updateFileList();

    });


    QObject::connect(m_newFileDialog, &QInputDialog::textValueSelected , this, [this](const QString &fileName) {
        std::cout << fileName.toStdString() << std::endl;

        createFile(fileName.toStdString(), m_folderPath.toStdString());
        updateFileList();

    });

    container->setLayout(gridLayout);
    setCentralWidget(container);
    

}

void MainWindow::updateFileList()
{
    QListWidget *replacingWidget = loadFileList(m_folderPath.toStdString());

    gridLayout->replaceWidget(m_fileListWidget, replacingWidget);
    m_fileListWidget = replacingWidget;

    QObject::connect(m_fileListWidget, &QListWidget::itemClicked, this, onFileListItemClicked);
}



// Replace old file list with the new one by reloading it 
void MainWindow::onFileListItemClicked(QListWidgetItem *item) {
    std::string itemText = item->text().toStdString();
    m_filePath = QString::fromStdString(m_folderPath.toStdString() + itemText);

    std::cout << m_filePath.toStdString() << std::endl;

    // check if the item is a folder
    if (!m_filePath.contains("."))
    {
        m_folderPath = m_filePath;
        updateFileList();

    } else {
        m_textEdit->setPlainText(loadFile(m_filePath.toStdString()));
    }
};

