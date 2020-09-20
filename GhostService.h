#pragma once

#pragma pack(push, 1)
class GhostService : public MonoBehaviour
{
public:
	unsigned char x9[0x9];
	unsigned char m_ghosts[0x8]; // 0x10

	int get_TotalGhosts()
	{
		auto get_TotalGhosts_address = Assembly_BaseAddr + 0xB37360;
		using oget_TotalGhosts = int(*)(GhostService*);
		auto get_TotalGhosts = reinterpret_cast<oget_TotalGhosts>(get_TotalGhosts_address);
		return get_TotalGhosts(this);
	}

	void RunGhosts()
	{
		auto RunGhosts_address = Assembly_BaseAddr + 0xB37E00;
		using oRunGhosts = void(*)(GhostService*);
		auto RunGhosts = reinterpret_cast<oRunGhosts>(RunGhosts_address);
		RunGhosts(this);
	}

	void ClearGhosts()
	{
		auto ClearGhosts_address = Assembly_BaseAddr + 0xB37480;
		using oClearGhosts = void(*)(GhostService*);
		auto ClearGhosts = reinterpret_cast<oClearGhosts>(ClearGhosts_address);
		ClearGhosts(this);
	}

	bool get_HasGhosts()
	{
		auto get_HasGhosts_address = Assembly_BaseAddr + 0xB373F0;
		using oget_HasGhosts = bool(*)(GhostService*);
		auto get_HasGhosts = reinterpret_cast<oget_HasGhosts>(get_HasGhosts_address);
		return get_HasGhosts(this);
	}

protected:
private:

};
#pragma pack(pop)