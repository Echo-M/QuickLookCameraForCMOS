#ifndef IMAGEWINDOWITEM_H
#define IMAGEWINDOWITEM_H

/// \brief ImageWindowItem displays image data

#include "IWindowItem.h"
#include <QScrollArea>
#include <QLabel>
#include <QMouseEvent>
#include <QStatusBar>
class ImageWindowItem;
class ImageLabel : public QLabel//The QLabel widget provides a text or image display. 
{
    Q_OBJECT

    friend class ImageWindowItem;
protected:
    std::shared_ptr<QImage> m_paintImg{nullptr}; //current visiable area
    QPoint m_offset{0,0}; //display offset
protected:
	//鼠标移动时，发送当前坐标
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
	//构造函数
    ImageLabel(QWidget* parent) : QLabel(parent) 
	{
        setMouseTracking(true);//鼠标没有被按下，窗口也会接受到鼠标移动事件
    }
    virtual void paintEvent(QPaintEvent*) override;
    void setImage(std::shared_ptr<QImage>& img) {m_paintImg = img;}
    void setOffset(const QPoint& offset) {m_offset=offset;}

signals:
    void mouseMoved(const QPoint& absolutePositon);
	void mousePressed(QString str1);
};

class QImage;
class ImageWindowItem :  public QScrollArea, public IWindowItem
{
    Q_OBJECT
protected:
    ImageLabel* m_imgLabel{nullptr}; //display image
    std::shared_ptr<QImage> m_image{nullptr}; //image rgba data
    std::shared_ptr<unsigned char> m_partOfImgData{nullptr}; //buffer which keeps image data of current display area
    mutable QSize m_szImageData{0,0}; //hold current image size , coz when hscroll scroll to right, image size may be changed
    unsigned char m_alpha{0xff}; //rgb a: alpha	`
protected:
    virtual void scrollContentsBy(int dx, int dy) override; //from QScrollArea, notify current display pos changed
    virtual void resizeEvent(QResizeEvent *) override;
protected:
    virtual int displayModeDisplay() const override;

protected:
    void onMouseMoved(const QPoint& absPos); //slot of mouseMoved signal
	//void onMousePressed(const QPoint &Pos);
	void leftMouseButtonDown(QString str);
    QRect displayArea() const; //fetch the rectangle of current valid image area
    bool resetBuffer(); 
public:
	virtual int saveToFile() const override;
public:
    ImageWindowItem(QWidget* parent=nullptr);
    ~ImageWindowItem();

    virtual IWindowItem* clone() const override;

    virtual int refresh() override;

    virtual int setDataItemPtr(std::shared_ptr<IDataItem>&) override;

//    //get&set window rectangle : left, top ,width, height
//    virtual int windowRect(int& left, int& top, int& width, int& height ) const override;
//    virtual int setWindowRect(int left, int top, int width, int height ) override;

//    //get&set client  rectangle : left, top ,width, height
//    virtual int clientRect(int& left, int& top, int& width, int& height ) const override;
//    virtual int setClientRect(int left, int top, int width, int height ) override;

signals:
    void displayPositionChanged(int x, int y); //when scroll pos changed
    void cursorPositionChanged(int x, int y); //when mouse pos changed
	void displayPressMousePostion(QString str); //when mouse pressed
};

#endif // IMAGEWINDOWITEM_H
