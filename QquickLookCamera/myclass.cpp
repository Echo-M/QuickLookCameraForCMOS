#include "myclass.h"
#include <iostream>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
MyClass::MyClass(QWidget *parent,Qt::WindowFlags f)
: QWidget(parent,f),
  gridLayout(new QGridLayout(this))
{
	//初始化数据缓冲区
	std::dynamic_pointer_cast<CCirQueue>(m_cmosData0)->Initial(1024 * 1300 * 64, 1300);
	std::dynamic_pointer_cast<CCirQueue>(m_cmosData1)->Initial(1024 * 1300 * 64, 1300);
	std::dynamic_pointer_cast<CCirQueue>(m_cmosData2)->Initial(1024 * 1300 * 64, 1300);
	std::dynamic_pointer_cast<CCirQueue>(m_cmosData3)->Initial(1024 * 1300 * 64, 1300);
	std::dynamic_pointer_cast<CCirQueue>(m_cmosImageData0)->Initial(1024 * 1280 * 64, 1024 * 1280 * 1);
	std::dynamic_pointer_cast<CCirQueue>(m_cmosImageData1)->Initial(1024 * 1280 * 64, 1024 * 1280 * 1);
	std::dynamic_pointer_cast<CCirQueue>(m_cmosImageData2)->Initial(1024 * 1280 * 64, 1024 * 1280 * 1);
	std::dynamic_pointer_cast<CCirQueue>(m_cmosImageData3)->Initial(1024 * 1280 * 64, 1024 * 1280 * 1);
	//注册缓冲区
	m_inputSrc0->registerOutputBuffer(0, m_cmosData0); 
	m_inputSrc1->registerOutputBuffer(0, m_cmosData1);	
	m_inputSrc2->registerOutputBuffer(0, m_cmosData2);
	m_inputSrc3->registerOutputBuffer(0, m_cmosData3);
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider0)->registerInputBuffer(0, m_cmosData0); 
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider1)->registerInputBuffer(0, m_cmosData1);
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider2)->registerInputBuffer(0, m_cmosData2);
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider3)->registerInputBuffer(0, m_cmosData3);
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider0)->registerOutputBuffer(0, m_cmosImageData0);
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider1)->registerOutputBuffer(0, m_cmosImageData1);
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider2)->registerOutputBuffer(0, m_cmosImageData2);
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider3)->registerOutputBuffer(0, m_cmosImageData3);
	std::dynamic_pointer_cast<RotatedImageDataItem>(m_rotatedDataProvider0)->registerInputBuffer(0, m_cmosImageData0);
	std::dynamic_pointer_cast<RotatedImageDataItem>(m_rotatedDataProvider1)->registerInputBuffer(0, m_cmosImageData1);
	std::dynamic_pointer_cast<RotatedImageDataItem>(m_rotatedDataProvider2)->registerInputBuffer(0, m_cmosImageData2);
	std::dynamic_pointer_cast<RotatedImageDataItem>(m_rotatedDataProvider3)->registerInputBuffer(0, m_cmosImageData3);

	//开始上传数据
	m_inputSrc0->start();
	m_inputSrc1->start();
	m_inputSrc2->start();
	m_inputSrc3->start();
	//开始图像解析
	m_dataProvider0->setup(20, 1280, 1024); 
	m_dataProvider1->setup(20, 1280, 1024);
	m_dataProvider2->setup(20, 1280, 1024);
	m_dataProvider3->setup(20, 1280, 1024);
	//开始图像旋转
	m_rotatedDataProvider0->setup(20, 1024, 1280);//
	m_rotatedDataProvider1->setup(20, 1024, 1280);
	m_rotatedDataProvider2->setup(20, 1024, 1280);
	m_rotatedDataProvider3->setup(20, 1024, 1280);

	//设置通道编号
	m_magnifier0->setCmosNumber(0);
	m_magnifier00->setCmosNumber(4);
	m_magnifier1->setCmosNumber(1);
	m_magnifier2->setCmosNumber(2);
	m_magnifier3->setCmosNumber(3);
    //窗口绑定数据指针，初始化m_dataProvider
	m_magnifier0->setDataItemPtr(m_rotatedDataProvider0);//
	m_magnifier00->setDataItemPtr(m_rotatedDataProvider0);
	m_magnifier1->setDataItemPtr(m_rotatedDataProvider1);
	m_magnifier2->setDataItemPtr(m_rotatedDataProvider2);
	m_magnifier3->setDataItemPtr(m_rotatedDataProvider3);
	//m_magnifier0->setDataItemPtr(m_dataProvider0);//
	//m_magnifier00->setDataItemPtr(m_dataProvider0);
	//m_magnifier1->setDataItemPtr(m_dataProvider1);
	//m_magnifier2->setDataItemPtr(m_dataProvider2);
	//m_magnifier3->setDataItemPtr(m_dataProvider3);
	//窗口绑定数据转换指针，初始化m_convertor
	m_magnifier0->setConvertor(std::shared_ptr<PixelConvertor>(new PixelBayerToRGB));   //显示彩色图像时，要改窗口构造函数
	m_magnifier00->setConvertor(std::shared_ptr<PixelConvertor>(new Pixel8To32));//放大灰度显示，对比
	m_magnifier1->setConvertor(std::shared_ptr<PixelConvertor>(new Pixel8To32));
	m_magnifier2->setConvertor(std::shared_ptr<PixelConvertor>(new Pixel8To32));
	m_magnifier3->setConvertor(std::shared_ptr<PixelConvertor>(new Pixel8To32));
	//设置保存文件，初始化m_file
	m_magnifier0->setSave(std::shared_ptr<SaveToFile>(new SaveToBmp24));//存为彩色图像，深度24
	m_magnifier00->setSave(std::shared_ptr<SaveToFile>(new SaveToBmpGray));//存为灰度图像，8位
	m_magnifier1->setSave(std::shared_ptr<SaveToFile>(new SaveToBmpGray));
	m_magnifier2->setSave(std::shared_ptr<SaveToFile>(new SaveToBmpGray));
	m_magnifier3->setSave(std::shared_ptr<SaveToFile>(new SaveToBmpGray));

	//设置窗口大小
	m_magnifier0->setMagnifierRange(1024, 1280);
	m_magnifier00->setMagnifierRange(1024, 1280);
	m_magnifier1->setMagnifierRange(1024, 1280);
	m_magnifier2->setMagnifierRange(1024, 1280);
	m_magnifier3->setMagnifierRange(1024, 1280);
	m_magnifier00->setWindowFlags(Qt::Window);
	m_magnifier00->show();//通道0，放大图
	m_magnifier00->resize(420, 320);
	//定时刷新界面
	m_refreshTimer = new QTimer(this);	
	connect(m_refreshTimer, &QTimer::timeout, this,[this](){m_magnifier0->refresh();});//捕获列表中捕获了它所在函数中的局部变量，才能在函数体中使用该变量。
	connect(m_refreshTimer, &QTimer::timeout, [this](){m_magnifier00->refresh(); });
	connect(m_refreshTimer, &QTimer::timeout, [this](){m_magnifier1->refresh(); });
	connect(m_refreshTimer, &QTimer::timeout, [this](){m_magnifier2->refresh(); });
	connect(m_refreshTimer, &QTimer::timeout, [this](){m_magnifier3->refresh(); });
	m_refreshTimer->start(30); 
	//单击，双击界面转换
	QObject::connect(m_magnifier0, SIGNAL(leftMouseClicked()), this, SLOT(showMagnifier0()));
	QObject::connect(m_magnifier0, SIGNAL(doubleClickEvent()), this, SLOT(showMagnifierBack()));
	QObject::connect(m_magnifier1, SIGNAL(leftMouseClicked()), this, SLOT(showMagnifier1()));
	QObject::connect(m_magnifier1, SIGNAL(doubleClickEvent()), this, SLOT(showMagnifierBack()));
	QObject::connect(m_magnifier2, SIGNAL(leftMouseClicked()), this, SLOT(showMagnifier2()));
	QObject::connect(m_magnifier2, SIGNAL(doubleClickEvent()), this, SLOT(showMagnifierBack()));
	QObject::connect(m_magnifier3, SIGNAL(leftMouseClicked()), this, SLOT(showMagnifier3()));
	QObject::connect(m_magnifier3, SIGNAL(doubleClickEvent()), this, SLOT(showMagnifierBack()));
	//默认界面
	gridLayout->addWidget(m_magnifier0, 0, 0);
	gridLayout->addWidget(m_magnifier1, 0, 1);
	gridLayout->addWidget(m_magnifier2, 1, 0);
	gridLayout->addWidget(m_magnifier3, 1, 1);
	setLayout(gridLayout);
}

