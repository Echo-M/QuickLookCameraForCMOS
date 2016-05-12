#include "Instruction.h"
#include <iostream>
Instruction::Instruction(USHORT port_target, ULONG ip_target, USHORT port_local = htons(4567), ULONG ip_local = inet_addr("192.168.1.1")) :
	cmdCounter(0),
	maxSend(5),
	maxWaitS(2),
	maxWaitUS(0),
	cmosId(NoCMOS)
{
	//填写本地地址信息
	addr_local.sin_family = AF_INET;
	addr_local.sin_addr.S_un.S_addr = ip_local;
	addr_local.sin_port = htons(port_local);

	//填写远程地址信息
	addr_target.sin_family = AF_INET;
	addr_target.sin_addr.S_un.S_addr = ip_target;
	addr_target.sin_port = htons(port_target);

	//填写本地地址信息
	addr_far.sin_family = AF_INET;
	addr_far.sin_addr.S_un.S_addr = ip_target;
	addr_far.sin_port = htons(3954);//之后要修改
}

Instruction::~Instruction()
{
	
}

bool Instruction::SetCmosId(CMOSID id)
{
	if (id == NoCMOS)
		return false;
	cmosId = id;
	return true;
}
bool Instruction::buildCmdReg(CMD* _cmd, int _addr, int _data)
{
	if (cmosId == NoCMOS)
		return false;
	_cmd->synWord = htonl(0x03CCF0FF);
	_cmd->dataLength = htonl(0x00000002);
	_cmd->counter = htons(cmdCounter);
	switch (cmosId)
	{
	case CMOSE:
		_cmd->form = htons(0x0300);
		break;
	case CMOS1:
		_cmd->form = htons(0x0400);
		break;
	case CMOS2:
		_cmd->form = htons(0x0500);
		break;
	case CMOS3:
		_cmd->form = htons(0x0600);
		break;
	default:
		break;
	}
	_cmd->timeStamp = htons(0x0000);
	_cmd->checkSum = htons(0x0000);
	unsigned long long cmdData{ 0x8000000000000000 };
	unsigned long long a = _addr*4294967296;
	cmdData |= a;
	cmdData |= _data;
	_cmd->data = htonll(cmdData);
	return true;
}

bool Instruction::sendCmdReg(int _addr, int _data)
{
	int alen = sizeof(addr_far);
	fd_set fdsock;//套接字集合
	struct timeval timeout;
	CMD* cmd = new CMD; //发送和接收的指令
	int count{ 0 }; //发送次数计数
	timeout.tv_sec = maxWaitS; // 等待时间（s）
	timeout.tv_usec = maxWaitUS; // 等待时间（μs）

	//while (1)
	for (int i = 0; i < 10;++i)
	{
		if (!buildCmdReg(cmd, _addr, _data))
		{
			return false;
		}

		//发送指令
		ULONG u1 = 1;
		SOCKET sock;
		sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		::ioctlsocket(sock, FIONBIO, (ULONG*)&u1);//设为非阻塞模式
		//将套接字与对应地址绑定
		if (::bind(sock, (LPSOCKADDR)&addr_local, sizeof(addr_local)) == SOCKET_ERROR)
		{
			std::cout << "绑定失败" << std::endl;
			//return;
		}
		::sendto(sock, (char*)cmd, sizeof(CMD), 0, (sockaddr*)&addr_target, sizeof(addr_target));
		::closesocket(sock);

		cmdCounter++;

		////接收指令
		//ULONG u2 = 1;
		//sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		//::ioctlsocket(sock, FIONBIO, (ULONG*)&u2);//设为非阻塞模式
		////将套接字与对应地址绑定
		//if (::bind(sock, (LPSOCKADDR)&addr_local, sizeof(addr_local)) == SOCKET_ERROR)
		//{
		//	std::cout << "绑定失败" << std::endl;
		//	//return;
		//}
		//FD_ZERO(&fdsock); // 先清空
		//FD_SET(sock, &fdsock);
		//int nret = ::select(0, &fdsock, NULL, NULL, &timeout);//select()返回值：有未决I/O的套接字句柄的个数
		//if (nret > 0)
		//{
		//	if (FD_ISSET(sock, &fdsock))//若该套接字可读
		//	{
		//		int nrecv = ::recvfrom(sock, (char*)cmd, sizeof(CMD), 0, (LPSOCKADDR)&addr_far, &alen);
		//		if (nrecv == 24)
		//		if (ntohl(cmd->synWord) == 0x05CCF0FF)
		//		{
		//			std::cout << "第" << cmdCounter <<"条指令发送成功！"<< std::endl;
		//			::closesocket(sock);
		//			return true;
		//		}
		//	}
		//}
		//count++;
		//if (count >= maxSend)
		//{
		//	std::cout << "第" << cmdCounter << "条指令发送失败！" << std::endl;
		//	::closesocket(sock);
		//	return false;
		//}
		//::closesocket(sock);
	}
}

