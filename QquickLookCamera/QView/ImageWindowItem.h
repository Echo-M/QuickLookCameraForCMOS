#ifndef ImageWindowItem_H
#define ImageWindowItem_H

/// \brief ImageWindowItem provides a window magnifying the area around the mouse

#include <memory>
#include <QWidget>
#include "IWindowItem.h"
#include <QMouseEvent>
#include "../QData/IDataItem.h"
#include "./Utility/PixelConvertor.h"
#include "../SaveFile/SaveToFile.h"
class ImageWindowItem : public QWidget, public IWindowItem
{
    Q_OBJECT

protected:
    QPoint m_cursorPostion{0,0}; //zoom in center
    QSize m_range{16,16}; //
    QImage* m_image{nullptr}; //
    std::shared_ptr<unsigned char> m_imgBuffer{nullptr};
protected:
    virtual void paintEvent(QPaintEvent *) override; 
	//鼠标移动时，发送当前坐标
	void onMouseMoved(const QPoint& absPos); //slot of mouseMoved signal
	virtual void mouseMoveEvent(QMouseEvent *ev) override
	{
		emit mouseMoved(ev->pos());
	}
	//鼠标按下时，发送字符串"(x,y)"，x和y分别是横纵坐标
	void mousePressEvent(QMouseEvent *ev)
	{
		QString str = "(" + QString::number(ev->x()) + "," + QString::number(ev->y()) + ")";
		emit mousePressed(str);
	}
	void leftMouseButtonDown(QString str2)
	{
		emit displayPressMousePostion(str2);
	}
private:
	int cmosNumber;
	QImage::Format strFormat;

protected:
    virtual int displayModeDisplay() const override;

public:
	virtual int saveToFile() const override;

public:
	ImageWindowItem(QWidget* parent = nullptr, Qt::WindowFlags f = 0, QImage::Format str = QImage::Format_ARGB32);//不带默认形参的只能放在带默认形参的前面
    ~ImageWindowItem();
	void setCmosNumber(int number);
    virtual IWindowItem* clone() const override;
    virtual int setDataItemPtr(std::shared_ptr<IDataItem>& ptr)  override;
    virtual int refresh() override;
    virtual QWidget* widget() /*const*/ override {return this;}


signals:
	void cursorPositionChanged(int x, int y, int w, int h); //when mouse pos changed
	void displayPressMousePostion(QString str); //when mouse pressed
signals:
	void mouseMoved(const QPoint& absolutePositon);
	void mousePressed(QString str1);
public:	
    void setMagnifierRange(int width, int height); //set range of zoom in area

};

#endif // ImageWindowItem_H
