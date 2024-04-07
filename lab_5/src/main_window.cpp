#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	centralWidget = new QWidget(this);
	this->setCentralWidget(centralWidget);

	QFont font("Arial", 12);

	fileManager = new QListWidget(centralWidget);
	fileManager->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	fileManager->setFont(font);
	
	next = new QPushButton("next", centralWidget);
	next->setGeometry(MAIN_WINDOW_WIDTH - 100, MAIN_WINDOW_HEIGHT + 5, BUTTON_WIDTH, BUTTON_HEIGHT);
	next->setFont(font);

	prev = new QPushButton("prev", centralWidget);
	prev->setGeometry(MAIN_WINDOW_WIDTH - 205, MAIN_WINDOW_HEIGHT + 5, BUTTON_WIDTH, BUTTON_HEIGHT);
	prev->setFont(font);

	print(START_PATH);

	path = START_PATH;

	pathes.push_back(START_PATH);

	QObject::connect(next, &QPushButton::clicked, this, &MainWindow::nextSlot);
	QObject::connect(prev, &QPushButton::clicked, this, &MainWindow::prevSlot);
	QObject::connect(fileManager, &QListWidget::itemDoubleClicked, this, &MainWindow::nextSlot);
}

MainWindow::~MainWindow()
{
	delete centralWidget;
}

void MainWindow::print(const QString& path)
{
	QFileInfo fileInfo(path);

	if (fileInfo.isFile())
	{
		#ifndef DEBUG_OFF
			qDebug() << "Error: this item not a folder";
		#endif // DEBUG_OFF

		QMessageBox::critical(centralWidget, "Error", "This item not a folder");

		if (pathes.size() != 1)
		{
			pathes.pop_back();
		}

		this->path = pathes.at(pathes.size() - 1);

		return;
	}

	QDir directory(path);
	QFileInfoList files = directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

	fileManager->clear();

	for (const auto& file : files)
	{
		QString file_name = file.fileName();

		if (file.isDir())
		{
			QListWidgetItem* item = new QListWidgetItem(QIcon(FOLDER_ICON_PATH), file_name);
			fileManager->addItem(item);
		}
		else if (file.isFile())
		{
			QListWidgetItem* item = new QListWidgetItem(QIcon(FILE_ICON_PATH), file_name);
			fileManager->addItem(item);
		}
	}
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	fileManager->setGeometry(0, 0, width(), height() - 50);
	next->setGeometry(width() - 100, height() - 45, BUTTON_WIDTH, BUTTON_HEIGHT);
	prev->setGeometry(width() - 205, height() - 45, BUTTON_WIDTH, BUTTON_HEIGHT);

	QMainWindow::resizeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	delete this;

	QMainWindow::closeEvent(event);
}

void MainWindow::nextSlot()
{
	if (not fileManager->currentItem())
	{
		#ifndef DEBUG_OFF
			qDebug() << "Error: path not found";
		#endif // DEBUG_OFF

		return;
	}

	QString selectedItemText = fileManager->currentItem()->text();

	path = pathes.at(pathes.size() - 1) + (QString) "/" + selectedItemText;

	pathes.push_back(path);

	print(path);
}

void MainWindow::prevSlot()
{
	if (pathes.size() != 1)
	{
		pathes.pop_back();
	}

	path = pathes.at(pathes.size() - 1);

	print(path);
}