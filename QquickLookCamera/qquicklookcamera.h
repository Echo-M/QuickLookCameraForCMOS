#ifndef QQUICKLOOKCAMERA_H
#define QQUICKLOOKCAMERA_H

#include <QMainWindow>

#include "ui_qquicklookcamera.h"
#include "myclass.h"
#include "./instruct/Instruction.h"
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
	//创建动作
	void createActions();
	//创建菜单栏
	void createMenus();
	// void createToolBars();
	//创建状态栏
	void cerateStatus();

public slots :
	void OpenFile();
	void saveFlie();

	void Initial();
	void Start();
	void Stop();

	void setExposureRate(int _rate);
	void setFrameRate(int _rate);

private: 
	//Ui::QquickLookCameraClass ui; //不使用UI，使用纯代码的方式添加控件

	QString filename;
	MyClass *showWidget;
	Instruction *instructionE;
	Instruction *instruction1;
	Instruction *instruction2;
	Instruction *instruction3;
	QFrame *ctrlFrame;
	QDockWidget *ctrlFrameDock;

private:
	//菜单栏
	QMenu *fileMenu;//文件（打开、保存、退出）
	QMenu *dataControlMenu;//数据控制（初始化、上传、停止）
	QMenu *cameraControlMenu;//相机控制（曝光率、帧率）
	QMenu *motorControlMenu;//电机控制
	QMenu *helpMenu;

	//菜单栏对应动作
	QAction *openFileAction;
	QAction *saveAction;
	QAction *exitAction;

	QAction *initAction;
	QAction *startAction;
	QAction *stopAction;

	QAction *setExposureRateAction;
	QAction *setFrameRateAction;

	QAction *aboutAction;

	QLineEdit *exposureRateLineEdit;
	QLineEdit *frameRateLineEdit;

	int exposureRate{ 0 };
	int frameRate{ 0 };

	//工具栏
	/*QToolBar *fileTool;
	QToolBar *zoomTool;
	QToolBar *rotateTool;
	QToolBar *mirrorTool;
	QToolBar *doToolBar;*/

	//状态栏
	QLabel  *statusLabel;
	QLabel  *frameRateLabel;
	
};

#endif // QQUICKLOOKCAMERA_H
