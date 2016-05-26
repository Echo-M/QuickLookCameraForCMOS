#include "ImageWindowItem.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QInputDialog>
#include <QLineEdit>

ImageWindowItem::ImageWindowItem(QWidget *parent, Qt::WindowFlags f, QImage::Format str)
    : QWidget(parent, f),
	strFormat(str)
{
	startAction = new QAction("start upload", this);
	stopAction = new QAction("stop upload", this);
	ag_cgAction = new QAction("set ag_cg", this);
	dgAction = new QAction("set dg", this);
	expoAction = new QAction("set exposure time", this);
	fpsAction = new QAction("set frame rate", this);
	menu->addAction(startAction);
	menu->addAction(stopAction);
	menu->addAction(fpsAction);
	menu->addAction(expoAction);
	menu->addAction(ag_cgAction);
	menu->addAction(dgAction);
	connect(startAction, &QAction::triggered, this, &ImageWindowItem::onStartActionTriggerd);
	connect(stopAction, &QAction::triggered, this, &ImageWindowItem::onStopActionTriggerd);
	connect(ag_cgAction, &QAction::triggered, this, &ImageWindowItem::onAg_cgActionTriggerd);
	connect(dgAction, &QAction::triggered, this, &ImageWindowItem::onDgActionTriggerd);
	connect(fpsAction, &QAction::triggered, this, &ImageWindowItem::onFpsActionTriggerd);
	connect(expoAction, &QAction::triggered, this, &ImageWindowItem::onExpoActionTriggerd);
	//m_image = new QImage(m_range, QImage::Format_ARGB32);  //default range 5*5, scale to the rectangle of window
	m_image = new QImage(m_range, strFormat);
	setMouseTracking(true);//鼠标没有被按下，窗口也会接受到鼠标移动事件
	connect(this, &ImageWindowItem::mouseMoved, this, &ImageWindowItem::onMouseMoved);
    //unsigned char* bits = m_image->bits(); for (int i=0; i<25*25; ++i)   *((unsigned int*)(bits+i*4)) = (((10*i)<<8) | (0xff<<24));    
}

ImageWindowItem::~ImageWindowItem()
{

}

void ImageWindowItem::onAg_cgActionTriggerd()
{
	if (!uploadFlag)
	{
		QMessageBox::critical(this, tr("Error"), tr("Data has not been upload! Please click the dataupload button!"));
		return;
	}

	InstructionProcess instruct(cmosNumber);

	QStringList list;
	list << tr("1.00") << tr("1.14") << tr("1.33") << tr("1.60") << tr("2.00") << tr("2.29") << tr("2.67") << tr("3.20") << tr("4.00") << tr("5.33") << tr("8.00");
	bool ok;
	int listNum;
	if (m_ag_cg == 1.00) listNum = 0;
	else if (m_ag_cg == 1.14) listNum = 1;
	else if (m_ag_cg == 1.33) listNum = 2;
	else if (m_ag_cg == 1.60) listNum = 3;
	else if (m_ag_cg == 2.00) listNum = 4;
	else if (m_ag_cg == 2.29) listNum = 5;
	else if (m_ag_cg == 2.67) listNum = 6;
	else if (m_ag_cg == 3.20) listNum = 7;
	else if (m_ag_cg == 4.00) listNum = 8;
	else if (m_ag_cg == 5.33) listNum = 9;
	else if (m_ag_cg == 8.00) listNum = 10;
	QString valueStr = QInputDialog::getItem(this, tr("AG&CG setting"), tr("input total gain"), list, listNum, false, &ok);
	if (ok&&!valueStr.isEmpty())
	{
		m_ag_cg = valueStr.toFloat(&ok);
		if(!instruct.SetAGCG(m_ag_cg))
		{
			QMessageBox::critical(this, tr("Error"), tr("Failed to set AG_CG!"));
			return;
		}
		uploadFlag = true;
	}
}
void ImageWindowItem::onDgActionTriggerd()
{
	if (!uploadFlag)
	{
		QMessageBox::critical(this, tr("Error"), tr("Data has not been upload! Please click the dataupload button!"));
		return;
	}
	InstructionProcess instruct(cmosNumber);

	bool ok;
	double value = QInputDialog::getDouble(this, tr("digital gain setting"), tr("input digital gain:"), m_dg, 0, 10, 1, &ok);//范围0-10,默认3.0
	if (ok)
	{
		m_dg = value;
		if(!instruct.SetDG(m_dg))
		{
			QMessageBox::critical(this, tr("Error"), tr("Failed to set DG!"));
			return;
		}
		uploadFlag = true;
	}
}
void ImageWindowItem::onExpoActionTriggerd()
{
	if (!uploadFlag)
	{
		QMessageBox::critical(this, tr("Error"), tr("Data has not been upload! Please click the dataupload button!"));
		return;
	}
	InstructionProcess instruct(cmosNumber);

	bool ok;
	int value = QInputDialog::getInt(this, tr("exposure time setting"), tr("input exposure time:"), m_expoTime, 0, 180000 / m_frRate, 1, &ok);
	if (ok)
	{
		m_expoTime = value;
		if(!instruct.setExpoTime(m_expoTime))
		{
			QMessageBox::critical(this, tr("Error"), tr("Failed to set exposure time!"));
			return;
		}
		uploadFlag = true;
	}
}
void ImageWindowItem::onFpsActionTriggerd()
{
	if (!uploadFlag)
	{
		QMessageBox::critical(this, tr("Error"), tr("Data has not been upload! Please click the dataupload button!"));
		return;
	}
	InstructionProcess instruct(cmosNumber);

	bool ok;
	int value = QInputDialog::getInt(this, tr("frame rate setting"), tr("input fps:"), m_frRate, 0, 50, 1, &ok);
	if (ok)
	{
		m_frRate = value;
		if (!instruct.SetFPS(m_frRate))
		{
			QMessageBox::critical(this, tr("Error"), tr("Failed to set frame rate!"));
			return;
		}
		uploadFlag = true;
	}
}
void ImageWindowItem::onStartActionTriggerd()
{
	InstructionProcess instruct(cmosNumber);
	if(!instruct.AECRun())
	{
		QMessageBox::critical(this, tr("Error"), tr("Failed to upload data!"));
		return;
	}
	uploadFlag = true;
}
void ImageWindowItem::onStopActionTriggerd()
{
	InstructionProcess instruct(cmosNumber);
	if(!instruct.Stop())
	{
		QMessageBox::critical(this, tr("Error"), tr("Failed to stop uploading!"));
		return;
	}
	uploadFlag = false;
}

