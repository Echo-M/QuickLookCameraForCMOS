#include "qquicklookcamera.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QMouseEvent>
#include <QComboBox>
#include <QPushButton>
#include <QDockWidget>
#include <qframe.h>
#include <qgroupbox.h>
#include <QFileDialog>
#include <QLabel>
#include <QBoxLayout>

QquickLookCamera::QquickLookCamera(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	setWindowTitle(tr("CMOS"));
	setWindowIcon(QIcon("realtime.png"));

	showWidget = new MyClass(this); 
	showWidget->setMinimumSize(500, 450);
	setCentralWidget(showWidget); 
	
	ctrlFrame = new QFrame;
	createControlFrame(); 
	ctrlFrameDock = new QDockWidget(tr("camea control"), this);
	ctrlFrameDock->setFixedWidth(180);
	ctrlFrameDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	ctrlFrameDock->setWidget(ctrlFrame);
	addDockWidget(Qt::LeftDockWidgetArea, ctrlFrameDock);

	cerateStatus();    //创建状态栏
}

QquickLookCamera::~QquickLookCamera()
{

}
void QquickLookCamera::createControlFrame()
{
	//曝光时间
	QLabel *expoTimeLabel = new QLabel(tr("exposure rate:"));
	expoTimeLineEdit = new QLineEdit;
	expoTimeLineEdit->setPlaceholderText(tr("0000"));
	connect(expoTimeLineEdit, &QLineEdit::textChanged, this, [this]()
	{
		bool ok;
		QString valueStr = expoTimeLineEdit->text();
		expoTime = valueStr.toInt(&ok);
	});
	QPushButton *expoTimeOKButton = new QPushButton(tr("OK"));
	connect(expoTimeOKButton, &QPushButton::clicked, this, [this]()
	{
		setExpoTime(expoTime);
	});
	//帧率
	QLabel *frRateLabel = new QLabel(tr("frame rate:"));                   //dg为小数，整数部分为5位，小数部分为7位
	frRateLineEdit = new QLineEdit;
	frRateLineEdit->setPlaceholderText(tr("0000"));
	connect(frRateLineEdit, &QLineEdit::textChanged, this, [this]()
	{
		bool ok;
		QString valueStr = frRateLineEdit->text();
		frRate = valueStr.toInt(&ok);
	});
	QPushButton *frRateOKButton = new QPushButton(tr("OK"));
	connect(frRateOKButton, &QPushButton::clicked, this, [this]()
	{
		setFrRate(frRate);
	});

	QGridLayout *cameraParaLayout = new QGridLayout;
	//cameraParaLayout->setContentsMargins(8, 8, 8, 8);      //设置布局内部四边的空隙
	//cameraParaLayout->setAlignment(Qt::AlignHCenter);
	////cameraParaLayout->setAlignment(Qt::AlignTop);
	//cameraParaLayout->setSpacing(15);                      //设置间距
	//cameraParaLayout->setMargin(4);

	cameraParaLayout->addWidget(expoTimeLabel, 0, 0);
	cameraParaLayout->addWidget(expoTimeLineEdit, 1, 0);
	cameraParaLayout->addWidget(expoTimeOKButton, 2, 0);
	cameraParaLayout->addWidget(frRateLabel, 3, 0);
	cameraParaLayout->addWidget(frRateLineEdit, 4, 0);
	cameraParaLayout->addWidget(frRateOKButton, 5, 0);

	QGroupBox *cameraPara = new QGroupBox(tr("camera parameter"));
	cameraPara->setContentsMargins(20, 20, 20, 20);
	cameraPara->setLayout(cameraParaLayout);

	QPushButton *startButton = new QPushButton(tr("StartUpload"));
	connect(startButton, &QPushButton::clicked, this, &QquickLookCamera::AECRun);
	QPushButton *stopButton = new QPushButton(tr("Stop"));
	connect(stopButton, &QPushButton::clicked, this, &QquickLookCamera::Stop);

	//Frame布局
	QGridLayout *frameLayout = new QGridLayout;
	frameLayout->setMargin(5);
	frameLayout->setSpacing(10);
	frameLayout->addWidget(startButton, 0, 0);
	frameLayout->addWidget(stopButton, 1, 0);
	frameLayout->addWidget(cameraPara, 2, 0);
	ctrlFrame->setLayout(frameLayout);
}

