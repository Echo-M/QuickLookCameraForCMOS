#pragma once
#include "InstructionUnit.h"
class SetFPSInstruction :
	public InstructionUnit
{
public:
	SetFPSInstruction(USHORT port_local_send, USHORT port_local_recv, USHORT port_far_send, char* ip_local, char* ip_far);
	~SetFPSInstruction();
	void setDg(int _fps)
	{
		m_frLength = 180000 / _fps;
	}
private:
	unsigned int m_frLength;
protected:
	virtual void thrSend() override;
};

