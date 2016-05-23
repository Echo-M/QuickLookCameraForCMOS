#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtWidgets/QMainWindow>
#include "./QData/InputCMOS.h"
#include "./QData/ImageDataItem.h"
#include "QData\RotatedImageDataItem.h"
#include "./QView/IWindowItem.h"
#include "./QView/Utility/Pixel8To32.h"
#include "./QView/Utility/PixelBayerToRGB.h"

#include "./QView/ImageMagnifierItem.h"  //class ImageMagnifierItem;
#include "./SaveFile/SaveToBmp24.h"
#include "./SaveFile/SaveToBmpGray.h"
#include "../QData/CirQueue.h"
#include <QTimer>
#include <QDebug>

class QGridLayout;

class MyClass : public QWidget
{
	Q_OBJECT

public:
	MyClass(QWidget *parent = 0, Qt::WindowFlags f = 0);
	~MyClass();

	void setSaveFile();
	//void setRotate90();
protected:
	std::shared_ptr<IDataItem> m_dataProvider0{ new ImageDataItem };
	std::shared_ptr<IDataItem> m_dataProvider1{ new ImageDataItem };
	std::shared_ptr<IDataItem> m_dataProvider2{ new ImageDataItem };
	std::shared_ptr<IDataItem> m_dataProvider3{ new ImageDataItem };

	std::shared_ptr<IDataItem> m_rotatedDataProvider0{ new RotatedImageDataItem };
	std::shared_ptr<IDataItem> m_rotatedDataProvider1{ new RotatedImageDataItem };
	std::shared_ptr<IDataItem> m_rotatedDataProvider2{ new RotatedImageDataItem };
	std::shared_ptr<IDataItem> m_rotatedDataProvider3{ new RotatedImageDataItem };

	/*std::shared_ptr<IDataItem> m_rotateDateProvider0{ new rotateDateProvider };
	std::shared_ptr<IDataItem> m_rotateDateProvider1{ new rotateDateProvider };
	std::shared_ptr<IDataItem> m_rotateDateProvider2{ new rotateDateProvider };
	std::shared_ptr<IDataItem> m_rotateDateProvider3{ new rotateDateProvider };*/

	IDataProcessUnit* m_inputSrc0{ new InputCMOS(3956, inet_addr("192.168.1.2")) };
	IDataProcessUnit* m_inputSrc1{ new InputCMOS(3957, inet_addr("192.168.1.2")) };	
	IDataProcessUnit* m_inputSrc2{ new InputCMOS(3958, inet_addr("192.168.1.2")) };
	IDataProcessUnit* m_inputSrc3{ new InputCMOS(3959, inet_addr("192.168.1.2")) };
	std::shared_ptr<IBuffer> m_cmosData0{ new CCirQueue };//输入数据
	std::shared_ptr<IBuffer> m_cmosData1{ new CCirQueue };//输入数据
	std::shared_ptr<IBuffer> m_cmosData2{ new CCirQueue };//输入数据
	std::shared_ptr<IBuffer> m_cmosData3{ new CCirQueue };//输入数据

	std::shared_ptr<IBuffer> m_cmosImageData0{ new CCirQueue };//图像帧数据
	std::shared_ptr<IBuffer> m_cmosImageData1{ new CCirQueue };//图像帧数据
	std::shared_ptr<IBuffer> m_cmosImageData2{ new CCirQueue };//图像帧数据
	std::shared_ptr<IBuffer> m_cmosImageData3{ new CCirQueue };//图像帧数据

protected:

	QTimer* m_refreshTimer{ nullptr };
	ImageMagnifierItem* m_magnifier0{ new ImageMagnifierItem(this, 0, QImage::Format_RGB888) }; //彩色图像格式24位	
	ImageMagnifierItem* m_magnifier00{ new ImageMagnifierItem(this) }; //图像格式24位	
	ImageMagnifierItem* m_magnifier1{ new ImageMagnifierItem(this) }; //
	ImageMagnifierItem* m_magnifier2{ new ImageMagnifierItem(this) }; //
	ImageMagnifierItem* m_magnifier3{ new ImageMagnifierItem(this) }; //

private:
	//Ui::MyClassClass ui;
	QGridLayout *gridLayout;

//protected:
//	void mousePressEvent(QMouseEvent *e);
signals:
	void clicked();
private slots :
    void showMagnifier1();
    void showMagnifier2();
    void showMagnifier3();
    void showMagnifier0();
	void showMagnifierBack();
};

#endif // MYCLASS_H