void QquickLookCamera::cerateStatus()
{
	frRateLabel = new QLabel;
	QString tempfr = tr(" | frame rate: ");
	tempfr += QString::number(frRate);
	tempfr += tr(" fps");
	frRateLabel->setText(tempfr);
	frRateLabel->setFixedWidth(150);
	statusBar()->addPermanentWidget(frRateLabel);

	frLengthLabel = new QLabel;
	QString tempfl = tr(" | frame length: ");
	tempfl += QString::number(frLength);
	frLengthLabel->setText(tempfl);
	frLengthLabel->setFixedWidth(150);
	statusBar()->addPermanentWidget(frLengthLabel);

	expoTimeLabel = new QLabel;
	QString tempet = tr(" | exposure time: ");
	tempet += QString::number(expoTime);
	expoTimeLabel->setText(tempet);
	expoTimeLabel->setFixedWidth(150);
	statusBar()->addPermanentWidget(expoTimeLabel);
}

void QquickLookCamera::OpenFile()
{
	//qDebug()<< "------------qqucickdianjichengggong---------------";
	filename = QFileDialog::getOpenFileName(this);
}
void QquickLookCamera::saveFlie()
{
	showWidget->setSaveFile();
}

void QquickLookCamera::AECRun()
{
	InstructionProcess instruct(Instruction::CMOSE);
	instruct.AECRun();
	uploadFlag = true;
	QMessageBox::information(this, tr("Tips"), tr("Data is alreay upload!"));
}

void QquickLookCamera::setExpoTime(long long _time)
{
	if (!uploadFlag)
	{
		QMessageBox::critical(this, tr("Error"), tr("Data has not been upload! Please click the dataupload button!"));
		return;
	}
	if (expoTime >= frLength*0.8)
		expoTime = frLength*0.8;
	else
		expoTime = _time;

	InstructionProcess instruct(Instruction::CMOSE);
	instruct.ManualRun(expoTime);

	QString tempet = tr(" | exposure time: ");
	tempet += QString::number(expoTime);
	expoTimeLabel->setText(tempet);
	expoTimeLabel->update();
	
	uploadFlag = true;
	QMessageBox::information(this, tr("Tips"), tr("Data is alreay upload!"));
}
void QquickLookCamera::setFrRate(int _rate)
{
	if (!uploadFlag)
	{
		QMessageBox::critical(this, tr("Error"), tr("Data has not been upload! Please click the dataupload button!"));
		return;
	}
	frRate = _rate;
	frLength = 180000 / frRate;

	InstructionProcess instruct(Instruction::CMOSE);
	instruct.SetFPS(frRate);

	QString tempfr = tr(" | frame rate: ");
	tempfr += QString::number(frRate);
	tempfr += tr(" fps");
	frRateLabel->setText(tempfr);
	frRateLabel->update();

	QString tempfl = tr(" | frame length: ");
	tempfl += QString::number(frLength);
	frLengthLabel->setText(tempfl);
	frLengthLabel->update();

	uploadFlag = true;
	QMessageBox::information(this, tr("Tips"), tr("Data is alreay upload!"));
}

void QquickLookCamera::Stop()
{
	InstructionProcess instruct(Instruction::CMOSE);
	instruct.Stop();
	instruct.Stop();
	instruct.Stop();
	instruct.Stop();
	instruct.Stop();
	instruct.Stop();
	instruct.Stop();
	instruct.Stop();
	instruct.Stop();
	instruct.Stop();

	uploadFlag = false;
	QMessageBox::information(this, tr("Tips"), tr("Data is alreay stop uploading!"));
}