bool Instruction::Initial()
{
	/*if (!Start())
		return false;
	if (!Reset())
		return false;*/
	if (!PowerUp())
		return false;
	if (!EnableClockManagement1())
		return false;
	if (!EnableClockManagement2())
		return false;
	if (!RequiredRegisterUpload())
		return false;
	if (!SoftPowerUp())
		return false;

	return true;
}

bool Instruction::Start()
{
	if (!EnableSequencer())
		return false;

	return true;
}

//bool Instruction::Open()
//{
//	if (cmosId == NoCMOS)
//		return false;
//
//	CMD *cmd = new CMD;
//	cmd->synWord = htonl(0x03CCF0FF);
//	cmd->dataLength = htonl(0x00000002);
//	cmd->counter = htons(cmdCounter);
//	cmd->form = htons(0x0100);
//	cmd->timeStamp = htons(0x0000);
//	cmd->checkSum = htons(0x0000);
//	cmd->data = htonll(0x0000000100000000);
//
//	sockaddr_in addr_far;
//	int alen = sizeof(addr_far);
//	fd_set fdsock;//套接字集合
//	struct timeval timeout;
//	int count{ 0 }; //发送次数计数
//	timeout.tv_sec = maxWaitS; // 等待时间（s）
//	timeout.tv_usec = maxWaitUS; // 等待时间（μs）
//	while (1)
//	{
//		::sendto(sock, (char*)cmd, sizeof(CMD), 0, (sockaddr*)&addr_target, sizeof(addr_target));
//		cmdCounter++;
//		FD_ZERO(&fdsock); // 先清空
//		FD_SET(sock, &fdsock);
//		int nret = ::select(0, &fdsock, NULL, NULL, &timeout);//select()返回值：有未决I/O的套接字句柄的个数
//		if (nret > 0)
//		{
//			if (FD_ISSET(sock, &fdsock))//若该套接字可读
//			{
//				int nrecv = ::recvfrom(sock, (char*)cmd, sizeof(CMD), 0, (LPSOCKADDR)&addr_far, &alen);
//				if (nrecv == 24)
//				if (ntohl(cmd->synWord) == 0x05CCF0FF)
//				{
//					return true;
//				}
//			}
//		}
//		count++;
//		if (count >= maxSend)
//		{
//			return false;
//		}
//	}
//}

