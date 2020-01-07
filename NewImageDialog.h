#ifndef NEWIMAGEDIALOG_H
#define NEWIMAGEDIALOG_H

#include <QtWidgets>

class NewImageDialog : public QDialog
{
	Q_OBJECT

	QSpinBox *widthBox = new QSpinBox(this);
	QSpinBox *heightBox = new QSpinBox(this);
	QComboBox *modeBox = new QComboBox(this);

	QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

	void setupLayout(){
		QFormLayout *mainLay = new QFormLayout(this);
		mainLay->addRow("Image width", this->widthBox);
		mainLay->addRow("Image height", this->heightBox);
		mainLay->addRow("Image mode", this->modeBox);
		mainLay->addRow(this->btnBox);
		this->setLayout(mainLay);
		mainLay->setSizeConstraint(QLayout::SetFixedSize);
	}

	void setupOptions(){
		this->widthBox->setMinimum(1);
		this->widthBox->setMaximum(640);
		this->heightBox->setMinimum(1);
		this->heightBox->setMaximum(640);
		this->widthBox->setSingleStep(1);
		this->heightBox->setSingleStep(1);

		this->modeBox->addItem("2 Colors [1 bit] (On/Off Palette)", "2");
		this->modeBox->addItem("4 Colors [2 bits] (Palette)", "4");
		this->modeBox->addItem("16 Colors [4 bits] (Palette)", "16");
		this->modeBox->addItem("256 Colors [8 bits] (Palette)", "256");
		this->modeBox->addItem("32768 Colors [15 bits available] (ARGB1555 Leave alpha channel set to 1)", "32768");
		this->modeBox->addItem("65536 Colors [16 bits] (RGB565)", "65536");
		this->modeBox->addItem("262K Colors [18 bits] (RGB666)", "262144");
		this->modeBox->addItem("16.7M Colors [24 bits] (RGB888)", "16777216");
		this->modeBox->addItem("16.7M Colors with alpha channel placeholder [32bits] (ARGB8888 Leave alpha channel set to 255)", "4294967296");

		this->connect(this->modeBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){
			Q_UNUSED(this);
			qDebug() << "Index:" << index;
		});

		this->connect(this->btnBox, &QDialogButtonBox::accepted, this, &NewImageDialog::accept);
		this->connect(this->btnBox, &QDialogButtonBox::rejected, this, &NewImageDialog::reject);
	}

public:
	explicit NewImageDialog(QWidget *parent = nullptr) : QDialog(parent){
		this->setupOptions();
		this->setupLayout();
	}

signals:

public slots:
};

#endif // NEWIMAGEDIALOG_H
