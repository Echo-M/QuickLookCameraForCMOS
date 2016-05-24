#include "InstructionProcess.h"


InstructionProcess::InstructionProcess(Instruction::CMOSID _cmosId) :
	m_cmosId(_cmosId),
	port_local_send(3954),
	port_far_send(4567),
	port_local_recv(39550),
	ip_local("192.168.1.2"),
	ip_far("192.168.1.1")
{
}


InstructionProcess::~InstructionProcess()
{
}

void InstructionProcess::AECRun()
{
	instruct = new Instruction(port_local_send, port_local_recv, port_far_send, ip_local, ip_far);
	instruct->SetCmosId(m_cmosId);
	instruct->startRecv();
	instruct->startSendAECRun();
	while (!instruct->DONEFLAG);
	instruct->stopRecv();
	instruct->stopSendAECRun();
	delete instruct;
}

void InstructionProcess::SetFPS(int _fps)
{
	instruct = new Instruction(port_local_send, port_local_recv, port_far_send, ip_local, ip_far);
	instruct->SetCmosId(m_cmosId);
	instruct->startSendSetFPS(_fps);
	instruct->startRecv();
	while (!instruct->DONEFLAG);
	instruct->stopRecv();
	instruct->stopSendSetFPS();
	delete instruct;
}

void InstructionProcess::setExpoTime(unsigned int _expoTime)
{
	instruct = new Instruction(port_local_send, port_local_recv, port_far_send, ip_local, ip_far);
	instruct->SetCmosId(m_cmosId);
	instruct->startSendsetExpoTime(_expoTime);
	instruct->startRecv();
	while (!instruct->DONEFLAG)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	instruct->stopRecv();
	instruct->stopSendsetExpoTime();
	delete instruct;
}

void InstructionProcess::Stop()
{
	instruct = new Instruction(port_local_send, port_local_recv, port_far_send, ip_local, ip_far);
	instruct->SetCmosId(m_cmosId);
	instruct->Stop();
	delete instruct;
}

void InstructionProcess::SetAGCG(float _total)
{
	instruct = new Instruction(port_local_send, port_local_recv, port_far_send, ip_local, ip_far);
	instruct->SetCmosId(m_cmosId);
	instruct->startSendSetAGCG(_total);
	instruct->startRecv();
	while (!instruct->DONEFLAG)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	instruct->stopRecv();
	instruct->stopSendSetAGCG();
	delete instruct;
}

void InstructionProcess::SetDG(float _dg)
{
	instruct = new Instruction(port_local_send, port_local_recv, port_far_send, ip_local, ip_far);
	instruct->SetCmosId(m_cmosId);
	instruct->startSendSetDG(_dg);
	instruct->startRecv();
	while (!instruct->DONEFLAG)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	instruct->stopRecv();
	instruct->stopSendSetDG();
	delete instruct;
}