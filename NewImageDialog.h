#ifndef NEWIMAGEDIALOG_H
#define NEWIMAGEDIALOG_H

#include <QtWidgets>

class NewImageDialog : public QDialog
{
	Q_OBJECT

	QSpinBox *widthBox = new QSpinBox(this);
	QSpinBox *heightBox = new QSpinBox(this);
	QComboBox *modeBox = new QComboBox(this);

	void setupLayout(){
		QFormLayout *mainLay = new QFormLayout(this);
		mainLay->addRow("Image width", this->widthBox);
		mainLay->addRow("Image height", this->heightBox);
		mainLay->addRow("Image mode", this->modeBox);
		this->setLayout(mainLay);
	}

	void setupDefault(){
		this->widthBox->setMinimum(1);
		this->widthBox->setMaximum(640);
		this->heightBox->setMinimum(1);
		this->heightBox->setMaximum(640);
		this->widthBox->setSingleStep(1);
		this->heightBox->setSingleStep(1);

		this->modeBox->addItem("2 Colors [1 bit] (On/Off Palette)");
		this->modeBox->addItem("4 Colors [2 bits] (Palette)");
		this->modeBox->addItem("16 Colors [4 bits] (Palette)");
		this->modeBox->addItem("256 Colors [8 bits] (Palette)");
		this->modeBox->addItem("32768 Colors [15 bits available] (ARGB1555 Leave alpha channel set to 1)");
		this->modeBox->addItem("65536 Colors [16 bits] (RGB565)");
		this->modeBox->addItem("262K Colors [18 bits] (RGB666)");
		this->modeBox->addItem("16.7M Colors [24 bits] (RGB888)");
		this->modeBox->addItem("16.7M Colors with alpha channel placeholder [32bits] (ARGB8888 Leave alpha channel set to 255)");
	}
public:
	explicit NewImageDialog(QWidget *parent = nullptr) : QDialog(parent){



		this->setupLayout();
	}

signals:

public slots:
};

#endif // NEWIMAGEDIALOG_H
