#include "SetFPSInstruction.h"


SetFPSInstruction::SetFPSInstruction(USHORT port_local_send, USHORT port_local_recv, USHORT port_far_send, char* ip_local, char* ip_far)
: InstructionUnit(port_local_send, port_local_recv, port_far_send, ip_local, ip_far)
{
	lastSendData = 0x8000000000000000;
	lastSendData |= 200 * 4294967296;//_addr * 4294967296
	lastSendData |= m_frLength;//data
}


SetFPSInstruction::~SetFPSInstruction()
{
}

void SetFPSInstruction::thrSend()
{
	sendCmdReg(200, m_frLength);//����֡��
}