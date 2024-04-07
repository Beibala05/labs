#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QSharedPointer>

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent) : QMainWindow(parent)
    {
        centralWidget = new QWidget(this);

        this->setFixedSize(1200, 800);
        this->setCentralWidget(centralWidget);

        QString styleSheet = "QLineEdit { font-size: 16pt; text-align: center; }";

        writer = new QLineEdit(centralWidget);
        writer->setStyleSheet(styleSheet);
        writer->setPlaceholderText("Введите текст...");
        writer->setAlignment(Qt::AlignCenter); 
        writer->setGeometry(25, 350, 1150, 100);

        this->show();
    }
    std::string getTextFromWriter() const
    {
        return this->writer->text().toStdString();
    }

private:
    QLineEdit*  writer;
    QWidget*    centralWidget;
};

void reader(QSharedPointer<MainWindow> mainWindowObj)
{
    while (true)
    {
        std::string text = mainWindowObj->getTextFromWriter();

        if (text.size() != 0)
        {
            std::cout << "Writer: " << text << std::endl;
            std::string reversed_text(text.rbegin(), text.rend());
            std::cout << "Reader: " << reversed_text << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QSharedPointer<MainWindow> mainWindowObj(new MainWindow(nullptr));
    
    std::thread __th(reader, mainWindowObj);

    __th.detach();

    return app.exec();
}