#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <QtCore>
#include <QtWidgets>

class DrawingPanel : public QWidget
{
	Q_OBJECT

	QImage *image = new QImage();

	QSize pixelSize = QSize(20, 20);
	QSize margin = QSize(5, 5);
	inline int marginH() const {return margin.width();}
	inline int marginV() const {return margin.height();}
	QSize padding = QSize(2, 2);
	inline int paddingH() const {return padding.width();}
	inline int paddingV() const {return padding.height();}

	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
		Q_UNUSED(event);
//		if(this->pixmap == nullptr || this->pixmap->isNull()){
//			return;
//		}
		QPainter painter(this);
		painter.setPen(Qt::white);
		//painter.drawText(this->size().width() / 2, this->size().height() / 2, "Hello, world");
		for(int line = 0; line < this->image->height(); line++){
			QRgb *lp = (QRgb*)(this->image->scanLine(line));
			for(int column = 0; column < this->image->width(); column++){
				if(*lp == 0xFFFFFFFF){
					painter.setBrush(Qt::yellow);
					painter.drawRect(QRect(imageToPanel(QPoint(column, line)), this->pixelSize));
				}else{
					painter.setBrush(Qt::black);
					painter.drawRect(QRect(imageToPanel(QPoint(column, line)), this->pixelSize));
				}
				lp++;
			}
		}
		painter.end();
	}

	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE {
		QPoint pos = event->pos();
		if(this->image->isNull()){
			qDebug() << "Current Image is null";
			return;
		}
		qDebug() << "Current Pos:" << pos;
		bool ok = false;
		QPoint loc = this->panelToImage(pos, &ok);
		if(ok){
			qDebug() << "Looking Loc:" << loc;
			if(this->image->width() < loc.x() || this->image->height() < loc.y()){
				qDebug() << "The panel is bigger than Image and detected out of bounds.";
				return;
			}
			if(event->button() == Qt::RightButton){
				this->image->setPixelColor(loc, Qt::black);
			}else if(event->button() == Qt::LeftButton){
				this->image->setPixelColor(loc, Qt::white);
			}
			this->update();
		}else{
			qDebug() << "Invalid Loc.";
		}
	}

	void setPixel(const QPoint &point, const QColor &color){
		if(point.x() > this->image->width() || point.y() > this->image->height()){
			return;
		}
		this->image->setPixelColor(point, color);
	}

	const QPoint imageToPanel(const QPoint &pointOnImage) const{
		if(pointOnImage.x() >= 0 && pointOnImage.y() >= 0){
			return QPoint(this->marginH() + pointOnImage.x() * (this->paddingH() + this->pixelSize.width()),
						  this->marginV() + pointOnImage.y() * (this->paddingV() + this->pixelSize.height()));
		}
		return QPoint();
	}

	const QPoint panelToImage(const QPoint &pointOnPanel, bool *ok = nullptr) const{
		if(ok){ *ok = false; }
		if(pointOnPanel.x() >= 0 && pointOnPanel.y() >= 0){
			qreal refX = (pointOnPanel.x() - this->marginH()) / (this->paddingH() + this->pixelSize.width());
			qreal refY = (pointOnPanel.y() - this->marginV()) / (this->paddingV() + this->pixelSize.height());
			qreal modX = (pointOnPanel.x() - this->marginH()) % (this->paddingH() + this->pixelSize.width());
			qreal modY = (pointOnPanel.y() - this->marginV()) % (this->paddingV() + this->pixelSize.height());
			if(refX < 0 || refY < 0){
				return QPoint();
			}
			if(modX <= this->paddingH() || modY <= this->paddingV()){
				return QPoint();
			}
			if(ok){ *ok = true; }
			return QPoint(floor(refX), floor(refY));
		}
		return QPoint();
	}

	inline const QSize calPanelSize(const QSize &imageSize) const{
		return QSize(imageSize.width() * (this->paddingH() + this->pixelSize.width()) + 2 * this->marginH(),
					 imageSize.height() * (this->paddingV() + this->pixelSize.height()) + 2 * this->marginV());
	}

	void doPanelResize(const QSize &imageSize){
		this->setFixedSize(this->calPanelSize(imageSize));
	}
public:
	explicit DrawingPanel(QWidget *parent = nullptr): QWidget(parent){
		//this->setMinimumSize(480, 320);
		QPalette palette = this->palette();{
			palette.setColor(QPalette::Base, QColor(128, 128, 128));
			palette.setColor(QPalette::Background, QColor(128, 128, 128));
		}
		this->setPalette(palette);
		this->setAutoFillBackground(true);

		this->setSize(QSize(16, 16));

	}

	void setSize(const QSize &size){
		if(size == this->image->size()){
			return;
		}
		QImage::Format imageFormat = this->image->format() == QImage::Format_Invalid ? QImage::Format_ARGB32_Premultiplied : this->image->format();
		QImage *newImage = new QImage(size, imageFormat);
		QPainter newImagePainter(newImage);
		newImagePainter.drawImage(0, 0, *this->image);
		newImagePainter.end();

		QImage *willBeDeleted = this->image;
		this->image = newImage;
		if(willBeDeleted != nullptr){
			delete willBeDeleted;
			willBeDeleted = nullptr;
		}

		this->doPanelResize(size);
	}

	inline void setPixelSize(const QSize &size) Q_DECL_NOTHROW {
		if(size.width() > 0 && size.height() > 0){
			this->pixelSize = size;

		}
	}

	inline void setMargin(const QSize &margin) Q_DECL_NOTHROW {
		if(margin.width() >= 0 && margin.height() >= 0){
			this->margin = margin;
		}
	}

	inline void setPadding(const QSize &padding) Q_DECL_NOTHROW {
		if(padding.width() >= 0 && padding.height() >= 0){
			this->padding = padding;
		}
	}

signals:

public slots:
};

#endif // DRAWINGPANEL_H
