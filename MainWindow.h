#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DrawingPanel.h"
#include "NewImageDialog.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	DrawingPanel *drawingPanel = new DrawingPanel(this);
	QScrollArea *drawingPanelScrollArea = new QScrollArea(this);

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
			//this->adjustSize();
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
			//this->adjustSize();
		});

		QAction *setImageMarginAct = new QAction(tr("Set View Margin(&M)"), this);
		viewMenu->addAction(setImageMarginAct);
		this->connect(setImageMarginAct, &QAction::triggered, [this](bool){
			int marginSize = this->drawingPanel->getMargin().width(); // 随便选择一个维度(反正都一样)
			bool ok = false;
			int result = QInputDialog::getInt(this, tr("Image Margin"), tr("Enter a new margin size"), marginSize, 0, 100, 1, &ok);
			if(!ok){
				return;
			}
			this->drawingPanel->setMargin(QSize(result, result));
			//this->adjustSize();
		});

		QAction *setImagePaddingAct = new QAction(tr("Set View Padding(&P)"), this);
		viewMenu->addAction(setImagePaddingAct);
		this->connect(setImagePaddingAct, &QAction::triggered, [this](bool){
			int paddingSize = this->drawingPanel->getPadding().width(); // 随便选择一个维度(反正都一样)
			bool ok = false;
			int result = QInputDialog::getInt(this, tr("Image Padding"), tr("Enter a new padding size"), paddingSize, 0, 100, 1, &ok);
			if(!ok){
				return;
			}
			this->drawingPanel->setPadding(QSize(result, result));
			//this->adjustSize();
		});

		this->menuBar()->addMenu(viewMenu);

	}
public:
	MainWindow(QWidget *parent = 0): QMainWindow(parent){
		this->createMenus();
		this->setCentralWidget(this->drawingPanelScrollArea);
		this->drawingPanelScrollArea->setAlignment(Qt::AlignCenter);
		this->drawingPanelScrollArea->setWidget(this->drawingPanel);
		//this->drawingPanelScrollArea->setMinimumSize(this->drawingPanel->minimumSize());
		this->drawingPanelScrollArea->resize(480, 320);
	}
	~MainWindow();
};

#endif // MAINWINDOW_H
