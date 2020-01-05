#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DrawingPanel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	DrawingPanel *drawingPanel = new DrawingPanel(this);

public:
	MainWindow(QWidget *parent = 0): QMainWindow(parent){
		this->setCentralWidget(this->drawingPanel);
	}
	~MainWindow();
};

#endif // MAINWINDOW_H
