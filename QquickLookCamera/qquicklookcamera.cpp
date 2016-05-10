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
	showWidget->setMinimumSize(400, 400);
	setCentralWidget(showWidget); 
	
	ctrlFrame = new QFrame;
	createControlFrame(); 
	ctrlFrameDock = new QDockWidget(tr("ctrlFrameDock"), this);
	ctrlFrameDock->setFixedWidth(180);
	ctrlFrameDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	ctrlFrameDock->setWidget(ctrlFrame);
	addDockWidget(Qt::LeftDockWidgetArea, ctrlFrameDock);

	instructionE = new Instruction(4567, inet_addr("192.168.1.1"), 3955, inet_addr("192.168.1.2"));
	instructionE->SetCmosId(Instruction::CMOSE);
	instruction1 = new Instruction(4567, inet_addr("192.168.1.1"), 3955, inet_addr("192.168.1.2"));
	instruction1->SetCmosId(Instruction::CMOS1);
	instruction2 = new Instruction(4567, inet_addr("192.168.1.1"), 3955, inet_addr("192.168.1.2"));
	instruction2->SetCmosId(Instruction::CMOS2);
	instruction3 = new Instruction(4567, inet_addr("192.168.1.1"), 3955, inet_addr("192.168.1.2"));
	instruction3->SetCmosId(Instruction::CMOS3);

	createActions();   //创建动作
	createMenus();     //创建菜单
	cerateStatus();    //创建状态栏
}

QquickLookCamera::~QquickLookCamera()
{

}
void QquickLookCamera::createControlFrame()
{
	//曝光时间
	QLabel *exposureRateLabel = new QLabel(tr("exposure rate:"));
	exposureRateLineEdit = new QLineEdit;
	exposureRateLineEdit->setPlaceholderText(tr("0000"));
	connect(exposureRateLineEdit, &QLineEdit::textChanged, this, [this]()
	{
		bool ok;
		QString valueStr = exposureRateLineEdit->text();
		exposureRate = valueStr.toInt(&ok);
	});
	QPushButton *exposureRateOKButton = new QPushButton(tr("OK"));
	connect(exposureRateOKButton, &QPushButton::clicked, this, [this]()
	{
		setExposureRate(exposureRate);
	});
	//帧率
	QLabel *frameRateLabel = new QLabel(tr("frame rate:"));                   //dg为小数，整数部分为5位，小数部分为7位
	frameRateLineEdit = new QLineEdit;
	frameRateLineEdit->setPlaceholderText(tr("0000"));
	connect(frameRateLineEdit, &QLineEdit::textChanged, this, [this]()
	{
		bool ok;
		QString valueStr = frameRateLineEdit->text();
		frameRate = valueStr.toInt(&ok);
	});
	QPushButton *frameRateOKButton = new QPushButton(tr("OK"));
	connect(frameRateOKButton, &QPushButton::clicked, this, [this]()
	{
		setFrameRate(frameRate);
	});

	QGridLayout *cameraParaLayout = new QGridLayout;
	cameraParaLayout->setContentsMargins(8, 8, 8, 8);      //设置布局内部四边的空隙
	cameraParaLayout->setAlignment(Qt::AlignHCenter);
	//cameraParaLayout->setAlignment(Qt::AlignTop);
	cameraParaLayout->setSpacing(15);                      //设置间距
	cameraParaLayout->setMargin(4);

	cameraParaLayout->addWidget(exposureRateLabel, 0, 0);
	cameraParaLayout->addWidget(exposureRateLineEdit, 1, 0);
	cameraParaLayout->addWidget(exposureRateOKButton, 2, 0);
	cameraParaLayout->addWidget(frameRateLabel, 3, 0);
	cameraParaLayout->addWidget(frameRateLineEdit, 4, 0);
	cameraParaLayout->addWidget(frameRateOKButton, 5, 0);
	QGroupBox *cameraPara = new QGroupBox(tr("camera parameter"));
	cameraPara->setContentsMargins(20, 20, 20, 20);
	cameraPara->setLayout(cameraParaLayout);

	//Frame布局
	QGridLayout *frameLayout = new QGridLayout;
	frameLayout->setMargin(5);
	frameLayout->setSpacing(10);
	frameLayout->addWidget(cameraPara, 1, 0, 4, 1);
	ctrlFrame->setLayout(frameLayout);
}

