#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QTimer>   
#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QPoint>
#include <QObject>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <ctime>

class MainWindow;

size_t randomSpeed()
{
    return rand() % 8 + 1;
}

int randomRounds()
{
    return rand() % 3 + 1;
}

namespace GameLogic
{
    inline void thread_1(MainWindow* obj);
    inline void thread_2(MainWindow* obj);
    inline void thread_3(MainWindow* obj);
}
 
enum Sizes : int
{
    MAIN_WINDOW_WIDTH  = 1190,
    MAIN_WINDOW_HEIGHT = 410 
};

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent) : QMainWindow(parent)
    {
        centralWidget = new QWidget(this);

        this->setFixedSize(Sizes::MAIN_WINDOW_WIDTH, Sizes::MAIN_WINDOW_HEIGHT);
        this->setCentralWidget(centralWidget);

        btn_1 = new QPushButton("1", centralWidget);
        btn_1->setFont(QFont("Arial", 18));
        btn_1->setGeometry(0, 50, 50, 50);

        btn_2 = new QPushButton("2", centralWidget);
        btn_2->setFont(QFont("Arial", 18));
        btn_2->setGeometry(0, 150, 50, 50);

        btn_3 = new QPushButton("3", centralWidget);
        btn_3->setFont(QFont("Arial", 18));
        btn_3->setGeometry(0, 250, 50, 50);

        speedPlayer1 = new QLabel(centralWidget);
        speedPlayer1->setGeometry(10, 350, 240, 50);
        speedPlayer1->setFont(QFont("Arial", 18));
        speedPlayer1->setStyleSheet("QLabel { background-color : red; }");
        speedPlayer1->setAlignment(Qt::AlignCenter);
        speedPlayer1->setText("Speed player 1 = " + QString::number(static_cast<qulonglong>(this->speedBtn1)));

        speedPlayer2 = new QLabel(centralWidget);
        speedPlayer2->setGeometry(260, 350, 240, 50);
        speedPlayer2->setFont(QFont("Arial", 18));
        speedPlayer2->setStyleSheet("QLabel { background-color : red; }");
        speedPlayer2->setAlignment(Qt::AlignCenter);
        speedPlayer2->setText("Speed player 2 = " + QString::number(static_cast<qulonglong>(this->speedBtn2)));

        speedPlayer3 = new QLabel(centralWidget);
        speedPlayer3->setGeometry(510, 350, 240, 50);
        speedPlayer3->setFont(QFont("Arial", 18));
        speedPlayer3->setStyleSheet("QLabel { background-color : red; }");
        speedPlayer3->setAlignment(Qt::AlignCenter);
        speedPlayer3->setText("Speed player 3 = " + QString::number(static_cast<qulonglong>(this->speedBtn3)));

        resPlayer1 = new QLabel(centralWidget);
        resPlayer1->setGeometry(760, 350, 80, 50);
        resPlayer1->setFont(QFont("Arial", 18));
        resPlayer1->setStyleSheet("QLabel { background-color : blue; }");
        resPlayer1->setAlignment(Qt::AlignCenter);
        resPlayer1->setText("1:  0/0");

        resPlayer2 = new QLabel(centralWidget);
        resPlayer2->setGeometry(850, 350, 80, 50);
        resPlayer2->setFont(QFont("Arial", 18));
        resPlayer2->setStyleSheet("QLabel { background-color : blue; }");
        resPlayer2->setAlignment(Qt::AlignCenter);
        resPlayer2->setText("2:  0/0");

        resPlayer3 = new QLabel(centralWidget);
        resPlayer3->setGeometry(940, 350, 80, 50);
        resPlayer3->setFont(QFont("Arial", 18));
        resPlayer3->setStyleSheet("QLabel { background-color : blue; }");
        resPlayer3->setAlignment(Qt::AlignCenter);
        resPlayer3->setText("3:  0/0");

        playerWin = new QLabel(centralWidget);
        playerWin->setGeometry(1030, 350, 150, 50);
        playerWin->setAlignment(Qt::AlignCenter);
        playerWin->setFont(QFont("Arial", 18));

        timer = new QTimer(this);

        QObject::connect(timer, &QTimer::timeout, this, &MainWindow::logicForBlocks);
        timer->start(10);
    }
    ~MainWindow()
    {   
        delete btn_1;
        delete btn_2;
        delete btn_3;

        delete timer;
    }   

