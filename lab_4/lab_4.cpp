#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QSharedPointer>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QDebug>

std::mutex      mtx;
QString         totalRes1 = "";
QString         totalRes2 = "";

class MainWindow : public QMainWindow
{
public:
        explicit MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) 
        {
                centralWidget = new QWidget(this);

                this->setFixedSize(1200, 800);
                this->setCentralWidget(centralWidget);

                QString styleSheet = "QLineEdit { font-size: 16pt; text-align: center; }";

                writers = new QPushButton("writers", centralWidget);
                writers->setStyleSheet("font-size: 16px;");
                writers->setGeometry(5, 200, (1200 - 10) / 2, 80);

                readers = new QPushButton("readers", centralWidget);
                readers ->setStyleSheet("font-size: 16px;");
                readers->setGeometry(((1200 - 10) / 2) + 5, 200, (1200 - 10) / 2, 80);

                printDataFronWriters = new QPushButton("print data from writers", centralWidget);
                printDataFronWriters ->setStyleSheet("font-size: 16px;");
                printDataFronWriters->setGeometry(1200 - 200 - 5, 800 - 50 - 5, 200, 50);

                textBox1 = new QLineEdit(centralWidget);
                textBox1->setStyleSheet("font-size: 16px;");
                textBox1->setPlaceholderText("Введите текст...");
                textBox1->setAlignment(Qt::AlignCenter); 
                textBox1->setGeometry(((1200 - 10) / 2) + 5, 290, (1200 - 10) / 2, 80);

                textBox2 = new QLineEdit(centralWidget);
                textBox2->setStyleSheet("font-size: 16px;");
                textBox2->setPlaceholderText("Введите текст...");
                textBox2->setAlignment(Qt::AlignCenter); 
                textBox2->setGeometry(((1200 - 10) / 2) + 5, 380, (1200 - 10) / 2, 80);

                label1 = new QLabel(centralWidget);
                label1->setStyleSheet("font-size: 16px;");
                label1->setAlignment(Qt::AlignCenter); 
                label1->setGeometry(5, 290, (1200 - 10) / 2, 80);

                label2 = new QLabel(centralWidget);
                label2->setStyleSheet("font-size: 16px;");
                label2->setAlignment(Qt::AlignCenter); 
                label2->setGeometry(5, 380, (1200 - 10) / 2, 80);

                QObject::connect(writers, &QPushButton::clicked, this, &MainWindow::writerSlot);
                QObject::connect(readers, &QPushButton::clicked, this, &MainWindow::readerSlot);
                QObject::connect(printDataFronWriters, &QPushButton::clicked, this, &MainWindow::printDataFronWritersSlot);
        }
        void writer1()
        {
                mtx.lock();
                totalRes1 = textBox1->text();
                mtx.unlock();
        }
        void writer2()
        {
                mtx.lock();
                totalRes2 = textBox2->text();
                mtx.unlock();
        }
        void reader1()
        {
                mtx.lock();
                label1->setText(totalRes1);
                totalRes1 = "";
                mtx.unlock();
        }
        void reader2()
        {
                mtx.lock();
                label2->setText(totalRes2);
                totalRes2 = "";
                mtx.unlock();
        }

public slots:
        void writerSlot()
        {
                writer1();
                writer2();
        }
        void readerSlot()
        {
                reader1();
                reader2();
        }
        void printDataFronWritersSlot()
        {
                qDebug() << totalRes1;
                qDebug() << totalRes2;
        }

private:
        QLineEdit*              textBox1;
        QLineEdit*              textBox2;
        QLabel*                 label1;
        QLabel*                 label2;
        QWidget*                centralWidget;
        QPushButton*            readers;
        QPushButton*            writers;
        QPushButton*            printDataFronWriters;
};

int main(int argc, char** argv)
{
        QApplication app(argc, argv);

        MainWindow window;
        window.show();

        mtx.lock();
        mtx.unlock();

        return app.exec();
}