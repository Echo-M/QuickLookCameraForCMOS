#include "ImageWindowItem.h"
#include <QLabel>
#include <QImage>
#include <QScrollBar>
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QStatusBar>
#include "./Utility/Pixel16To32.h"
#include "../QData/IDataItem.h"

void ImageLabel::paintEvent(QPaintEvent *)
{
    if (!m_paintImg)
        return;
    QPainter painter(this);
    painter.drawImage(m_offset.x(), m_offset.y(), *m_paintImg);//ÔÚµãm_offset»æÖÆÍ¼Ïñ
}

ImageWindowItem::ImageWindowItem(QWidget *parent)
    : QScrollArea(parent)
{
    m_imgLabel = new ImageLabel(this);
    //setMouseTracking(true);
    connect(m_imgLabel, &ImageLabel::mouseMoved, this, &ImageWindowItem::onMouseMoved);
	connect(m_imgLabel, &ImageLabel::mousePressed, this, &ImageWindowItem::leftMouseButtonDown);
    setWidget(m_imgLabel);
}

ImageWindowItem::~ImageWindowItem()
{

}

void ImageWindowItem::onMouseMoved(const QPoint &absPos)
{
   // qDebug()<<absPos;
    emit cursorPositionChanged(absPos.x(), absPos.y());
}
void ImageWindowItem::leftMouseButtonDown(QString str2)
{
	emit displayPressMousePostion(str2);
}


void ImageWindowItem::scrollContentsBy(int dx, int dy)
{
    int x= horizontalScrollBar()->value();
    int y = verticalScrollBar()->value();

    resetBuffer(); //adjust in case the current width changed, if not, do nothing

    if (m_imgLabel)
        m_imgLabel->setOffset({x, y});
    //set current image offset, notify, adjust hardware somewhere
    emit displayPositionChanged(x, y);

    refresh();

    QScrollArea::scrollContentsBy(dx, dy);
}

IWindowItem* ImageWindowItem::clone() const
{
    ImageWindowItem* newItem = new ImageWindowItem();
    //set properties
    newItem->setConvertor(m_convertor);  //share the pixel convertor
    return  newItem;
}

int ImageWindowItem::displayModeDisplay() const
{
    //query current display offset, copyArea, update
    if (!m_convertor || !m_imgLabel || !m_image || !m_dataProvider || !m_partOfImgData)
        return EXEC_SUCCESS;
    const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
    if (!features)
        return ERR_INTERNAL_ERROR;

    QRect rtArea = displayArea();
    if (!rtArea.isValid() || rtArea.width()<=0 || rtArea.height()<=0)
        return ERR_INVALID_PARAM;

    if (m_dataProvider->copyArea(rtArea.left(), rtArea.top(), rtArea.width(), rtArea.height(), m_partOfImgData.get()))
    {
        //convert original data to display data  
        m_convertor->convert(m_image->bits(), m_partOfImgData.get(), rtArea.width(), rtArea.height(), m_alpha);
    }
    m_imgLabel->update();
    return EXEC_SUCCESS;
}

int ImageWindowItem::refresh()
{
    //if not in edit mode
    displayModeDisplay();
    update();
    return EXEC_SUCCESS;
}

bool ImageWindowItem::resetBuffer()
{
    if (!m_dataProvider)
        return false;
    const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
    if (!features)
        return false;

    QRect rtArea = displayArea();
    if (!rtArea.isValid() || rtArea.width()<=0 || rtArea.height()<=0)
        return false;

    if (m_szImageData != rtArea.size())
    {
		m_partOfImgData.reset(new unsigned char[rtArea.width()*rtArea.height()]);
        m_image.reset(new QImage(rtArea.width(), rtArea.height(), QImage::Format_ARGB32));
        m_imgLabel->setImage(m_image);
    }
    m_szImageData = rtArea.size();

    return true;
}

QRect ImageWindowItem::displayArea() const
{
    QRect rtArea(0,0,0,0);
    if (!m_dataProvider)
        return rtArea;
    const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
    if (!features)
        return rtArea;
    rtArea.setLeft(horizontalScrollBar()->value());
    rtArea.setTop(verticalScrollBar()->value());
    QRect rtWnd = geometry(); //container rect
    rtArea.setWidth(qMin(features->payloadDataWidth-rtArea.left(), rtWnd.width()));
    rtArea.setHeight(qMin(features->linesPerFrame-rtArea.top(), rtWnd.height()));

    return rtArea;
}

int ImageWindowItem::setDataItemPtr(std::shared_ptr<IDataItem>& dataPtr)
{
    m_dataProvider = dataPtr; //
    if (!m_dataProvider)
        return EXEC_SUCCESS; //unset

    //reset image size and label size
    const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
    if (!features)
        return ERR_INTERNAL_ERROR;
    QSize szEntireImage(features->payloadDataWidth, features->linesPerFrame);

    m_imgLabel->resize(szEntireImage);

    if (!resetBuffer())
        return ERR_INVALID_PARAM;

    scrollContentsBy(0, 0); //keep scroll pos, notify
    return EXEC_SUCCESS;
}

void ImageWindowItem::resizeEvent(QResizeEvent * e)
{
    if (m_dataProvider)
    {
        const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
        if (features)
        {
            resetBuffer();
            refresh();
        }
    }
    QScrollArea::resizeEvent(e);
}

//int ImageWindowItem::windowRect(int &left, int &top, int &width, int &height) const
//{
//    return EXEC_SUCCESS;
//}

//int ImageWindowItem::setWindowRect(int left, int top, int width, int height)
//{
//    return EXEC_SUCCESS;
//}

//int ImageWindowItem::clientRect(int &left, int &top, int &width, int &height) const
//{
//    return EXEC_SUCCESS;
//}

//int ImageWindowItem::setClientRect(int left, int top, int width, int height)
//{
//    return EXEC_SUCCESS;
//}
