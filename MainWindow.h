#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DrawingPanel.h"
#include "NewImageDialog.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	DrawingPanel *drawingPanel = new DrawingPanel(this);

	void createMenus(){
		QMenu *fileMenu = new QMenu("File(&F)", this);
		QAction *newImageAct = new QAction("New Image(&N)", this);
		fileMenu->addAction(newImageAct);
		this->connect(newImageAct, &QAction::triggered, [this](bool){
			NewImageDialog dialog(this);
			int ret = dialog.exec();
			qDebug() << ret;
		});
		this->menuBar()->addMenu(fileMenu);

		QMenu *editMenu = new QMenu("Edit(&E)", this);
		QAction *clearImageAct = new QAction("Clear Image(&C)", this);
		editMenu->addAction(clearImageAct);
		this->connect(clearImageAct, &QAction::triggered, [this](bool){
			this->drawingPanel->clear();
		});
		this->menuBar()->addMenu(editMenu);

	}
public:
	MainWindow(QWidget *parent = 0): QMainWindow(parent){
		this->createMenus();
		this->setCentralWidget(this->drawingPanel);
	}
	~MainWindow();
};

#endif // MAINWINDOW_H
