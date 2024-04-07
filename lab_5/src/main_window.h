#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QWidget>
#include <QDir>
#include <QFileInfoList>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QIcon>
#include <QListWidgetItem>
#include <QMessageBox>

#define DEBUG_OFF
#define MAIN_WINDOW_WIDTH  1200
#define MAIN_WINDOW_HEIGHT 750
#define BUTTON_WIDTH	   100
#define BUTTON_HEIGHT	   40
#define START_PATH		   "/mnt/c"
#define FOLDER_ICON_PATH   "../res/folder_icon.png"
#define FILE_ICON_PATH	   "../res/file_icon.png"

class MainWindow final : public QMainWindow
{
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	void print(const QString& path);

protected:
	void resizeEvent(QResizeEvent* event) override;
	void closeEvent(QCloseEvent* event)   override;

private slots:
	void nextSlot();
	void prevSlot();

private:
	QListWidget*	 fileManager;
	QWidget*		 centralWidget;
	QPushButton*	 next;
	QPushButton*	 prev;
	QString			 path;
	QVector<QString> pathes;
};