void ImageWindowItem::onMouseMoved(const QPoint &absPos)
{
	// qDebug()<<absPos;
	QRect rtWnd = geometry();//显示区左上角坐标及显示区的长宽
	const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
	m_mousePostion.rx() = features->payloadDataWidth*absPos.x() / rtWnd.width();
	m_mousePostion.ry() = features->payloadDataWidth*absPos.y() / rtWnd.height();
	emit cursorPositionChanged(m_mousePostion.x(),m_mousePostion.y());
}

void ImageWindowItem::paintEvent(QPaintEvent *)//实现重绘，显示图像
{
    displayModeDisplay();
}
//void  ImageWindowItem::mousePressEvent(QMouseEvent *e)//单击切换显示
//{
//	if (e->button()== Qt::LeftButton )
//	{
//		emit leftMouseClicked();
//	}
//}
//void ImageWindowItem::mouseMoveEvent(QMouseEvent *e)
//{
//	emit mouseMoved(e->pos());
//}
//void ImageWindowItem::mouseDoubleClickEvent(QMouseEvent *e)//双击恢复  //怎么知道这是双击-->这是QMouseEvent事件。
//{
//	emit doubleClickEvent();
//}
void ImageWindowItem::setCmosNumber(Instruction::CMOSID number)//设置显示通道
{
	cmosNumber = number;
}
int ImageWindowItem::setDataItemPtr(std::shared_ptr<IDataItem>& ptr)
{
   IWindowItem::setDataItemPtr(ptr);
   const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
   if (!features)
       return ERR_INTERNAL_ERROR;
   m_imgBuffer.reset(new unsigned char[m_range.width()*m_range.height()]);    //图像数据智能指针
   return EXEC_SUCCESS;
}

int ImageWindowItem::saveToFile() const
{
	if (!m_file)
	{
		return ERR_NOT_SET_FILE;
	}
	if (!m_dataProvider || !m_imgBuffer || !m_image)
		return ERR_NOT_SET_DATAPTR;
	unsigned char *buffer{ new unsigned char[m_range.width()*m_range.height()] };
	unsigned char *bufferConverted{ new unsigned char[m_range.width()*m_range.height() * 3] };
	m_dataProvider->copyArea(0, 0, m_range.width(), m_range.height(), buffer);

	std::string name;
	char temp[10];
	sprintf_s(temp, 10, "COMS%d", cmosNumber);
	name += temp;
	
	if (cmosNumber == 0)
	{
		m_convertor->convert(bufferConverted, buffer, m_range.height(), m_range.width());
		m_file->save(bufferConverted, m_range.height(), m_range.width(), /*"../QquickLookCamera/BMP/"*/"C:\\Users\\CMOS\\Desktop\\MultiCOMS\\BMP\\", name);
	}
	else  //灰度图像直接存储原始bayer(8为深度)数据   //如果全部转换后存储，8->32转换有错。
		m_file->save(buffer, m_range.height(), m_range.width(), "C:\\Users\\CMOS\\Desktop\\MultiCOMS\\BMP\\", name);  //不能为空指针，否则访问地址出错，而且放在displayModeDisplay()会实时保存
	
	delete buffer;
	delete bufferConverted;
}

