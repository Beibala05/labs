import sys
import random
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QPushButton, QLabel, QVBoxLayout
from PyQt5.QtCore import QTimer, Qt
from PyQt5.QtGui import QFont

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.centralWidget = QWidget(self)
        self.setFixedSize(1190, 410)
        self.setCentralWidget(self.centralWidget)

        layout = QVBoxLayout(self.centralWidget)

        self.btn_1 = QPushButton("1", self)
        self.btn_2 = QPushButton("2", self)
        self.btn_3 = QPushButton("3", self)
        self.speedPlayer1 = QLabel("Speed player 1 = ", self)
        self.speedPlayer2 = QLabel("Speed player 2 = ", self)
        self.speedPlayer3 = QLabel("Speed player 3 = ", self)
        self.resPlayer1 = QLabel("1: 0/0", self)
        self.resPlayer2 = QLabel("2: 0/0", self)
        self.resPlayer3 = QLabel("3: 0/0", self)
        self.playerWin = QLabel("", self)

        for btn in [self.btn_1, self.btn_2, self.btn_3]:
            btn.setFont(QFont("Arial", 18))
            btn.setGeometry(0, 50 * (btn.text()), 50, 50)

        for label in [self.speedPlayer1, self.speedPlayer2, self.speedPlayer3, self.resPlayer1, self.resPlayer2, self.resPlayer3, self.playerWin]:
            label.setFont(QFont("Arial", 18))
            label.setAlignment(Qt.AlignCenter)

        self.movements = {self.btn_1: 0, self.btn_2: 0, self.btn_3: 0}
        self.results = {self.btn_1: 0, self.btn_2: 0, self.btn_3: 0}
        self.moving = {self.btn_1: True, self.btn_2: True, self.btn_3: True}
        
        self.speeds = {self.btn_1: self.random_speed(), self.btn_2: self.random_speed(), self.btn_3: self.random_speed()}
        self.rounds = self.random_rounds()
        self.win = ''

        self.speedPlayer1.setText(f"Speed player 1 = {self.speeds[self.btn_1]}")
        self.speedPlayer2.setText(f"Speed player 2 = {self.speeds[self.btn_2]}")
        self.speedPlayer3.setText(f"Speed player 3 = {self.speeds[self.btn_3]}")

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.logic_for_blocks)
        self.timer.start(10)

    @staticmethod
    def random_speed():
        return random.randint(1, 8)

    @staticmethod
    def random_rounds():
        return random.randint(1, 3)

    def logic_for_blocks(self):
        if not self.win:
            threads = []
            for btn in [self.btn_1, self.btn_2, self.btn_3]:
                threads.append(self.move_and_check_winner(btn))
            
            for thread in threads:
                thread.join()

            if self.win:
                self.playerWin.setStyleSheet("QLabel { background-color : green; }")
                self.playerWin.setText(self.win)

    def move_and_check_winner(self, btn):
        def thread_func():
            if not self.moving[btn]:
                self.movements[btn] -= self.speeds[btn]
            else:
                self.movements[btn] += self.speeds[btn]
    
            btn.move(self.movements[btn], btn.pos().y())

            major_dimension = self.size().width()
    
            if self.moving[btn]:
                if btn.pos().x() >= major_dimension - btn.width():
                    self.moving[btn] = False
            else:
                if btn.pos().x() <= 0:
                    self.moving[btn] = True
                    self.results[btn] += 1

                    if self.results[btn] == self.rounds:
                        self.win = f"Player {btn.text()} win"
                        return

                    self.update_player_results()

        return threading.Thread(target=thread_func)

    def update_player_results(self):
        self.resPlayer1.setText(f"1: {self.results[self.btn_1]}/{self.rounds}")
        self.resPlayer2.setText(f"2: {self.results[self.btn_2]}/{self.rounds}")
        self.resPlayer3.setText(f"3: {self.results[self.btn_3]}/{self.rounds}")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec_())