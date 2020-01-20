#ifndef DRAWINGFRAME_H
#define DRAWINGFRAME_H

#include <QtWidgets>

class DrawingFrame : public QWidget
{
	Q_OBJECT

	QImage **image = nullptr;
	QWidget *drawingPanel = new QWidget(this);
	QScrollArea *scrollArea = new QScrollArea(this);

public:
	explicit DrawingFrame(QImage *&image, QWidget *parent = nullptr) : QWidget(parent) {
		Q_ASSERT_X(image, "Image is nullptr", "Image is nullptr");
		this->image = &image;

		this->setMinimumSize(480, 320);
		this->scrollArea->setWidget(drawingPanel);
		this->scrollArea->setAlignment(Qt::AlignCenter);

		this->drawingPanel->setAutoFillBackground(true);

		QVBoxLayout *layout = new QVBoxLayout;
		layout->addWidget(this->scrollArea);
		layout->setMargin(0);
		this->setLayout(layout);

		this->drawingPanel->resize(480, 320);
	}

signals:

public slots:
};

#endif // DRAWINGFRAME_H