//bool Instruction::Reset()
//{
//	if (cmosId == NoCMOS)
//		return false;
//
//	CMD *cmd = new CMD;
//	cmd->synWord = htonl(0x03CCF0FF);
//	cmd->dataLength = htonl(0x00000002);
//	cmd->counter = htons(cmdCounter);
//	cmd->form = htons(0x0100);
//	cmd->timeStamp = htons(0x0000);
//	cmd->checkSum = htons(0x0000);
//	cmd->data = htonll(0x0000000200000000);
//	
//	sockaddr_in addr_far;
//	int alen = sizeof(addr_far);
//	fd_set fdsock;//套接字集合
//	struct timeval timeout;
//	int count{ 0 }; //发送次数计数
//	timeout.tv_sec = maxWaitS; // 等待时间（s）
//	timeout.tv_usec = maxWaitUS; // 等待时间（μs）
//	while (1)
//	{
//		::sendto(sock, (char*)cmd, sizeof(CMD), 0, (sockaddr*)&addr_target, sizeof(addr_target));
//		cmdCounter++;
//		FD_ZERO(&fdsock); // 先清空
//		FD_SET(sock, &fdsock);
//		int nret = ::select(0, &fdsock, NULL, NULL, &timeout);//select()返回值：有未决I/O的套接字句柄的个数
//		if (nret > 0)
//		{
//			if (FD_ISSET(sock, &fdsock))//若该套接字可读
//			{
//				int nrecv = ::recvfrom(sock, (char*)cmd, sizeof(CMD), 0, (LPSOCKADDR)&addr_target, &alen);
//				if (nrecv == 24)
//				if (ntohl(cmd->synWord) == 0x05CCF0FF)
//				{
//					return true;
//				}
//			}
//		}
//		count++;
//		if (count >= maxSend)
//		{
//			return false;
//		}
//	}
//}

bool Instruction::PowerUp()
{
	if (cmosId == NoCMOS)
		return false;

	CMD *cmd = new CMD;
	cmd->synWord = htonl(0x03CCF0FF);
	cmd->dataLength = htonl(0x00000002);
	cmd->counter = htons(cmdCounter);
	cmd->form = htons(0x0200);
	cmd->timeStamp = htons(0x0000);
	cmd->checkSum = htons(0x0000);
	cmd->data = htonll(0x0000000100000000);
	
	int alen = sizeof(addr_far);
	fd_set fdsock;//套接字集合
	struct timeval timeout;
	int count{ 0 }; //发送次数计数
	timeout.tv_sec = maxWaitS; // 等待时间（s）
	timeout.tv_usec = maxWaitUS; // 等待时间（μs）
	//while (1)
	for (int i = 0; i < 10; ++i)
	{
		//发送指令
		ULONG u1 = 1;
		SOCKET sock;
		sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		::ioctlsocket(sock, FIONBIO, (ULONG*)&u1);//设为非阻塞模式
		//将套接字与对应地址绑定
		if (::bind(sock, (LPSOCKADDR)&addr_local, sizeof(addr_local)) == SOCKET_ERROR)
		{
			std::cout << "绑定失败" << std::endl;
			//return;
		}
		::sendto(sock, (char*)cmd, sizeof(CMD), 0, (sockaddr*)&addr_target, sizeof(addr_target));
		::closesocket(sock);

		cmdCounter++;

		////接收指令
		//ULONG u2 = 1;
		//sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		//::ioctlsocket(sock, FIONBIO, (ULONG*)&u2);//设为非阻塞模式
		////将套接字与对应地址绑定
		//if (::bind(sock, (LPSOCKADDR)&addr_local, sizeof(addr_local)) == SOCKET_ERROR)
		//{
		//	std::cout << "绑定失败" << std::endl;
		//	//return;
		//}
		//FD_ZERO(&fdsock); // 先清空
		//FD_SET(sock, &fdsock);
		//int nret = ::select(0, &fdsock, NULL, NULL, &timeout);//select()返回值：有未决I/O的套接字句柄的个数
		//if (nret > 0)
		//{
		//	if (FD_ISSET(sock, &fdsock))//若该套接字可读
		//	{
		//		int nrecv = ::recvfrom(sock, (char*)cmd, sizeof(CMD), 0, (LPSOCKADDR)&addr_far, &alen);
		//		if (nrecv == 24)
		//		if (ntohl(cmd->synWord) == 0x05CCF0FF)
		//		{
		//			std::cout << "上电：第" << cmdCounter << "条指令发送成功！" << std::endl;
		//			::closesocket(sock);
		//			return true;
		//		}
		//	}
		//}
		//count++;
		//if (count >= maxSend)
		//{
		//	std::cout << "上电：第" << cmdCounter << "条指令发送失败！" << std::endl;
		//	::closesocket(sock);
		//	return false;
		//}
		//::closesocket(sock);
	}
}

