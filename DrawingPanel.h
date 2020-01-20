#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <QtCore>
#include <QtWidgets>

class DrawingPanel : public QWidget
{
	Q_OBJECT

	QImage *image = new QImage;

	QSize pixelSize = QSize(20, 20);
	QSize margin = QSize(5, 5);
	inline int marginH() const {return margin.width();}
	inline int marginV() const {return margin.height();}
	QSize padding = QSize(0, 0);
	inline int paddingH() const {return padding.width();}
	inline int paddingV() const {return padding.height();}

	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE {
		qDebug() << __PRETTY_FUNCTION__ << "size:" << event->size();
	}

	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
		Q_UNUSED(event);

		QPainter painter(this);

		if(this->image == nullptr || this->image->isNull()){
			painter.setPen(Qt::black);
			painter.setFont(QApplication::font());
			QString msg = tr("Please click File -> New Image to create a new image.");
			QFontMetrics fm(painter.font());
			QSize msgSize = fm.boundingRect(msg).size();
			painter.drawText((this->size().width() - msgSize.width()) / 2, (this->size().height() - msgSize.height()) / 2, msg);
		}else{
			if(this->pixelSize.width() == 1 && this->pixelSize.height() == 1){
				// 中间应该以或者进行处理的, 但想到画矩形的时候要么有边框要么没有, 所以一个为1也感觉显示不出图片,
				// 而且设置的时候也是直接设定两个值的, 所以在这里使用And连接, 如果显示一个块, 就直接画Image
				painter.drawImage(this->margin.width(), this->margin.height(), *this->image);
			}else{
				painter.setPen(Qt::lightGray);
				//painter.drawText(this->size().width() / 2, this->size().height() / 2, "Hello, world");
				for(int line = 0; line < this->image->height(); line++){
					QRgb *lp = (QRgb*)(this->image->scanLine(line));
					for(int column = 0; column < this->image->width(); column++){
						painter.setBrush(QColor(*lp));
						painter.drawRect(QRect(imageToPanel(QPoint(column, line)), this->pixelSize));
						lp++;
					}
				}
			}
		}
		painter.end();
	}

	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE {
		QPoint pos = event->pos();
		if(this->image->isNull()){
			return;
		}
		qDebug() << "Current Pos:" << pos;
		bool ok = false;
		QPoint loc = this->panelToImage(pos, &ok);
		if(ok){
			qDebug() << "Looking Loc:" << loc;
			if(this->image->width() < loc.x() || this->image->height() < loc.y()){
				return;
			}
			if(event->button() == Qt::RightButton){
				this->image->setPixelColor(loc, Qt::black);
				this->update();
				event->accept();
				return;
			}else if(event->button() == Qt::LeftButton){
				this->image->setPixelColor(loc, Qt::white);
				this->update();
				event->accept();
				return;
			}
		}
	}

	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE {
		const QPoint pos = event->pos();
		const Qt::MouseButtons buttons = event->buttons();
		if(this->image->isNull()){
			qDebug() << "Current Image is null";
		}
		bool ok = false;
		QPoint loc = this->panelToImage(pos, &ok);
		if(ok){
			if(this->image->width() < loc.x() || this->image->height() < loc.y()){
				return;
			}
			if(buttons & Qt::RightButton){
				this->image->setPixelColor(loc, Qt::black);
				this->update();
				event->accept();
				return;
			}else if(buttons & Qt::LeftButton){
				this->image->setPixelColor(loc, Qt::white);
				this->update();
				event->accept();
				return;
			}
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
			//qreal modX = (pointOnPanel.x() - this->marginH()) % (this->paddingH() + this->pixelSize.width());
			//qreal modY = (pointOnPanel.y() - this->marginV()) % (this->paddingV() + this->pixelSize.height());
			if(refX < 0 || refY < 0){
				return QPoint();
			}
//			if(modX <= this->paddingH() || modY <= this->paddingV()){
//				return QPoint();
//			}
			if(ok){ *ok = true; }
			return QPoint(qFloor(refX), qFloor(refY));
		}
		return QPoint();
	}

	inline const QSize calPanelSize(const QSize &imageSize) const{
		return QSize(imageSize.width() * (this->paddingH() + this->pixelSize.width()) + 2 * this->marginH(),
					 imageSize.height() * (this->paddingV() + this->pixelSize.height()) + 2 * this->marginV());
	}

	void doPanelResize(const QSize &imageSize){
		//this->setFixedSize(this->calPanelSize(imageSize));
		this->resize(this->calPanelSize(imageSize + QSize(1, 1))); // Margin will add a extra rect border 1 to fix right and left margin same
	}
public:
	explicit DrawingPanel(QWidget *parent = nullptr): QWidget(parent){
		//Q_ASSERT_X(image, "Image is nullptr", "Image is nullptr");
		//this->image = image;
		this->setMinimumSize(480, 320);
		this->resize(480, 320);
//		QPalette palette = this->palette();{
//			palette.setColor(QPalette::Base, QColor(128, 128, 128));
//			palette.setColor(QPalette::Background, QColor(128, 128, 128));
//		}
//		this->setPalette(palette);
		this->setAutoFillBackground(true);

//		this->setSize(QSize(40, 8));

	}

	void createNew(const QSize &size){
		if(this->image && !this->image->isNull()){
			int result = QMessageBox::question(this, tr("Create New Image"), tr("There has a modified image already, it will remove when new image created. Continue?"), QMessageBox::Yes|QMessageBox::No);
			if(result == QMessageBox::No){
				return;
			}
		}
		this->setSize(size);
	}

	void setSize(const QSize &size){
		if(this->image && size == this->image->size()){
			return;
		}
		QImage::Format imageFormat = this->image->format() == QImage::Format_Invalid ? QImage::Format_ARGB32_Premultiplied : this->image->format();
		QImage *newImage = new QImage(size, imageFormat);
		newImage->fill(Qt::black);
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

	inline const QSize getSize() const Q_DECL_NOTHROW {
		return this->image->size();
	}

	inline void setPixelSize(const QSize &size) Q_DECL_NOTHROW {
		if(size.width() > 0 && size.height() > 0){
			this->pixelSize = size;
			this->doPanelResize(this->image->size());
			this->update();
		}
	}

	inline const QSize getPixelSize() const Q_DECL_NOTHROW {
		return this->pixelSize;
	}

	inline void setMargin(const QSize &margin) Q_DECL_NOTHROW {
		if(margin.width() >= 0 && margin.height() >= 0){
			this->margin = margin;
			this->doPanelResize(this->image->size());
			this->update();
		}
	}

	inline const QSize getMargin() const Q_DECL_NOTHROW {
		return this->margin;
	}

	inline void setPadding(const QSize &padding) Q_DECL_NOTHROW {
		if(padding.width() >= 0 && padding.height() >= 0){
			this->padding = padding;
			this->doPanelResize(this->image->size());
			this->update();
		}
	}

	inline const QSize getPadding() const Q_DECL_NOTHROW {
		return this->padding;
	}

	void clear(){
		this->image->fill(Qt::black);
		this->update();
	}



signals:

public slots:
};

#endif // DRAWINGPANEL_H
