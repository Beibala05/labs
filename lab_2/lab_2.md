# Лаба 2

## Код на C++

```C++
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <QTextBrowser>

#define MAIN_WINDOW_WIDTH  1200
#define MAIN_WINDOW_HEIGHT 750
#define BUTTON_WIDTH	   200
#define BUTTON_HEIGHT	   40
#define DIR_PATH           "/mnt/c" 

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent) : QMainWindow(parent)
    {
        centralWidget = new QWidget(this);
        this->setCentralWidget(centralWidget);
        this->setMinimumSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT + 50);

        QFont font("Arial", 12);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
        
        openFile = new QPushButton("open file", centralWidget);
        openFile->setGeometry(MAIN_WINDOW_WIDTH - BUTTON_WIDTH, MAIN_WINDOW_HEIGHT - 45, BUTTON_WIDTH, BUTTON_HEIGHT);
        openFile->setFont(font);

        QObject::connect(openFile, &QPushButton::clicked, this, &MainWindow::openFileSlot);
    }
    ~MainWindow()
    {
        delete centralWidget;
    }

protected:
    void resizeEvent(QResizeEvent* event) override
    {
        textBrowser->setGeometry(0, 0, width(), height() - 50);
        openFile->setGeometry(width() - BUTTON_WIDTH, height() - 45, BUTTON_WIDTH, BUTTON_HEIGHT);

	    QMainWindow::resizeEvent(event);

    }
	void closeEvent(QCloseEvent* event) override
    {
        delete this;
	    QMainWindow::closeEvent(event);
    }

private:
    void printText(const QString& path)
    {
        this->textBrowser->setText(path);
    }

private slots:
    void openFileSlot()
    {
        path = QFileDialog::getOpenFileName(this, "Choose file", DIR_PATH);
        printText(path);
    }

private:
    QWidget*        centralWidget;
    QTextBrowser*   textBrowser;
    QPushButton*    openFile;
    QString         path;
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow* window = new MainWindow(nullptr);
    window->show();

    return app.exec();
}
```

## Команда для компиляци
>g++ -c -pipe -O2 -Wall -Wextra -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../../lab_2 -I. -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -o main.o main.cpp
g++ -Wl,-O1 -o lab_2 main.o   /usr/lib/x86_64-linux-gnu/libQt5Widgets.so /usr/lib/x86_64-linux-gnu/libQt5Gui.so /usr/lib/x86_64-linux-gnu/libQt5Core.so -lGL -lpthread

## Запуск
> ./lab_2

# Для компиляции нужно скачать фреймворк Qt