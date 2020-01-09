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
		QMenu *fileMenu = new QMenu(tr("File(&F)"), this);
		QAction *newImageAct = new QAction(tr("New Image(&N)"), this);
		fileMenu->addAction(newImageAct);
		this->connect(newImageAct, &QAction::triggered, [this](bool){
			NewImageDialog dialog(this);
			int ret = dialog.exec();
			if(!ret){
				return;
			}
			QSize imageSize = dialog.getImageSize();
			NewImageDialog::ImageMode imageMode = dialog.getImageMode();
			qDebug() << "Create an image size:" << imageSize << "mode:" << imageMode;
			this->drawingPanel->createNew(imageSize);
			this->adjustSize();
		});
		this->menuBar()->addMenu(fileMenu);

		QMenu *editMenu = new QMenu(tr("Edit(&E)"), this);
		QAction *clearImageAct = new QAction(tr("Clear Image(&C)"), this);
		editMenu->addAction(clearImageAct);
		this->connect(clearImageAct, &QAction::triggered, [this](bool){
			this->drawingPanel->clear();
		});
		this->menuBar()->addMenu(editMenu);

		QMenu *viewMenu = new QMenu(tr("View(&V)"), this);
		QAction *setPixelSizeAct = new QAction(tr("Set Pixel Size(&P)"), this);
		viewMenu->addAction(setPixelSizeAct);
		this->connect(setPixelSizeAct, &QAction::triggered, [this](bool){
			int pixelSize = this->drawingPanel->getPixelSize().width(); // 随便选择一个维度(反正都是正方形)
			bool ok = false;
			int result = QInputDialog::getInt(this, tr("Pixel size"), tr("Enter a new pixel size"), pixelSize, 1, 40, 1, &ok);
			if(!ok){
				return;
			}
			this->drawingPanel->setPixelSize(QSize(result, result));
		});
		this->menuBar()->addMenu(viewMenu);

	}
public:
	MainWindow(QWidget *parent = 0): QMainWindow(parent){
		this->createMenus();
		this->setCentralWidget(this->drawingPanel);
	}
	~MainWindow();
};

#endif // MAINWINDOW_H
