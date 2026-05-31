#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    // load a default file so it's not blank
    std::string filePath = "../code.txt";

    //https://stackoverflow.com/questions/29284643/how-to-set-an-icon-on-a-main-window-and-action-with-qt
    this->setWindowIcon(QIcon("../logo.png"));

    QWidget *container = new QWidget();
    gridLayout = new QGridLayout();

    m_textEdit = new QPlainTextEdit();
    m_pathInput = new QLineEdit();

    // buttons
    QPushButton *saveFileBtn = new QPushButton("Save");
    QPushButton *loadFileBtn = new QPushButton("Load");
    QPushButton *indentFileBtn = new QPushButton("Indent");
    QPushButton *compileFileBtn = new QPushButton("Compile");
    QPushButton *createFileBtn = new QPushButton("+");
    QPushButton *navigateBackBtn = new QPushButton("<");
    m_runFileBtn = new QPushButton("Run");


    QPlainTextEdit *newFileNameInput = new QPlainTextEdit("");
    
    

    m_terminalWidget = new TerminalWidget();
    m_codeProcess = new QProcess(parent);

    // new file creation popup
    m_newFileDialog = new CreateFileModal();

    QString loadedText = loadFile(filePath);
    m_textEdit->setPlainText(loadedText);
    m_textEdit->setMinimumSize(500,400);
   
    

    // file explorer widget
    QWidget *fileList = new QWidget();
    m_fileListWidget = loadFileList("../");

    // add widgets to the main layout (QGridLayout docs)
    gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gridLayout->addWidget(navigateBackBtn, 0, 1);
    gridLayout->addWidget(createFileBtn, 0, 2);
    gridLayout->addWidget(indentFileBtn, 0, 3);
    gridLayout->addWidget(m_pathInput, 0, 4);
    gridLayout->addWidget(loadFileBtn, 0, 5);
    gridLayout->addWidget(saveFileBtn, 0, 6);
    gridLayout->addWidget(compileFileBtn, 0, 7);
    gridLayout->addWidget(m_runFileBtn, 0, 8);
    gridLayout->addWidget(m_textEdit, 1, 1, 1,8);
    gridLayout->addWidget(m_terminalWidget, 2, 1, 1,8);
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

    // Compile button functionality
    QObject::connect(compileFileBtn, &QPushButton::clicked , this, [this]() {
        compileFile(m_filePath.toStdString());
        updateFileList();
    });

    // Run file button functionality
    QObject::connect(m_runFileBtn, &QPushButton::clicked , this, [this]() {
        runFile();
    });


    // File Running Process
    QObject::connect(m_codeProcess, &QProcess::started , this, [this]() {
        std::cout << "started running the file" << std::endl;
        m_runFileBtn->setText("Stop");
       // std::cout << m_codeProcess->readAllStandardOutput().toStdString() << std::endl;
    });


    // update the terminal widget to reflect process output
    QObject::connect(m_codeProcess, &QProcess::readyRead , this, [this]() {
        // std::cout << m_codeProcess->readAllStandardOutput().toStdString() << std::endl;
        QByteArray dataIn = m_codeProcess->readAll();
        

            /*
            QDataStream stream(&dataIn, QIODevice::ReadOnly);
            stream.setVersion(QDataStream::Qt_4_0);
             
        
            QString data;
           */

        // tried doing it through streams but ultimately gave up after too much time, instead the output is loaded in one chunk.
        std::cout << "data" << std::endl;
        std::cout << dataIn.toStdString() << std::endl;  
        m_terminalWidget->setText(m_terminalWidget->text() + QString::fromStdString(dataIn.toStdString()));  
    });

    // signal the process is over
    QObject::connect(m_codeProcess, &QProcess::finished , this, [this]() {
        m_runFileBtn->setText("Run");
    });

    // prompt file creation window
    QObject::connect(createFileBtn, &QPushButton::clicked , this, [this]() {
        m_newFileDialog->show();
    });

    // updates folder path to one directory back
    QObject::connect(navigateBackBtn, &QPushButton::clicked , this, [this]() {
       // remove the last folder from the path
        std::string path = m_folderPath.toStdString();

        if (path.find_last_of('\\') != -1)
            m_folderPath = QString::fromStdString(path.substr(0,path.find_last_of('\\'))); // windows file system
        else
            m_folderPath = QString::fromStdString(path.substr(0,path.find_last_of('/'))); // everyone else
        
        updateFileList();
    });


    // handle file creation once the prompt is complete
    QObject::connect(m_newFileDialog, &QInputDialog::textValueSelected , this, [this](const QString &fileName) {
        std::cout << fileName.toStdString() << std::endl;

        createFile(fileName.toStdString(), m_folderPath.toStdString());
        updateFileList();
    });

    container->setLayout(gridLayout);
    setCentralWidget(container);
}





// refreshes the list of files
void MainWindow::updateFileList()
{
    QListWidget *replacingWidget = loadFileList(m_folderPath.toStdString());

    gridLayout->replaceWidget(m_fileListWidget, replacingWidget);
    m_fileListWidget = replacingWidget;

    QObject::connect(m_fileListWidget, &QListWidget::itemClicked, this, onFileListItemClicked);
}

// runs the compiled file
void MainWindow::runFile()
{
    QStringList args;
    
    // pass the the java file as the command argument
    args << m_filePath;
    
    // starts the java command process
    m_codeProcess->start(QString::fromStdString("java"), args);
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

