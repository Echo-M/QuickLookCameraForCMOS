#ifndef QQUICKLOOKCAMERA_H
#define QQUICKLOOKCAMERA_H

#include <QMainWindow>
#include "ui_qquicklookcamera.h"
#include "myclass.h"
#include "../QData/InstructionProcess.h"
class QLabel;

//该类提供整个上位机的主窗口
class QquickLookCamera : public QMainWindow
{
	Q_OBJECT
public:
	QquickLookCamera(QWidget *parent = 0);
	~QquickLookCamera();

	//创建相机控制子窗口
	void createControlFrame();
	//创建状态栏
	void cerateStatus();

public slots :
	void OpenFile();
	void saveFlie();
	void AECRun();
	void Stop();
	void setExpoTime(long long _time);
	void setFrRate(int _rate);

private: 
	//Ui::QquickLookCameraClass ui; //不使用UI，使用纯代码的方式添加控件

	QString filename;
	MyClass *showWidget;
	QFrame *ctrlFrame;
	QDockWidget *ctrlFrameDock;

private:
	QLineEdit *expoTimeLineEdit;
	QLineEdit *frRateLineEdit;

	long long expoTime{ 8000 };
	int frRate{ 18 };
	long long frLength{ 10000 };
	bool uploadFlag{ false };//数据上传标志

	//工具栏
	/*QToolBar *fileTool;
	QToolBar *zoomTool;
	QToolBar *rotateTool;
	QToolBar *mirrorTool;
	QToolBar *doToolBar;*/

	//状态栏
	QLabel  *expoTimeLabel;
	QLabel  *frRateLabel;
	QLabel  *frLengthLabel;	
};

#endif // QQUICKLOOKCAMERA_H
