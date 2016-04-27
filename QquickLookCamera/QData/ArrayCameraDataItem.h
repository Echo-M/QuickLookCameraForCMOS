#ifndef ARRAYCAMERADATAITEM_H
#define ARRAYCAMERADATAITEM_H


class IDataItem;
class IDataProcessUnit;

#define FRM_SYNWORD 0x499602D2

class ArrayCameraDataItem : public IDataItem, public IDataProcessUnit
{
protected:
    bool m_dualBuffer{false}; //use dual buffer, ping-pong
    std::shared_ptr<unsigned char> m_dualImageBuffer[2]; //entire image data buffer, dual
    //std::shared_ptr<unsigned char> m_dualAssistBuffer[2]; //entire assist data buffer, dual,6+8=14bytes frame header
    int m_curLineCnt; //channel 4 line counter
    long long m_newFrame{-1}; //frame counter
	long long m_curFrameCnt{ -1 }; //
protected:
    virtual void process() override; //inherit from IProcessingItem

protected:
    void storePayloadData(const unsigned char* buf);

	//将帧计数和各通道的行计数设为-1
	void resetCounter()
	{ m_newFrame = m_curLineCnt = -1; }
public:
    ArrayCameraDataItem();
    ~ArrayCameraDataItem();

    //inherit from IDataItem
    virtual bool setup(int assWidth, int imgWidth, int height) override;
    //copy area of image data
    virtual bool copyArea(int x, int y, int w, int h, unsigned char* extPtr) const override;
    ////get entire image data ptr
    //virtual bool internalImageDataPtr(const unsigned char*& ptr) const override;
    ////get entire assist data ptr
    //virtual bool internalAssistDataPtr(const unsigned char*& ptr) const override;

public:
    unsigned int currentFrameCount() const {return m_curFrameCnt;}
};

#pragma pack (push)
#pragma pack (1)
struct CMOS_FRAME_HEAD
{
	//20 Bytes
	unsigned int synWord{ 0x499602D2 };//帧同步字
	unsigned int dgramCount;//包计数，htonl
	unsigned int channelID;//镜头标识
	unsigned int frmCount;//帧计数
	unsigned int lineCount;//行标识
};
#pragma pack (pop)

#endif // ARRAYCAMERADATAITEM_H