private slots:
    void logicForBlocks()
    {
        if (win.isEmpty())
        {
            std::thread __th1(GameLogic::thread_1, this);
            std::thread __th2(GameLogic::thread_2, this);
            std::thread __th3(GameLogic::thread_3, this);

            __th1.join();
            __th2.join();
            __th3.join();

            btn_1->setGeometry(move_1,  50, 50, 50);
            btn_2->setGeometry(move_2, 150, 50, 50);
            btn_3->setGeometry(move_3, 250, 50, 50);

            this->resPlayer1->setText("1:  " + QString::number(static_cast<qulonglong>(this->res_1)) + "/" + QString::number(static_cast<qulonglong>(this->rounds)));
            this->resPlayer2->setText("2:  " + QString::number(static_cast<qulonglong>(this->res_2)) + "/" + QString::number(static_cast<qulonglong>(this->rounds)));
            this->resPlayer3->setText("3:  " + QString::number(static_cast<qulonglong>(this->res_3)) + "/" + QString::number(static_cast<qulonglong>(this->rounds)));
        }
        else
        {   
            this->playerWin->setStyleSheet("QLabel { background-color : green; }");
            this->playerWin->setText(this->win);

            return;
        }
    }

public:
    int     move_1   = 0;
    int     move_2   = 0;
    int     move_3   = 0;
    int     res_1    = 0;
    int     res_2    = 0;
    int     res_3    = 0;
    bool    moving_1 = true;
    bool    moving_2 = true;
    bool    moving_3 = true;
    QString win;

public:
    [[nodiscard]] auto getAxisXFromBtn1() const {return this->btn_1->pos().x();}
    [[nodiscard]] auto getAxisXFromBtn2() const {return this->btn_2->pos().x();}
    [[nodiscard]] auto getAxisXFromBtn3() const {return this->btn_3->pos().x();}

    size_t speedBtn1 = randomSpeed();
    size_t speedBtn2 = randomSpeed();
    size_t speedBtn3 = randomSpeed();
    int    rounds    = randomRounds();

private:
    QWidget*     centralWidget;
    QTimer*      timer;
    QPushButton* btn_1;
    QPushButton* btn_2;
    QPushButton* btn_3;
    QLabel*      speedPlayer1;
    QLabel*      speedPlayer2;
    QLabel*      speedPlayer3;
    QLabel*      resPlayer1;
    QLabel*      resPlayer2;
    QLabel*      resPlayer3;
    QLabel*      playerWin;
};

namespace GameLogic
{
    inline void thread_1(MainWindow* obj)
    {
        if (!obj->moving_1)
            obj->move_1 -= obj->speedBtn1;
        else
            obj->move_1 += obj->speedBtn1;
        

        if (obj->moving_1)
        {
            if (obj->getAxisXFromBtn1() >= Sizes::MAIN_WINDOW_WIDTH)
                obj->moving_1 = false;
        }
        else
        {
            if (obj->getAxisXFromBtn1() <= 0)
            {
                obj->moving_1 = true;

                if (obj->res_1 + 1 == obj->rounds)
                {
                    obj->win = "Player 1 win";
                    obj->res_1++;
                    return;
                }
                else
                {
                    obj->res_1++;
                }
            }
        }
    }

    inline void thread_2(MainWindow* obj)
    {
        if (!obj->moving_2)
            obj->move_2 -= obj->speedBtn2;
        else
            obj->move_2 += obj->speedBtn2;
        

        if (obj->moving_2)
        {
            if (obj->getAxisXFromBtn2() >= Sizes::MAIN_WINDOW_WIDTH)
                obj->moving_2 = false;
        }
        else
        {
            if (obj->getAxisXFromBtn2() <= 0)
            {
                obj->moving_2 = true;

                if (obj->res_2 + 1 == obj->rounds)
                {
                    obj->win = "Player 2 win";
                    obj->res_2++;
                    return;
                }
                else
                {
                    obj->res_2++;
                }
            }
        }
    }

    inline void thread_3(MainWindow* obj)
    {
        if (!obj->moving_3)
            obj->move_3 -= obj->speedBtn3;
        else
            obj->move_3 += obj->speedBtn3;
        

        if (obj->moving_3)
        {
            if (obj->getAxisXFromBtn3() >= Sizes::MAIN_WINDOW_WIDTH)
                obj->moving_3 = false;
        }
        else
        {
            if (obj->getAxisXFromBtn3() <= 0)
            {
                obj->moving_3 = true;

                if (obj->res_3 + 1 == obj->rounds)
                {
                    obj->win = "Player 3 win";
                    obj->res_3++;
                    return;
                }
                else
                {
                    obj->res_3++;
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    QApplication app(argc, argv);

    MainWindow obj(nullptr);
    obj.show();

    return app.exec();
}