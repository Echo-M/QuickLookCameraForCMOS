#pragma once
#include "InstructionUnit.h"
class SetExpoTimeInstruction :
	public InstructionUnit
{
public:
	SetExpoTimeInstruction(USHORT port_local_send, USHORT port_local_recv, USHORT port_far_send, char* ip_local, char* ip_far);
	~SetExpoTimeInstruction();
	void setExpoTime(int _time)
	{
		m_expoTime = _time;
	}
private:
	unsigned int m_expoTime;
protected:
	virtual void thrSend() override;
};