void QquickLookCamera::createActions()
{
	openFileAction = new QAction(QIcon("open.png"), tr("open"), this);
	openFileAction->setShortcut(tr("Ctrl+O"));
	openFileAction->setStatusTip(tr("open files"));
	connect(openFileAction, &QAction::triggered, this, &QquickLookCamera::OpenFile);
	
	saveAction = new QAction(tr("save"), this);
	saveAction->setShortcut(tr("Ctrl+S"));
	saveAction->setStatusTip(tr("save current 4 image"));
	connect(saveAction, &QAction::triggered, this, &QquickLookCamera::saveFlie); 
	
	exitAction = new QAction(tr("exit"), this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("quit programmer"));
	connect(exitAction, &QAction::triggered, this, &QquickLookCamera::close);

	initAction = new QAction(tr("initial"), this);
	initAction->setStatusTip(tr("initial camera..."));
	connect(initAction, &QAction::triggered, this, &QquickLookCamera::Initial);

	startAction = new QAction(tr("start"), this);
	startAction->setStatusTip(tr("start upload image data..."));
	connect(startAction, &QAction::triggered, this, &QquickLookCamera::Start);

	stopAction = new QAction(tr("stop"), this);
	stopAction->setStatusTip(tr("start upload image data..."));
	connect(stopAction, &QAction::triggered, this, &QquickLookCamera::Stop);

	setExposureRateAction = new QAction(tr("set exposure rate"), this);
	setExposureRateAction->setStatusTip(tr("set exposure rate"));
	connect(setExposureRateAction, &QAction::triggered, this, &QquickLookCamera::setExposureRate);

	setFrameRateAction = new QAction(tr("set frame rate"), this);
	setFrameRateAction->setStatusTip(tr("set frame rate"));
	connect(setFrameRateAction, &QAction::triggered, this, &QquickLookCamera::setFrameRate);

	aboutAction = new QAction(tr("about"), this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutMSg()));
}

void QquickLookCamera::createMenus()
{
	//文件菜单
	fileMenu = menuBar()->addMenu(tr("file"));
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(exitAction);

	dataControlMenu = menuBar()->addMenu(tr("data control"));
	dataControlMenu->addAction(initAction);
	dataControlMenu->addAction(startAction);
	dataControlMenu->addAction(stopAction);

	cameraControlMenu = menuBar()->addMenu(tr("camera control"));
	cameraControlMenu->addAction(setExposureRateAction);
	cameraControlMenu->addAction(setFrameRateAction);

	helpMenu = menuBar()->addMenu(tr("help"));
	helpMenu->addAction(aboutAction);
}

void QquickLookCamera::cerateStatus()
{
	statusLabel = new QLabel;
	statusLabel->setText(tr("frame rate:"));
	statusLabel->setFixedWidth(50);
	statusBar()->addPermanentWidget(statusLabel);

	frameRateLabel = new QLabel;
	QString temp = QString::number(exposureRate);//帧率
	frameRateLabel->setText(temp);
	frameRateLabel->setFixedWidth(100);
	statusBar()->addPermanentWidget(frameRateLabel);
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

void QquickLookCamera::Initial()
{
	instructionE->Initial();
	instruction1->Initial();
	instruction2->Initial();
	instruction3->Initial();
}
void QquickLookCamera::Start()
{
	instructionE->Start();
	instruction1->Start();
	instruction2->Start();
	instruction3->Start();
}
void QquickLookCamera::Stop()
{
	instructionE->Stop();
	instruction1->Stop();
	instruction2->Stop();
	instruction3->Stop();
}
void QquickLookCamera::setExposureRate(int _rate)
{
	instructionE->SetExposureRate(_rate);
	instruction1->SetExposureRate(_rate);
	instruction2->SetExposureRate(_rate);
	instruction3->SetExposureRate(_rate);
}
void QquickLookCamera::setFrameRate(int _rate)
{
	instructionE->SetFrameRate(_rate);
	instruction1->SetFrameRate(_rate);
	instruction2->SetFrameRate(_rate);
	instruction3->SetFrameRate(_rate);

	QString temp = QString::number(frameRate);//帧率
	frameRateLabel->setText(temp);
	frameRateLabel->update();
}