int ImageWindowItem::displayModeDisplay() const
{
    if (!m_dataProvider || !m_imgBuffer || !m_image)
        return ERR_NOT_SET_DATAPTR;
    if (!m_convertor)       //表明转换过后才显示
        return ERR_NOT_SET_CONVERTOR;
    const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
    if (!features)
        return ERR_INTERNAL_ERROR;

    //fetch pixel around cursor, convert to rgba format
    QRect rtWnd = geometry();//显示区左上角坐标及显示区的长宽
	//m_range显示图像的大小
    QRect rtRange(
                m_cursorPostion.x()-m_range.width()/2,
                m_cursorPostion.y()-m_range.height()/2,
                m_range.width(),
                m_range.height()
                );
    QRect rtData(0,0,features->payloadDataWidth, features->linesPerFrame);
    //qDebug()<<rtWnd<<rtRange<<"->";
    if (!rtData.contains(rtRange))//数据区不包含图像显示区
    {
        //adjust target rectangle
        if (!rtData.contains(0, rtRange.top()))
            rtRange.setTop(0);
        if (!rtData.contains(rtRange.left(), 0))
            rtRange.setLeft(0);
        if (!rtData.contains(rtRange.right(), 0))
        {
            rtRange.setRight(rtData.right());
            int left = rtData.right()-m_range.width();
            rtRange.setLeft(left < 0 ? 0 : left);
        }
        if (!rtData.contains(rtRange.right(), rtRange.bottom()))
        {
            rtRange.setBottom(rtData.bottom());
            int top = rtData.bottom()-m_range.height();
            rtRange.setTop(top < 0 ? 0 : top);
        }

        rtRange.setWidth(m_range.width());
        rtRange.setHeight(m_range.height());
    }
    //qDebug()<<rtRange<<"<-\n";
    unsigned char *pixel = m_imgBuffer.get();
	//put sth useful information
	QString str;
	str.sprintf("COMS %d (%d,%d)", cmosNumber,m_mousePostion.x(),m_mousePostion.y());  //图像上标记通道和当前坐标（相对于图像1280*1024）
	
	//	 str.sprintf("[%d,%d, %d*%d] H:%.2f, V:%.2f", rtRange.left()*features->colSampleLevel, rtRange.top()*features->rowSampleLevel, rtRange.width(), rtRange.height(),
	//	 static_cast<float>(pic.width())/rtRange.width(), static_cast<float>(pic.height())/rtRange.height());
	
    if (!m_dataProvider->copyArea(rtRange.left(), rtRange.top(), rtRange.width(), rtRange.height(), pixel))
        return ERR_INVALID_PARAM; 
    m_convertor->convert(m_image->bits(), pixel, rtRange.width(), rtRange.height());

	//scale and paint
    QPainter painter(const_cast<ImageWindowItem*>(this));
    QPixmap pic = QPixmap::fromImage(*m_image).scaled(rtWnd.width(), rtWnd.height(), Qt::KeepAspectRatio);
    QRect rtDst((rtWnd.width()-pic.width())/2,(rtWnd.height()-pic.height())/2,pic.width(), pic.height());
    painter.drawPixmap(rtDst, pic);//显示图像

	painter.setPen(m_fontColor);
	painter.drawText(rtDst, str);
    return EXEC_SUCCESS;
}

IWindowItem* ImageWindowItem::clone() const
{
	ImageWindowItem* item = new ImageWindowItem;
	item->setConvertor(m_convertor);
	item->setSave(m_file);
//	item->setRgbSave(m_rgbFile);
	return item;
}


int ImageWindowItem::refresh()  //调用update(),自动调用paintEvet();再调用displayModeDisplay().
{
    update();    
    return EXEC_SUCCESS;
}

void ImageWindowItem::setMagnifierRange(int width, int height)
{
    if (width == m_image->width() && height == m_image->height())
        return;
    if (width < 0 || height < 0)
        return;
    if (!m_dataProvider)
        return ;
    const FeaturesOfDataItem* features = m_dataProvider->constDataFeatures();
    if (!features)
        return;
    if (width > features->payloadDataWidth || height > features->linesPerFrame)
        return ;

    m_imgBuffer.reset();

    m_range = {width, height};
    if (m_image)
        delete m_image;
 // m_image = new QImage(m_range, QImage::Format_ARGB32);
	m_image = new QImage(m_range,strFormat);
    m_imgBuffer.reset(new unsigned char[m_range.width()*m_range.height()]);

    QWidget::update();
}
