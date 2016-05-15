#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_
#include "../QData/initsock.h"


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

//PC->FPGA的指令，控制相机参数改变 ；但是先要要个指令触发硬件发数据，然后InputCOMS开始接收数据。
class Instruction
{
public:
	enum CMOSID{ NoCMOS, CMOSE, CMOS1, CMOS2, CMOS3 };
public:
	Instruction(USHORT port_target, ULONG ip_target, USHORT port_local, ULONG ip_local);
	~Instruction();

	//设置CMOS编号，在调用发送指令的函数前应设置本函数
	bool SetCmosId(CMOSID id);
	bool Initial();
	bool Start();

protected:
	bool Open();
	bool Reset();
	bool PowerUp();
	bool EnableClockManagement1();
	bool EnableClockManagement2();
	bool RequiredRegisterUpload();
	bool SoftPowerUp();
	bool EnableSequencer();

	bool DisableSequencer();
	bool SoftPowerDown();
	bool DisableClockManagement2();
	bool DisableClockManagement1();
	
protected:
	bool buildCmdReg(CMD* _cmd, int _addr, int _data);
	bool sendCmdReg(int _addr, int _data);

protected:
	CInitSock c;//Winsock库的装入和释放
	sockaddr_in addr_local;//本地地址
	sockaddr_in addr_target;//远程地址
	sockaddr_in addr_far;//远程地址

private:
	CMOSID cmosId;
	unsigned short cmdCounter;//初值为0
	const int maxSend; //允许的最大发送次数
	const int maxWaitS; //允许的最长等待时间s
	const int maxWaitUS; //允许的最长等待时间us
};

#endif