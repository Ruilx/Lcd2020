#ifndef NEWIMAGEDIALOG_H
#define NEWIMAGEDIALOG_H

#include <QtWidgets>

class NewImageDialog : public QDialog
{
	Q_OBJECT
public:
	enum ImageMode{
		ColorUnknown = -1,
		Colors2 = 0,
		Colors4,
		Colors16,
		Colors256,
		Colors32768,
		Colors65536,
		Colors262144,
		Colors16777216,
		Colors4294967296
	};

private:
	QSpinBox *widthBox = new QSpinBox(this);
	QSpinBox *heightBox = new QSpinBox(this);
	QComboBox *modeBox = new QComboBox(this);
	QLabel *tipLabel = new QLabel(this);

	bool ready = false;

	QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

	void setupLayout(){
		QFormLayout *mainLay = new QFormLayout(this);
		mainLay->addRow("Image width", this->widthBox);
		mainLay->addRow("Image height", this->heightBox);
		mainLay->addRow("Image mode", this->modeBox);
		mainLay->addRow(this->tipLabel);
		mainLay->addRow(this->btnBox);
		this->setLayout(mainLay);
		mainLay->setSizeConstraint(QLayout::SetFixedSize);
	}

	static const QString getModeDescription(int index){
		switch(index){
			case 0: /* 用两种颜色代表亮和灭, 一个字节表示8个点阵, 可以在输出设置中指定方向和行列 */
				return tr("Two colors are used to represent on and off, one byte represents 8 dot matrix. The direction and rank can be specified in the output settings.");
			case 1: /* 使用预置的调色板选中4种颜色, 一个字节表示4个点阵, 可以在输出设置中指定方向和行列 */
				return tr("Use the preset palette to select 4 colors, one byte represents 4 dot matrix, and you can specify the direction and rank in the output settings.");
			case 2: /* 使用预置的调色板选中16种颜色, 一个字节表示两个点阵, 可以在输出中指定方向和行列 */
				return tr("Use the preset palette to select 16 colors, one byte represents 2 dot matrix, and you can specify the direction and rank in the output settings.");
			case 3: /* 使用预置的调色板选中256种颜色, 一个字节表示一个点阵, 可以在输出中指定方向和行列 */
				return tr("Use the preset palette to select 256 colors, one byte represents 1 dot, and you can specify the direction and rank in the output settings.");
			case 4: /* 32768种RGB颜色, 使用ARGB1555格式, 最高位透明通道默认为1, 两个字节表示一个点阵, 可以在输出中指定方向和行列 */
				return tr("32768 RGB colors, using ARGB1555 format, the highest bit transparent channel defaults to 1, two bytes represent a dot matrix, the direction and rank can be specified in the output settings.");
			case 5: /* 65536种RGB颜色, 使用RGB565格式, 两个字节表示一个点阵, 可以在输出中指定方向和行列 */
				return tr("65536 RGB colors, using RGB565 format, two bytes represent a dot matrix, the direction and rank can be specified in the output settings.");
			case 6: /* 262144种颜色, 使用RGB666格式, 三个字节表示4/3个点阵, 可以在输出中指定方向和行列 */
				return tr("262144 colors, using RGB666 format, three bytes represent 4/3 dot matrix, the direction and rows can be specified in the output settings.");
			case 7: /* 16777216种颜色, 使用RGB888格式, 三个字节表示一个点阵, 可以在输出中指定方向和行列 */
				return tr("16777216 colors, using RGB888 format, three bytes represent a dot matrix, the direction and rows can be specified in the output settings.");
			case 8: /* 16777216种颜色, 使用ARGB8888格式, 四个字节表示一个点阵, 透明通道默认为255, 可以在输出中指定方向和行列 */
				return tr("16777216 colors, using ARGB8888 format, four bytes represent a dot matrix, transparent channel defaults to 255, you can specify the direction and rank in the output settings.");
			default:
				return tr("Unknown mode, cannot display the description.");
		}
	}

	void setupOptions(){
		this->widthBox->setMinimum(1);
		this->widthBox->setMaximum(640);
		this->heightBox->setMinimum(1);
		this->heightBox->setMaximum(640);
		this->widthBox->setSingleStep(1);
		this->heightBox->setSingleStep(1);

		this->modeBox->addItem("2 Colors [1 bit] (On/Off Palette)", Colors2);
		this->modeBox->addItem("4 Colors [2 bits] (Palette)", Colors4);
		this->modeBox->addItem("16 Colors [4 bits] (Palette)", Colors16);
		this->modeBox->addItem("256 Colors [8 bits] (Palette)", Colors256);
		this->modeBox->addItem("32768 Colors [15 bits] (ARGB1555)", Colors32768);
		this->modeBox->addItem("65536 Colors [16 bits] (RGB565)", Colors65536);
		this->modeBox->addItem("262K Colors [18 bits] (RGB666)", Colors262144);
		this->modeBox->addItem("16.7M Colors [24 bits] (RGB888)", Colors16777216);
		this->modeBox->addItem("16.7M Colors [32 bits] (ARGB8888)", Colors4294967296);

		this->tipLabel->setText(NewImageDialog::getModeDescription(this->modeBox->currentIndex()));
		this->tipLabel->setMaximumWidth(350);
		this->tipLabel->setWordWrap(true);

		this->connect(this->modeBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){
			qDebug() << "Index:" << index;
			this->tipLabel->setText(NewImageDialog::getModeDescription(index));
		});

		this->connect(this->btnBox, &QDialogButtonBox::accepted, [this](){
			this->ready = true;
			this->accept();
		});
		this->connect(this->btnBox, &QDialogButtonBox::rejected, this, &NewImageDialog::reject);
	}

public:

	explicit NewImageDialog(QWidget *parent = nullptr) : QDialog(parent){
		this->setupOptions();
		this->setupLayout();
	}

	const QSize getImageSize(){
		if(this->ready){
			return QSize(this->widthBox->value(), this->heightBox->value());
		}
		qWarning() << "Using exec() to show the dialog first.";
		return QSize();
	}

	ImageMode getImageMode() const{
		if(this->ready){
			return (ImageMode)this->modeBox->currentData().toInt();
		}
		qWarning() << "Using exec() to show the dialog first.";
		return ColorUnknown;
	}

signals:

public slots:
};

#endif // NEWIMAGEDIALOG_H