bool Instruction::EnableClockManagement1()
{
	//Part1
	if (cmosId == CMOSE)
	{
		if (!sendCmdReg(2, 0x0002))//Monochrome sensor parallel mode selection
			return false;
	}
	else
	{
		if (!sendCmdReg(2, 0x0003))//Color sensor parallel mode selection
			return false;
	}
	if (!sendCmdReg(32, 0x200C))//Configure clock management
		return false;
	if (!sendCmdReg(20, 0x0000))//Configure clock management
		return false;
	if (!sendCmdReg(16, 0x0007))//Configure PLL bypass mode
		return false;

	return true;
}

bool Instruction::EnableClockManagement2()
{
	//Part2
	if (!sendCmdReg(9, 0x0000))//Release clock generator soft reset
		return false;
	if (!sendCmdReg(32, 0x200E))//Enable logic clock
		return false;
	if (!sendCmdReg(34, 0x0001))//Enable logic blocks
		return false;

	return true;
}

bool Instruction::RequiredRegisterUpload()
{
	if (!sendCmdReg(41, 0x085A))//
		return false;
	if (!sendCmdReg(129, 0x0<<13 | 0x0001))//129[13]-0x0
		return false;
	if (!sendCmdReg(65, 0x288B))//
		return false;
	if (!sendCmdReg(66, 0x53C5))//
		return false;
	if (!sendCmdReg(67, 0x0344))//
		return false;
	if (!sendCmdReg(68, 0x0085))//
		return false;
	if (!sendCmdReg(70, 0x4800))//
		return false;
	if (!sendCmdReg(128, 0x4710))//
		return false;
	if (!sendCmdReg(197, 0x0103))//
		return false;
	if (!sendCmdReg(176, 0x00F5))//
		return false;
	if (!sendCmdReg(180, 0x00FD))//
		return false;
	if (!sendCmdReg(181, 0x0144))//
		return false;

	return true;
}


bool Instruction::SoftPowerUp()
{
	if (!sendCmdReg(32, 0x200F))//
		return false;
	if (!sendCmdReg(10, 0x0000))//
		return false;
	if (!sendCmdReg(64, 0x0001))//
		return false;
	if (!sendCmdReg(72, 0x0203))//
		return false;
	if (!sendCmdReg(40, 0x0003))//
		return false;
	if (!sendCmdReg(48, 0x0001))//
		return false;
	if (!sendCmdReg(112, 0x0000))//
		return false;

	return true;
}
bool Instruction::EnableSequencer()
{
	if (!sendCmdReg(192, 0x1<<0))//192[0]-0x1
		return false;

	return true;
}
bool Instruction::DisableSequencer()
{
	if (!sendCmdReg(192, 0x0 << 0))//192[0]-0x1
		return false;

	return true;
}
bool Instruction::SoftPowerDown()
{
	if (!sendCmdReg(112, 0x0000))//
		return false; 
	if (!sendCmdReg(48, 0x0000))//
		return false;
	if (!sendCmdReg(40, 0x0000))//
		return false;
	if (!sendCmdReg(72, 0x0200))//
		return false;
	if (!sendCmdReg(64, 0x0000))//
		return false;
	if (!sendCmdReg(10, 0x0999))//
		return false;

	return true;
}
bool Instruction::DisableClockManagement2()
{
	//Part2
	if (!sendCmdReg(34, 0x0000))//Disable logic blocks
		return false;
	if (!sendCmdReg(32, 0x200C))//Disable logic clock
		return false;
	if (!sendCmdReg(9, 0x0009))//Soft reset clock generator
		return false;

	return true;
}
bool Instruction::DisableClockManagement1()
{
	//Part1
	if (!sendCmdReg(16, 0x0000))//Disable PLL
		return false;
	if (!sendCmdReg(8, 0x0099))//Soft reset PLL
		return false;
	if (!sendCmdReg(20, 0x0000))//Configure clock management
		return false;

	return true;
}

