
## Intelijoo
A bare-bones Java IDE built with C++ and the QT6 UI Library.

### Features
- File explorer with the ability to traverse folder trees
- Auto code indentation
- Easy Java compilation with one click
- Load / Save files
### Usage
To run the executable, go to the releases tab and download the latest release which is available for Linux, MacOS, and Windows.

### Building from source
1. Ensure you have the g++ compiler installed. 
2. Clone the repository to your computer and navigate into the root directory of the project
3. Execute the following command:
	`g++ compile`
4. Run the compiled file located in the build directory

### Challenges
- Figuring out how to structure the project and understanding the role of the various widgets (ex. MainWindow needs to act as the root for the rest of the components to work)
- Designing the auto indentation algorithm. At first I went with a design that simply finds lines that end with semi-colons and just indented them, but I quickly realized that this solution wouldn't work for most case, so instead I decided to search for open and close braces and indenting what was inside of them.
- Reconstructing the file path from the file list items in the file explorer (part of the function where the user clicks on the "file" and it gets loaded in)
- Handling Windows vs Unix file system paths (\\\ shouldn't exist)
- Streaming file data
### What was interesting?
- Building the file navigation side bar helped me better understand how a file explorer works, something that you don't really have to ever design because it's built into the OS.
- Figuring out how to design the auto indentation made me realize how much people take that feature for granted, since kind of like choosing a random number, while it may be easy for a human to decide what to indent / not indent, the program has to handle all sorts of edge cases in order to have a pretty output. It sounds easy but it can get really complex.
### What I would add
- Color coded text for readability
- Support for more languages
- Folder / file icons
- Tab to complete
- Line numbers
- Highlighting syntax errors in the editor
### Sources
- QT6 UI
	- PushButton: https://doc.qt.io/qt-6/qpushbutton.html
	- QPlainTextEdit: https://doc.qt.io/qt-6/qplaintextedit.html
	- Signals: https://doc.qt.io/qt-6/signalsandslots.html
	- QLineEdit: https://doc.qt.io/qt-6/qlineedit.html
	- QListView: https://doc.qt.io/qt-6/qml-qtquick-listview.html
	- Calculator example app: https://doc.qt.io/qt-6/qtdoc-demos-calqlatr-example.html
	- Creating background processes: https://doc.qt.io/qt-6/qprocess.html
- File handling
	- Reading and Writing to files: https://www.youtube.com/watch?v=Cz4fl-TUjVk
	- Streams: https://www.udacity.com/blog/c-streams/
	- Running shell scripts: https://www.geeksforgeeks.org/cpp/system-call-in-c/
	- Conversion: https://www.geeksforgeeks.org/cpp/convert-string-char-array-cpp/
	- Create file: https://www.geeksforgeeks.org/cpp/c-program-to-create-a-file/
