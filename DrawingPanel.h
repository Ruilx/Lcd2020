#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <QtCore>
#include <QtWidgets>

class DrawingPanel : public QWidget
{
	Q_OBJECT

	QPixmap *pixmap = new QPixmap();
	QSize pixelSize = QSize(10, 10);

	void paintEvent(QPaintEvent *event){
//		if(this->pixmap == nullptr || this->pixmap->isNull()){
//			return;
//		}
		QPainter painter(this);
		painter.setBrush(Qt::white);
		painter.drawText(QPointF(100, 100), "Hello, world");
		painter.end();
	}

	void setPixel(QPoint point, QColor color){
		QPainter painter(this->pixmap);
		painter.setPen(color);
		painter.drawPoint(point);
		painter.end();
	}
public:
	explicit DrawingPanel(QWidget *parent = nullptr): QWidget(parent){
		this->setMinimumSize(480, 320);
		QPalette palette = this->palette();{
			palette.setColor(QPalette::Base, QColor(128, 128, 128));
			palette.setColor(QPalette::Background, QColor(128, 128, 128));
		}
		this->setPalette(palette);
		this->setAutoFillBackground(true);
	}

	void setSize(const QSize &size){
		if(size == this->pixmap->size()){
			return;
		}
		QPixmap *newPixmap = new QPixmap(size);
		QPainter newPixmapPainter(newPixmap);
		newPixmapPainter.drawPixmap(0, 0, *this->pixmap);
		newPixmapPainter.end();
		QPixmap *willBeDelete = this->pixmap;
		this->pixmap = newPixmap;
		if(willBeDelete != nullptr){
			delete willBeDelete;
			willBeDelete = nullptr;
		}
	}

	void setPixelSize(const QSize &size){
		if(size != QSize(0, 0)){
			this->pixelSize = size;
		}
	}

signals:

public slots:
};

#endif // DRAWINGPANEL_H