MyClass::~MyClass()
{
}
//点击，保存bmp文件
void MyClass::setSaveFile()
{
   // qDebug() << "--------------保存bmp文件-----------"; 
	m_magnifier0->saveToFile();
	m_magnifier00->saveToFile();
	m_magnifier1->saveToFile();
	m_magnifier2->saveToFile();
	m_magnifier3->saveToFile();
}
////点击，图像旋转90°
//void MyClass::setRotate90()
//{
//	 qDebug() << "--------------图像旋转90-----------";
//	 std::cout << "---------图像旋转90----------";
//	 m_rotateDateProvider0->setup(20, 1024, 1280);  //将当前线程停止，开始新的线程
//	 m_rotateDateProvider1->setup(20, 1024, 1280);
//	 m_rotateDateProvider2->setup(20, 1024, 1280);
//	 m_rotateDateProvider3->setup(20, 1024, 1280);
//
//	m_magnifier0->setDataItemPtr(m_rotateDateProvider0);
////	m_magnifier00->setDataItemPtr(m_dataProvider0);
//	m_magnifier1->setDataItemPtr(m_rotateDateProvider1);
//	m_magnifier2->setDataItemPtr(m_rotateDateProvider2);
//	m_magnifier3->setDataItemPtr(m_rotateDateProvider3);
//}
//单击窗口一大三小
void MyClass::showMagnifier0()
{
	//qDebug()<< "-----------myclassdianjichenggong------------------";
	gridLayout->removeWidget(m_magnifier0);  // m_magnifier0->setVisible(true);
	gridLayout->removeWidget(m_magnifier1);
	gridLayout->removeWidget(m_magnifier2);
	gridLayout->removeWidget(m_magnifier3);
	
	gridLayout->addWidget(m_magnifier0, 0, 0, 3, 1);
	gridLayout->addWidget(m_magnifier1, 0, 1, 1, 1);
	gridLayout->addWidget(m_magnifier2, 1, 1, 1, 1);
	gridLayout->addWidget(m_magnifier3, 2, 1, 1, 1);
	setLayout(gridLayout);
}
void MyClass::showMagnifier1()
{
	//qDebug()<< "-----------myclassdianjichenggong------------------";
	gridLayout->removeWidget(m_magnifier0);
	gridLayout->removeWidget(m_magnifier1);
	gridLayout->removeWidget(m_magnifier2);
	gridLayout->removeWidget(m_magnifier3);

	gridLayout->addWidget(m_magnifier1, 0, 0, 3, 1);
	gridLayout->addWidget(m_magnifier0, 0, 1, 1, 1);
	gridLayout->addWidget(m_magnifier2, 1, 1, 1, 1);
	gridLayout->addWidget(m_magnifier3, 2, 1, 1, 1);
	setLayout(gridLayout);
}
void MyClass::showMagnifier2()
{
	//qDebug()<< "-----------myclassdianjichenggong------------------";
	gridLayout->removeWidget(m_magnifier0);
	gridLayout->removeWidget(m_magnifier1);
	gridLayout->removeWidget(m_magnifier2);
	gridLayout->removeWidget(m_magnifier3);

	gridLayout->addWidget(m_magnifier2, 0, 0, 3, 1);
	gridLayout->addWidget(m_magnifier0, 0, 1, 1, 1);
	gridLayout->addWidget(m_magnifier1, 1, 1, 1, 1);
	gridLayout->addWidget(m_magnifier3, 2, 1, 1, 1);
	setLayout(gridLayout);
}
void MyClass::showMagnifier3()
{
	//qDebug()<< "-----------myclassdianjichenggong------------------";
	gridLayout->removeWidget(m_magnifier0);
	gridLayout->removeWidget(m_magnifier1);
	gridLayout->removeWidget(m_magnifier2);
	gridLayout->removeWidget(m_magnifier3);

	gridLayout->addWidget(m_magnifier3, 0, 0, 3, 1);
	gridLayout->addWidget(m_magnifier0, 0, 1, 1, 1);
	gridLayout->addWidget(m_magnifier1, 1, 1, 1, 1);
	gridLayout->addWidget(m_magnifier2, 2, 1, 1, 1);
	setLayout(gridLayout);
}
//双击还原默认窗口
void MyClass::showMagnifierBack()
{
	//qDebug()<< "-----------myclassdianjichenggong------------------";
	gridLayout->removeWidget(m_magnifier0);
	gridLayout->removeWidget(m_magnifier1);
	gridLayout->removeWidget(m_magnifier2);
	gridLayout->removeWidget(m_magnifier3);

	gridLayout->addWidget(m_magnifier0, 0, 0);
	gridLayout->addWidget(m_magnifier1, 0, 1);
	gridLayout->addWidget(m_magnifier2, 1, 0);
	gridLayout->addWidget(m_magnifier3, 1, 1);
	setLayout(gridLayout);
}

//void MyClass::mousePressEvent(QMouseEvent *e)
//{
//  if (e->button()==Qt::LeftButton)
//  {
//	  emit clicked();
//  }
//}