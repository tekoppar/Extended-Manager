#pragma once

#pragma pack(push, 1)

class GhostPlayer : public MonoBehaviour
{
public:
	unsigned char x17[0x17];
	unsigned char OriRig[0x8]; // 0x18
	unsigned char Puppets[0x8]; // 0x20

	void Run()
	{
		auto Run_address = Assembly_BaseAddr + 0x9FF830;
		using GhostPlayer__Run = void(*)(GhostPlayer*);
		auto Run = reinterpret_cast<GhostPlayer__Run>(Run_address);
		return Run(this);
	}

	void Stop()
	{
		auto Stop_address = Assembly_BaseAddr + 0xA000C0;
		using GhostPlayer__Stop = void(*)(GhostPlayer*);
		auto Stop = reinterpret_cast<GhostPlayer__Stop>(Stop_address);
		return Stop(this);
	}

protected:
private:

};
#pragma pack(pop)