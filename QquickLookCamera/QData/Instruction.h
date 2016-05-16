#pragma once
#include "initsock.h"
#include <thread>
#pragma pack (push)
#pragma pack (1)
struct CMD
{
	//16 byte + 8 byte
	unsigned int synWord{ 0 }; // 命令同步字 - 4 byte
	unsigned int dataLength{ 0 }; // 命令数据长度 - 4 byte
	unsigned short counter{ 0 }; // 命令计数器 - 2 byte
	unsigned short form{ 0 }; // 命令类型
	unsigned short timeStamp{ 0 }; // 时间戳
	unsigned short checkSum{ 0 }; // 校验和

	unsigned long long data{ 0 }; // 命令数据
};

#pragma pack (pop)
class Instruction
{
//构造函数&析构函数
public:
	Instruction(USHORT port_local_send, USHORT port_local_recv, USHORT port_far_send, char* ip_local, char* ip_far);
	~Instruction();

//数据
public:
	//枚举类型CMOSID
	enum CMOSID{ NoCMOS, CMOSE, CMOS1, CMOS2, CMOS3 };
private:
	CMOSID cmosId;
	CMD *cmd;

	int m_FPS;
	long long m_frLength{ 10000 };//帧长
	long long m_frExpoTime{ 8000 };//曝光时间，小于帧长

	bool m_recving{ false }; //线程退出标识
	bool m_sendingAECRun{ false }; //线程退出标识
	bool m_sendingManualRun{ false }; //线程退出标识
	bool m_sendingSetFPS{ false }; //线程退出标识

	std::thread m_thrSendSetFPS; //线程句柄
	std::thread m_thrRecv; //线程句柄
	std::thread m_thrSendManualRun; //线程句柄
	std::thread m_thrSendAECRun; //线程句柄
//socket
protected:
	CInitSock c;//Winsock库的装入和释放
	SOCKET sock_send;
	SOCKET sock_recv;
	sockaddr_in addr_local_send;
	sockaddr_in addr_far_send;
	sockaddr_in addr_local_recv;
//
public:
	//
	virtual bool startSendAECRun()
	{
		if (m_sendingAECRun)
			return false;
		m_sendingAECRun = true;
		m_thrSendAECRun = std::thread([this](){this->AECRun(); });
		return true;
	}
	virtual void stopSendAECRun()
	{
		m_sendingAECRun = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrSendAECRun.joinable())
			m_thrSendAECRun.join();
	}
	//
	virtual bool startSendManualRun(long long _expoTime)
	{
		m_frExpoTime = _expoTime;
		if (m_sendingManualRun)
			return false;
		m_sendingManualRun = true;
		m_thrSendManualRun = std::thread([this](){this->ManualExposure(m_frExpoTime); });
		return true;
	}
	virtual void stopSendManualRun()
	{
		m_sendingManualRun = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrSendManualRun.joinable())
			m_thrSendManualRun.join();
	}
	virtual bool startSendSetFPS(int _fps)
	{
		m_FPS = _fps;
		if (m_sendingSetFPS)
			return false;
		m_sendingSetFPS = true;
		m_thrSendSetFPS = std::thread([this](){this->SetFPS(m_FPS); });
		return true;
	}
	//停止发送
	virtual void stopSendSetFPS()
	{
		m_sendingSetFPS = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrSendSetFPS.joinable())
			m_thrSendSetFPS.join();
	}

	//
	virtual bool startRecv()
	{
		if (m_recving)
			return false;
		m_recving = true;
		m_thrRecv = std::thread([this](){this->receive(); });
		return true;
	}
	virtual void stopRecv()
	{
		m_recving = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrRecv.joinable())
			m_thrRecv.join();
	}
//发送
private:
	unsigned short cmdCounter;//发送指令计数，初值为0
public:
	void SetCmosId(CMOSID id);
	void AECRun();//开始上传图像，自动曝光
	void ManualExposure(long long _expoTime);//自动曝光
	void SetFPS(int _fps);
	void Stop();
protected:
	bool buildCmdReg(int _addr, int _data);
	void sendCmdReg(int _addr, int _data);
	void PowerUp();
	void EnableClockManagement1();
	void EnableClockManagement2();
	void RequiredRegisterUpload();
	void ExtraConfig();
	void SoftPowerUp();
	void EnableSequencer();

	void DisableSequencer();
	void SoftPowerDown();
	void DisableClockManagement2();
	void DisableClockManagement1();
	void PowerDown();
//接收
public:
	bool DONEFLAG = false;
protected:
	void receive();
};