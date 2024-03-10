#include "Data.h"

#include "Offsets.h"
#include "driver.h"
#include "Game.h"
#include<thread>
#include <map>

//DriverController* Controller = nullptr;
Espp* g_pEsp = new Espp();

DWORD Data::ViewMatrixBase;
DWORD Data::UWorld = 0;
DWORD Data::Ue4base;
BYTE ViewMatrixSearch[] =
{
	0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01
};



BYTE ue4[] =
{
 0x7F, 0x45, 0x4C, 0x46, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x28, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x50, 0x30, 0x02, 0x34, 0x00, 0x00, 0x00, 0x68, 0x94, 0xF3, 0x08, 0x00, 0x02, 0x00, 0x05, 0x34, 0x00, 0x20, 0x00, 0x0D, 0x00, 0x28, 0x00, 0x19, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
};
//DWORD Data::GetUe4Base(DWORD StartAddress, DWORD EndAddress)
//{
//	DWORD ViewMatrixBase = 0;
//	std::vector<DWORD_PTR> FoundedBase;
//	Utility::MemSearch(ue4, sizeof(ue4), StartAddress, EndAddress, 0, 0, FoundedBase);
//
//
//
//
//	return FoundedBase[0];
//}



DWORD Data::GetUe4Base(DWORD StartAddress, DWORD EndAddress)
{
	std::vector<DWORD_PTR> FoundedUE4Base;
	Tools::MemSearch(ue4, sizeof(ue4), (DWORD)StartAddress, (DWORD)EndAddress, 0, 0, FoundedUE4Base);

	if (!FoundedUE4Base.empty())
	{
		int Verify = Tools::ReadMemoryEx<int>(FoundedUE4Base[0]);
		if (Verify == 1179403647)
		{
			return FoundedUE4Base[0];
		}
	}

	return 0;
}








DWORD Data::GetViewMatrixBase(DWORD StartAddress, DWORD EndAddress)
{
	DWORD ViewMatrixBase = 0;
	std::vector<DWORD_PTR> FoundedBase;
	Tools::MemSearch(ViewMatrixSearch, sizeof(ViewMatrixSearch), StartAddress, EndAddress, 0, 0, FoundedBase);

	for (int i = 0; i < FoundedBase.size(); i++)
	{
		DWORD Cand = FoundedBase[i] - 0x20;
		DWORD Eng = Tools::ReadMemoryEx<DWORD>(Cand) + 0x20;
		DWORD Tmp = Tools::ReadMemoryEx<DWORD>(Eng) + 0x200;

		float v1, v2, v3, v4;
		v1 = Tools::ReadMemoryEx<float>(Tmp + 0x8);
		v2 = Tools::ReadMemoryEx<float>(Tmp + 0x18);
		v3 = Tools::ReadMemoryEx<float>(Tmp + 0x28);
		v4 = Tools::ReadMemoryEx<float>(Tmp + 0x38);

		if (v1 == 0 && v2 == 0 && v3 == 0 && v4 >= 3)
		{
			ViewMatrixBase = Cand;
			FoundedBase.clear();
			break;
		}
	}

	FoundedBase.clear();
	return ViewMatrixBase;
}



string GetString(DWORD BaseAddress)
{
	char* String = new char[34];
	for (int i = 0; i < 34; i++)
	{
		String[i] = Tools::ReadMemoryEx<char>(BaseAddress + i);
	}

	string Result = String;

	delete[] String;
	return Result;
}

inline std::vector<std::string> split(const std::string& str, const char* separator)
{
	std::vector<std::string> output;
	std::string::size_type prev_pos = 0, pos = 0;
	while ((pos = str.find(separator, pos)) != std::string::npos)
	{
		auto substring(str.substr(prev_pos, pos - prev_pos));
		output.push_back(substring);
		prev_pos = ++pos;
	}
	output.push_back(str.substr(prev_pos, pos - prev_pos));
	return output;
}
std::string GetEntity(DWORD gNames, int id)
{
	auto gname = Tools::ReadMemoryEx<DWORD>(gNames);
	auto fNamePtr = Tools::ReadMemoryEx<DWORD>(gname + int(id / 16384) * 0x4);
	auto fName = Tools::ReadMemoryEx<DWORD>(fNamePtr + int(id % 16384) * 0x4);
	auto entryOffset = fName + 0x8;
	auto nameEntry = Tools::ReadMemoryEx<INT16>(entryOffset);

	auto nameLength = nameEntry >> 6;
	char buff[1028];

	if ((uint32_t)nameLength && nameLength > 0)
	{
		Tools::RPM(LPCVOID(entryOffset), buff, nameLength, 0);

		buff[nameLength] = '\0';

		std::string name_str(buff, nameLength);

		return name_str.c_str();
	}
	else
		return "";

	return "";
}
std::string GetEntityType(DWORD gNames, int id)
{

	auto gname = Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(gNames) + 0x80);
	auto fNamePtr = Tools::ReadMemoryEx<DWORD>(gname + int(id / 16384) * 0x4);
	auto fName = Tools::ReadMemoryEx<DWORD>(fNamePtr + int(id % 16384) * 0x4);
	auto entryOffset = fName + 0x8;
	auto nameEntry = Tools::ReadMemoryEx<INT16>(entryOffset);

	auto nameLength = nameEntry >> 6;
	char buff[1028];

	if ((uint32_t)nameLength && nameLength > 0)
	{
		ReadProcessMemory(Tools::GameProcess, LPCVOID(entryOffset), buff, nameLength, 0);

		buff[nameLength] = '\0';

		std::string name_str(buff, nameLength);

		return name_str.c_str();
	}
	else
		return "";

	return "";
}

struct ObjectName
{
	char Data[64];
};



string GetEntityType2(LONG GNames, LONG Id)
{
	DWORD GName = Tools::ReadMemoryEx<DWORD>(GNames);
	DWORD NamePtr = Tools::ReadMemoryEx<DWORD>(GName + int(Id / 16384) * 0x4);
	DWORD Name = Tools::ReadMemoryEx<DWORD>(NamePtr + int(Id % 16384) * 0x4);
	ObjectName pBuffer = Tools::ReadMemoryEx<ObjectName>(Name + 0x8);

	return string(pBuffer.Data);
}

std::string GetEntityType3(UINT gNames, UINT id)
{

	auto gname = Tools::ReadMemoryEx<UINT>(gNames);
	if (id > 0 && id < 2000000)
	{
		auto page = id / 16384;
		DWORD index = id % 16384;
		auto secPartAddv = Tools::ReadMemoryEx<UINT>(gname + page * 4);
		if (secPartAddv > 0)
		{
			auto nameAddv = Tools::ReadMemoryEx<UINT>(secPartAddv + index * 4);

			if (nameAddv > 0)
			{
				ObjectName pBuffer = Tools::ReadMemoryEx<ObjectName>(nameAddv + 0x8);
				return pBuffer.Data;
			}
		}
	}
	return std::string("");
}


std::wstring read_unicode(const std::uintptr_t address, std::size_t size)
{
	const auto buffer = std::make_unique<wchar_t[]>(size);
	Tools::RPM((LPVOID)address, buffer.get(), size * 2, 0);
	return std::wstring(buffer.get());
}


DWORD dGet(DWORD addr) {
	DWORD buff;
	ReadProcessMemory(Tools::GameProcess, (LPCVOID)addr, &buff, sizeof(DWORD), NULL);
	return buff;
}





template <typename T>
T ReadMemoryEx(DWORD BaseAddress)
{
	T Buffer;
	ReadProcessMemory(Tools::GameProcess, (LPCVOID)BaseAddress, &Buffer, sizeof(Buffer), nullptr);

	return Buffer;
}



std::string ConvertFromUtf16ToUtf8(const std::wstring& wstr)
{
	std::string convertedString;
	int requiredSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, 0, 0, 0, 0);
	if (requiredSize > 0)
	{
		std::vector<char> buffer(requiredSize);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &buffer[0], requiredSize, 0, 0);
		convertedString.assign(buffer.begin(), buffer.end() - 1);
	}
	return convertedString;
}

struct ObjectNameU
{
	wchar_t data[64];
};
std::string GetPlayerName(ULONG Address)
{
	ObjectNameU pBuffer = Tools::ReadMemoryEx<ObjectNameU>(Tools::ReadMemoryEx<UINT>(Address));
	const auto player_name = std::wstring(pBuffer.data);
	if (player_name.empty())
	{
		return "Player";
	}

	return ConvertFromUtf16ToUtf8(player_name);

	/*std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
	return utf8_conv.to_bytes(player_name);*/
}

std::string GetPlayerNameUTF(uint32_t entityAddv)
{
	wchar_t szChar[64] = { '\0' };
	Controller->ReadProcessMemory(read<uint32_t>(entityAddv + Offset::Name), &szChar, sizeof(szChar));
	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
	return utf8_conv.to_bytes(szChar);
}


string GetPlayerFlag(DWORD BaseAddress)
{
	char* String = new char[34];

	for (int i = 0; i < 34; i++)
	{
		String[i] = Tools::ReadMemoryEx<char>(BaseAddress + i * 2);
	}

	string Name = String;

	delete[] String;
	return Name;
}

BOOL IsPlayer(string EntityType)
{
	if (EntityType.find("BP_PlayerPawn") != string::npos
		|| EntityType.find("BP_PlayerCharacter") != string::npos
		|| EntityType.find("BP_CharacterModel") != string::npos
		|| EntityType.find("PlanET_FakePlayer") != string::npos
		|| EntityType.find("PlayerPawn_Infec") != string::npos
		|| EntityType.find("BP_PlayerPawn_FM_C") != string::npos
		|| EntityType.find("BP_PlayerPawn_C") != string::npos
		|| EntityType.find("BP_PlayerPawn_Rune_C") != string::npos
		|| EntityType.find("PlayerPawn_Infec_InvisibleZombie_C") != string::npos
		|| EntityType.find("PlayerPawn_Infec_Human_C") != string::npos
		|| EntityType.find("BP_PlayerPawn_ZombieBase_C") != string::npos
		|| EntityType.find("BP_PlayerPawn_TDM_TPP_C") != string::npos
		|| EntityType.find("BP_PlayerPawn_FM_Bot_C") != string::npos
		|| EntityType.find("BP_PlayerCharacter_SlayTheBot_C") != string::npos
		|| EntityType.find("PlanET_FakePlayer_AIPawn_C") != string::npos
		|| EntityType.find("BP_PlayerPawn_SI_C") != string::npos
		|| EntityType.find("BP_PlayerPawn_Heavy_C") != string::npos
		|| EntityType.find("PlayerPawn_Infec_Revenger_C") != string::npos
		|| EntityType.find("BP_PlayerCharacter_FourMaps_ZNQ4th_C") != string::npos
		|| EntityType.find("PlayerPawn_Infec_NormalZombie_C") != string::npos
		|| EntityType.find("PlayerPawn_Infec_KingZombie_C") != string::npos
		|| EntityType.find("BP_PlayerCharacter_PlanA_C") != string::npos
		|| EntityType.find("BP_PlayerCharacter_PlanX_C") != string::npos
		|| EntityType.find("PlanX_PlayerCharacter_AI_C") != string::npos

		|| EntityType.find("BPPawn_HungerH_C") != std::string::npos 
		|| EntityType.find("BPPawn_HungerB_C") != std::string::npos
		|| EntityType.find("BP_PlayerPawn_TPlanAI_C") != std::string::npos
		|| EntityType.find("BPPawn_VenomVariant_C") != std::string::npos 
		|| EntityType.find("BP_PlayerPawn_ST_AI_C") != std::string::npos 
		|| EntityType.find("BP_PlayerPawn_ST_C") != std::string::npos 
		|| EntityType.find("BPPawn_BurningVariant_C") != std::string::npos 
		|| EntityType.find("BP_PlayerPawn_TPlanAI_Boss_C") != std::string::npos
		|| EntityType.find("BP_PlayerPawn_NoviceAI_C") != std::string::npos)
		
	{
		return TRUE;
	}

	return FALSE;
}

std::string PlayerWeapon(std::string str)
{
	if (str == "BP_Sniper_AWM_C")
		return "AWM";
	else if (str == "BP_Sniper_QBU_C")
		return "QBU";
	else if (str == "BP_Sniper_SLR_C")
		return "SLR";
	else if (str == "BP_Sniper_SKS_C")
		return "SKS";
	else if (str == "BP_Sniper_Mini14_C")
		return "Mini14";
	else if (str == "BP_Sniper_M24_C")
		return "M24";
	else if (str == "BP_Sniper_Kar98k_C")
		return "Kar98k";
	else if (str == "BP_Sniper_VSS_C")
		return "VSS";
	else if (str == "BP_Sniper_Win94_C")
		return "Win94";
	else if (str == "BP_Sniper_Mosin_C")
		return "Mosin";
	else if (str == "BP_Sniper_MK12_C")
		return "MK12";
	else if (str == "BP_Rifle_AUG_C")
		return "AUG";
	else if (str == "BP_Rifle_M762_C")
		return "M762";
	else if (str == "BP_Rifle_SCAR_C")
		return "SCAR";
	else if (str == "BP_Rifle_M416_C")
		return "M416";
	else if (str == "BP_Rifle_M16A4_C")
		return "M16A4";
	else if (str == "BP_Rifle_Mk47_C")
		return "Mk47";
	else if (str == "BP_Rifle_G36_C")
		return "G36";
	else if (str == "BP_Rifle_QBZ_C")
		return "QBZ";
	else if (str == "BP_Rifle_AKM_C")
		return "AKM";
	else if (str == "BP_Rifle_Groza_C")
		return "Groza";
	else if (str == "BP_Other_DP28_C")
		return "DP28";
	else if (str == "BP_Other_M249_C")
		return "M249";
	else if (str == "BP_MachineGun_P90_C")
		return "P90";
	else if (str == "BP_ShotGun_S12K_C")
		return "S12K";
	else if (str == "BP_ShotGun_DP12_C")
		return "DP12";
	else if (str == "BP_ShotGun_S686_C")
		return "S686";
	else if (str == "BP_ShotGun_S1897_C")
		return "S1897";
	else if (str == "BP_ShotGun_SawedOff_C")
		return "SawedOff";
	else if (str == "BP_MachineGun_PP19_C")
		return "PP19";
	else if (str == "BP_MachineGun_TommyGun_C")
		return "TommyGu";
	else if (str == "BP_MachineGun_MP5K_C")
		return "MP5K";
	else if (str == "BP_MachineGun_UMP9_C")
		return "UMP9";
	else if (str == "BP_MachineGun_Vector_C")
		return "Vector";
	else if (str == "BP_MachineGun_Uzi_C")
		return "Uzi";
	else if (str == "BP_Pistol_Flaregun_C")
		return "Flaregun";
	else if (str == "BP_Pistol_R1895_C")
		return "R1895";
	else if (str == "BP_Pistol_Vz61_C")
		return "Vz61";
	else if (str == "BP_Pistol_P92_C")
		return "P92";
	else if (str == "BP_Pistol_P18C_C")
		return "P18C";
	else if (str == "BP_Pistol_R45_C")
		return "R45";
	else if (str == "BP_Pistol_P1911_C")
		return "P1911";
	else if (str == "BP_Pistol_DesertEagle_C")
		return "DesertEagle";
	else if (str == "BP_WEP_Mk14_C")
		return "Mk14";
	else if (str == "BP_Other_CrossBow_C")
		return "CrossBow";
	else if (str == "BP_Grenade_Shoulei_C")
		return "Shoulei Grenade";
	else if (str == "BP_Grenade_Smoke_C")
		return "Smoke Grenade";
	else if (str == "BP_Grenade_Burn_C")
		return "Burn Grenade";
	else
		return "";
	return "";
}
string GetItemType(string Name)
{///name.find("BP_Rifle_AKM_Wrapper_C") != std::string::npos
	if (Setting::Esp_Item_AKM) if (Name.find("BP_Rifle_AKM_Wrapper_C") != std::string::npos) return "AKM";
	if (Setting::Esp_Item_M249) if (Name.find("BP_Other_M249_Wrapper_C") != std::string::npos)return "M249";

	if (Setting::Esp_Item_Mk12) if (Name.find("BP_Other_MK12_Wrapper_C") != std::string::npos)return "MK12";
	if (Setting::plan)  if (Name.find("BP_AirDropPlane_C") != std::string::npos) return "Plan";
	if (Setting::Esp_Item_SCARL) if (Name.find("BP_Rifle_SCAR_Wrapper_C") != string::npos) return "SCAR-L";
	if (Setting::Esp_Item_M416) if (Name.find("BP_Rifle_M416_Wrapper_C") != std::string::npos) return "M416";
	if (Setting::Esp_Item_M24) if (Name.find("BP_Sniper_M24_Wrapper_C") != string::npos) return "M24";
	if (Setting::Esp_Item_Kar98k) if (Name.find("BP_Sniper_Kar98k_Wrapper_C") != string::npos) return "Kar98k";
	if (Setting::Esp_Item_Awm) if (Name.find("BP_Sniper_AWM_Wrapper_C") != string::npos) return "AWM";
	if (Setting::Esp_Item_FlareGun) if (Name.find("BP_Pistol_Flaregun_Wrapper_C") != string::npos) return "Flare Gun";
	if (Setting::Esp_Item_Flare) if (Name.find("BP_Ammo_Flare_Pickup_C") != string::npos) return "Flare";
	//if (Setting::Esp_Item_AirDrop) if (Name.find("AirDropListWrapperActor") != string::npos) return "Air Drop";

	if (Setting::Esp_Item_M762) if (Name.find("BP_Rifle_M762_Wrapper_C") != string::npos) return "M762";
	if (Setting::Esp_Item_Mk47Mutant) if (Name.find("BP_Rifle_Mk47_Wrapper_C") != string::npos) return "Mk47 Mutant";
	if (Setting::Esp_Item_DP28) if (Name.find("BP_Other_DP28_Wrapper_C") != string::npos) return "DP28";
	if (Setting::Esp_Item_SCARL) if (Name.find("BP_Rifle_SCAR_Wrapper_C") != string::npos) return "SCAR-L";
	if (Setting::Esp_Item_M416) if (Name.find("BP_Rifle_M416_Wrapper_C") != string::npos) return "M416";
	if (Setting::Esp_Item_M16A4) if (Name.find("BP_Rifle_M16A4_Wrapper_C") != string::npos) return "M16A4";
	if (Setting::Esp_Item_G36C) if (Name.find("BP_Rifle_G36_Wrapper_C") != string::npos) return "G36C";
	if (Setting::Esp_Item_QBZ) if (Name.find("BP_Rifle_QBZ_Wrapper_C") != string::npos) return "QBZ";

	if (Setting::Esp_Item_QBU) if (Name.find("BP_Sniper_QBU_Wrapper_C") != string::npos) return "QBU";
	if (Setting::Esp_Item_SLR) if (Name.find("BP_Sniper_SLR_Wrapper_C") != string::npos) return "SLR";
	if (Setting::Esp_Item_SKS) if (Name.find("BP_Sniper_SKS_Wrapper_C") != string::npos) return "SKS";
	if (Setting::Esp_Item_Mini14) if (Name.find("BP_Sniper_Mini14_Wrapper_C") != string::npos) return "Mini-14";


	if (Setting::Esp_Item_PP19) if (Name.find("BP_MachineGun_PP19_Wrapper_C") != string::npos) return "PP19";
	if (Setting::Esp_Item_TommyGun) if (Name.find("BP_MachineGun_TommyGun_Wrapper_C") != string::npos) return "Tommy Gun";
	if (Setting::Esp_Item_MP5K) if (Name.find("BP_MachineGun_MP5K_Wrapper_C") != string::npos) return "MP5K";
	if (Setting::Esp_Item_UMP9) if (Name.find("BP_MachineGun_UMP9_Wrapper_C") != string::npos) return "UMP9";
	if (Setting::Esp_Item_Vector) if (Name.find("BP_MachineGun_Vector_Wrapper_C") != string::npos) return "Vector";
	if (Setting::Esp_Item_Uzi) if (Name.find("BP_MachineGun_Uzi_Wrapper_C") != string::npos) return "Uzi";
	if (Setting::Esp_Item_Awmimo) if (Name.find("BP_Ammo_300Magnum_Pickup_C") != std::string::npos) return "300Magnum";
	if (Setting::Esp_Item_762mm) if (Name.find("BP_Ammo_762mm_Pickup_C") != string::npos) return "7.62mm";
	if (Setting::Esp_Item_556mm) if (Name.find("BP_Ammo_556mm_Pickup_C") != string::npos) return "5.56mm";
	if (Setting::Esp_Item_9mm) if (Name.find("BP_Ammo_9mm_Pickup_C") != string::npos) return "9mm";
	if (Setting::Esp_Item_45ACP) if (Name.find("BP_Ammo_45ACP_Pickup_C") != string::npos) return "45ACP";

	if (Setting::Esp_Item_Holo) if (Name.find("BP_MZJ_QX_Pickup_C") != string::npos) return "Holo";


	//if (Setting::Esp_Item_AirDrop) if (Name.find("BP_AirDropBox_C") != string::npos) return "Air Drop";
	if (Setting::Esp_Item_MedKit) if (Name.find("FirstAidbox_Pickup_C") != string::npos) return "Med Kit";
	if (Setting::Esp_Item_FirstAidKit) if (Name.find("Firstaid_Pickup_C") != string::npos) return "First Aid Kit";
	if (Setting::Esp_Item_Painkiller) if (Name.find("Pills_Pickup_C") != string::npos) return "Painkiller";
	if (Setting::Esp_Item_EnergyDrink) if (Name.find("Drink_Pickup_C") != string::npos) return "Energy Drink";
	if (Setting::Esp_Item_AdrenalineSyringe) if (Name.find("Injection_Pickup_C") != string::npos) return "Adrenaline Syringe";

	if (Setting::Esp_Item_Frag) if (Name.find("BP_Grenade_Shoulei_Weapon_Wrapper_C") != string::npos) return "frag";
	if (Setting::Esp_Item_Frag) if (Name.find("BP_Grenade_Shoulei_C") != string::npos) return "Frag";
	if (Setting::Esp_Item_Smoke) if (Name.find("BP_Grenade_Smoke_Weapon_Wrapper_C") != string::npos) return "Smoke";
	if (Setting::Esp_Item_Molotof) 	if (Name.find("BP_Grenade_Burn_C") != std::string::npos)return "Burn";

	if (Setting::Esp_Item_Molotof) if (Name.find("BP_Grenade_Burn_Weapon_Wrapper_C") != string::npos) return "Molotof";

	if (Setting::Esp_Item_Helmet1) if (Name.find("PickUp_BP_Helmet_Lv1") != string::npos) return "Helmet L.1";
	if (Setting::Esp_Item_Helmet2) if (Name.find("PickUp_BP_Helmet_Lv2") != string::npos) return "Helmet L.2";
	if (Setting::Esp_Item_Helmet3) if (Name.find("PickUp_BP_Helmet_Lv3") != string::npos) return "Helmet L.3";

	if (Setting::Esp_Item_Armor1) if (Name.find("PickUp_BP_Armor_Lv1") != string::npos) return "Armor L.1";
	if (Setting::Esp_Item_Armor2) if (Name.find("PickUp_BP_Armor_Lv2") != string::npos) return "Armor L.2";
	if (Setting::Esp_Item_Armor3) if (Name.find("PickUp_BP_Armor_Lv3") != string::npos) return "Armor L.3";
	if (Setting::Esp_Item_x2) if (Name.find("BP_MZJ_2X_Pickup_C") != string::npos) return "2x";
	if (Setting::Esp_Item_x3) if (Name.find("BP_MZJ_3X_Pickup_C") != string::npos) return "3x";
	if (Setting::Esp_Item_x4) if (Name.find("BP_MZJ_4X_Pickup_C") != string::npos) return "4x";
	if (Setting::Esp_Item_x6) if (Name.find("BP_MZJ_6X_Pickup_C") != string::npos) return "6x";
	if (Setting::Esp_Item_x8) if (Name.find("BP_MZJ_8X_Pickup_C") != string::npos) return "8x";
	if (Setting::Esp_Item_Bag1) if (Name.find("PickUp_BP_Bag_Lv1") != string::npos) return "Bag L.1";
	if (Setting::Esp_Item_Bag2) if (Name.find("PickUp_BP_Bag_Lv2") != string::npos) return "Bag L.2";
	if (Setting::Esp_Item_Bag3) if (Name.find("PickUp_BP_Bag_Lv3") != string::npos) return "Bag L.3";
	if (Setting::deadbox) if (Name.find("PlayerDeadInventoryBox") != std::string::npos || Name.find("PickUpListWrapperActor") != std::string::npos) return "Dead-Box";
	if (Setting::Esp_Item_Bag3)if (Name.find("GoldenTokenWrapper_C") != string::npos) return "Token";

	return "Unknown";
}
bool IsBox(std::string classname)
{
	/*if ( classname.find("BP_AirDropBox_C") != std::string::npos)
			return true;*/
	if (classname.find("PickUpListWrapperActor") != std::string::npos)// || classname.find("PlayerDeadInventoryBox") != std::string::npos || classname.find("PlayerDeadBox_C") != std::string::npos)
	{
		return true;
	}
	return false;
}
bool AirrDrop(std::string classname)
{
	// | classname.find("AirDropListWrapperActor") != std::string::npos
	if (classname.find("AirDropBox") != std::string::npos)//AirDropBox
		return true;
	return false;

}
string GetVehicleType(string Name)
{
	if (Name.find("BRDM") != std::string::npos) return "BRDM";
	if (Name.find("Scooter") != std::string::npos) return "Scooter";
	if (Name.find("Motorcycle") != std::string::npos) return "Motorcycle";
	if (Name.find("Snowmobile") != std::string::npos) return "Snowmobile";
	if (Name.find("Tuk") != std::string::npos) return "Tuk";
	if (Name.find("Buggy") != std::string::npos) return "Buggy";
	if (Name.find("open") != std::string::npos) return "Sports";
	if (Name.find("close") != std::string::npos) return "Sportsa";
	if (Name.find("Dacia") != std::string::npos) return "Dacia";
	if (Name.find("Rony") != std::string::npos) return "Rony";
	if (Name.find("UAZ") != std::string::npos) return "UAZ";
	if (Name.find("MiniBus") != std::string::npos) return "Minibus";
	if (Name.find("PG117") != std::string::npos) return "PG117";
	if (Name.find("AquaRail") != std::string::npos) return "Aquarail";
	if (Name.find("CoupeRB") != std::string::npos) return "Coupe RB";
	if (Name.find("ModelY") != std::string::npos) return "Tesla";
	if (Name.find("G-38Anti-GravityMotorcycle") != std::string::npos) return "Gravity";
	if (Name.find("BP_VH_Bigfoot_C") != std::string::npos) return "Monster Truck";
	if (Name.find("Motorglider") != std::string::npos) return "Motor Glider";
	if (Name.find("UTV") != std::string::npos) return "UTV";
	if (Name.find("BP_AirDropPlane_C") != std::string::npos) return "Plane";
	return "Unknown";
}
std::string GetBoxItems(int code)
{
	if (code == 101008)
	{
		Setting::colorcode = weapon::m762;
		return "M762";

	}
	else if (code == 306001)
	{
		Setting::colorcode = weapon::AWMimmo;
		return "AWM Ammo";
	}

	else if (code == 101003)
	{
		Setting::colorcode = weapon::scarl;
		return "SCAR-L";
	}
	else if (code == 302001)
	{

		Setting::colorcode = Colors::ammo7;
		return "7.62";
	}
	else if (code == 303001)
	{

		Setting::colorcode = Colors::ammo5;
		return "5.56";
	}
	else if (code == 602004)
	{
		Setting::colorcode = Colors::Grandes;

		return "Grenade";
	}
	else if (code == 601006)
	{
		Setting::colorcode = Colors::madkit;

		return "Medkit";
	}
	else if (code == 101004)
	{
		Setting::colorcode = weapon::m16;
		return "M416";
	}

	else if (code == 101010)
	{
		Setting::colorcode = Colors::g36;
		return "G36";
	}

	else if (code == 101006)
	{
		Setting::colorcode = Colors::aug;
		return "AUG";
	}

	else if (code == 101101)
	{
		Setting::colorcode = Colors::assm;
		return "ASM"; //time
	}

	else if (code == 101001)
	{
		Setting::colorcode = weapon::AKM;
		return "AKM";
	}

	else if (code == 101005)
	{
		Setting::colorcode = weapon::GROZZA;
		return "Groza";
	}

	else if (code == 103003)
	{
		Setting::colorcode = weapon::AWM;
		return "AWM";
	}

	else if (code == 103002)
	{
		Setting::colorcode = weapon::M24;
		return "M24";
	}

	else if (code == 103001)
	{
		Setting::colorcode = weapon::kar98;
		return "Kar98k";
	}

	else if (code == 103011)
	{
		Setting::colorcode = Colors::mosin;
		return "Mosin";
	}

	else if (code == 502002)
	{
		Setting::colorcode = Colors::helmat;
		return "Helmet Lv.2";
	}

	else if (code == 502003)
	{
		Setting::colorcode = Colors::helmat;
		return "Helmet Lv.3";
	}

	else if (code == 503002)
	{
		Setting::colorcode = Colors::armer;
		return "Armour Lv.2";
	}

	else if (code == 503003)
	{
		Setting::colorcode = Colors::armer;
		return "Armour Lv.3";
	}

	else if (code == 501006)
	{
		Setting::colorcode = Colors::bag;
		return "Bag Lv.3";
	}

	else if (code == 501005)
	{
		Setting::colorcode = Colors::bag;
		return "Bag Lv.2";
	}

	else if (code == 203014)
	{
		Setting::colorcode = Colors::scope3x;
		return "3X";

	}

	else if (code == 203004)
	{
		Setting::colorcode = Colors::scope4x;
		return "4x";
	}

	else if (code == 203015)
	{
		Setting::colorcode = Colors::scope6x;
		return "6x";
	}

	else if (code == 203005)
	{
		Setting::colorcode = weapon::scope8x;
		return "8x";
	}

	else if (code == 106007)
	{
		Setting::colorcode = weapon::Flare;
		return "Flaregun";
	}

	else if (code == 105001)
	{
		Setting::colorcode = Colors::M249;
		return "M249";
	}

	else if (code == 105002)
	{
		Setting::colorcode = Colors::dp;
		return "DP28";
	}

	else if (code == 105010)
	{
		Setting::colorcode = Colors::mg3;
		return "MG3";
	}

	return "tatti";
}
std::string getState(int state)
{
	switch (state)
	{
	case 0:
		return "AFK";
	case 1:
		return "In Water";
	case 8:
		return "Standing";
	case 9:
		return "Walking";
	case 10:
		return "Landing";
	case 11:
		return "Running";
	case 16:
		return "Crouching";
	case 17:
		return "Crouching Walk";
	case 19:
		return "Crouching Run";
	case 32:
		return "Snaking";
	case 33:
		return "Snaking Walk";
	case 35:
		return "Snaking Run";
	case 5445:
	case 762:
		return "Snake";
	case 72:
	case 73:
	case 75:
		return "Jumping";
	case 264:
	case 272:
	case 273:
	case 288:
	case 265:
	case 329:
		return "Relaoding";
	case 136:
	case 137:
	case 144:
	case 145:
	case 160:
	case 648:
	case 649:
	case 1160:
	case 1161:
	case 1169:
	case 201:
		return "Firing";
	case 4194304:
	case 4194307:
		return "Swimming";
	case 131070:
	case 131071:
	case 131072:
	case 131073:
	case 131074:
	case 131075:
		return "Knocked";
	case 524296:
		return "Driving Vehicle";
	case 524288:
		return "Driving Boat";
	case 1048584:
		return "Set in Vehicle";
	case 1048576:
		return "Set in Boat";
	case 33554440:
		return "Set in Plane";
	case 3146248:
		return "Aim in vehicle";
	case 3146240:
		return "Aim in boat";
	case 3145736:
		return "Beek in vehicle";
	case 3145728:
		return "Beek in boat";
	case 1050632:
		return "Change vehicle seat";
	case 1050624:
		return "Change boat seat";
	case 32784:
		return "Reviving";
	case 16392:
	case 16393:
	case 16401:
	case 16416:
	case 16417:
	case 16457:
	case 16400:
	case 17401:
	case 17417:
	case 17424:
	case 17425:
		return "Throwing Bomp";
	case 16777224:
		return "Climping";
	case 8200:
	case 8208:
		return "Punish, Stab";
	case 520:
	case 544:
	case 521:
	case 656:
	case 528:
		return "Aiming";
	case 1680:
	case 1672:
	case 1673:
	case 1032:
	case 1544:
	case 1545:
	case 1033:
		return "Peeking";
	case 2056:
		return "Change Weapon";
	case 65544:
		return "Healing";
	case 65545:
		return "Healing & Walk";
	case 268435464:
		return "Playing Emotion";
	case 4194305:
		return "Diving, Floating";
	}

	return std::to_string(state);
}
std::string GetGrenadeType(std::string classname)
{
	if (classname.find("BP_Grenade_Smoke_C") != std::string::npos)
		return "Smoke";
	if (classname.find("BP_Grenade_Burn_C") != std::string::npos)
		return "Burn";
	/* if (classname.find("BP_Grenade_tun_C") != std::string::npos)
		 return "[ALERT] !Flash Granade";*/
	if (classname.find("BP_Grenade_Shoulei_C") != std::string::npos)
		return "Frag";

	return "tatti";
}


DWORD Data::NetDriver;
DWORD Data::LocalPlayer;
DWORD Data::PlayerController;
DWORD Data::EntityAddress = 0;
vector<AActor> Data::AActorList = {};

vector<BombAlert> Data::BombAlertList = {};
vector<Item> Data::ItemList = {};
vector<impItem> Data::impItemList = {};
vector<Vehicle> Data::VehicleList = {};
//std::vector<Airdrop>  Data::LootData, Data::LootDatadatar = {};
int Data::ElapsedTime;
DWORD Data::GameState;

VOID Data::QueryThread()
{

	DWORD GWorld = 0;
	DWORD GName = 0;

//	GWorld = Tools::ReadMemoryEx<DWORD>(ViewMatrixBase + 114532) + 60;  //here
//	GName = Tools::ReadMemoryEx<DWORD>(ViewMatrixBase - 3218136) + 136;

	GWorld = Tools::ReadMemoryEx<DWORD>(Data::Ue4base + 0x92880F8) + 0x3C;
	GName = Tools::ReadMemoryEx<DWORD>(Data::Ue4base + 0x8F2D424) + 0x88;

	DWORD PersistentLevel = 0;
	DWORD ServerConnection = 0;
	DWORD EntityList = 0;
	INT EntityCount = 0;

	DWORD EntityStruct = 0;
	string EntityType = "";

	DWORD RootComponent = 0;
	INT MyTeamId = 9999;

	DWORD MeshAddv;
	DWORD BodyAddv;
	DWORD BoneAddv;

	string GrenadeType = "";
	string ItemType = "";
	string VehicleType = "";
	string airdroptype = "";
	string deadboxtype = "";
	string wep = "";
	vector<AActor> AActorList = {};


	vector<BombAlert> BombAlertList = {};
	vector<Item> ItemList = {};
	vector<impItem> impItemList = {};
	vector<Vehicle> VehicleList = {};
	std::map<DWORD, int> GrenadesCD;

	while (true)
	{
		if (Game::isUnloaded)
		{
			break;
		}

		g_pEsp->lootbox.clear();
		g_pEsp->airdropi.clear();
		//Sleep(100);

		UWorld = Tools::ReadMemoryEx<DWORD>(GWorld);
		PersistentLevel = Tools::ReadMemoryEx<DWORD>(UWorld + Offset::PersistentLevel);
		NetDriver = Tools::ReadMemoryEx<DWORD>(UWorld + Offset::NetDriver);
		ServerConnection = Tools::ReadMemoryEx<DWORD>(NetDriver + Offset::ServerConnection);
		PlayerController = Tools::ReadMemoryEx<DWORD>(ServerConnection + Offset::PlayerController);
		LocalPlayer = Tools::ReadMemoryEx<DWORD>(PlayerController + Offset::AcknowledgedPawn);
		EntityList = Tools::ReadMemoryEx<DWORD>(PersistentLevel + Offset::EntityList);
		EntityCount = Tools::ReadMemoryEx<INT>(PersistentLevel + Offset::EntityCount);
		ElapsedTime = Tools::ReadMemoryEx<int>(GameState + Offset::ElapsedTime);

		if (EntityCount < 0)
		{
			EntityCount = 0;
		}
		if (EntityCount > 1024)
		{
			EntityCount = 1024;
		}

		for (int i = 0; i < EntityCount; ++i)
		{
			EntityAddress = Tools::ReadMemoryEx<DWORD>(EntityList + i * 4);
			EntityStruct = Tools::ReadMemoryEx<DWORD>(EntityAddress + 0x10);

			EntityType = GetEntityType2(GName, EntityStruct);

			RootComponent = Tools::ReadMemoryEx<DWORD>(EntityAddress + Offset::RootComponent);

			if (IsPlayer(EntityType))
			{
				AActor AActor;
				AActor.TeamId = Tools::ReadMemoryEx<INT>(EntityAddress + Offset::TeamId);
				AActor.Address = EntityAddress;

				if (AActor.Address == LocalPlayer)
				{
					MyTeamId = AActor.TeamId;
					continue;
				}

				if (AActor.TeamId == MyTeamId) continue;

				AActor.Position = Tools::ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);
				AActor.IsDead = Tools::ReadMemoryEx<bool>(EntityAddress + Offset::bDead);
				if (AActor.IsDead) continue;
				AActor.IsBot = Tools::ReadMemoryEx<bool>(EntityAddress + Offset::IsBot);
				if (!AActor.IsBot)
				{
					//AActor.Name = GetPlayerNameUTF(EntityAddress);//raze
					AActor.Name = GetPlayerName(EntityAddress + Offset::Name);

					AActor.Nation = GetPlayerFlag(Tools::ReadMemoryEx<DWORD>(EntityAddress + Offset::Nation));

				}
				else
				{
					AActor.Name = "Bot";
					//AActor.Nation = "";
				}
				if (Setting::plr_wpn)
				{


					wep = PlayerWeapon(GetEntityType3(GName, Tools::ReadMemoryEx<UINT>(Tools::ReadMemoryEx<UINT>(EntityAddress + Offset::CurrentReloadWeapon) + 16)));

					if (wep == "")
					{
						wep = "Fist";
					}

					AActor.weapon = wep;

					std::string sta = getState(Tools::ReadMemoryEx<UINT>(EntityAddress + Offset::CurrentStates));
					if (sta == "")
						sta = "UNKO";
					AActor.stateInt = sta;
				}
				AActor.Health = Tools::ReadMemoryEx<FLOAT>(EntityAddress + Offset::Health);
				AActor.HealthMax = Tools::ReadMemoryEx<FLOAT>(EntityAddress + Offset::HealthMax);
				AActor.Velocity = Tools::ReadMemoryEx<VECTOR3>(Tools::ReadMemoryEx<DWORD>(AActor.Address + Offset::CharacterMovement) + Offset::LastUpdateVelocity);
				if (Setting::Bone || Setting::MagicBullet)
				{
					MeshAddv = Tools::ReadMemoryEx<DWORD>(AActor.Address + Offset::Mesh);
					BodyAddv = MeshAddv + Offset::BodyAddv;
					BoneAddv = Tools::ReadMemoryEx<DWORD>(MeshAddv + Offset::MinLOD) + 48;
					AActor.HeadPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 5 * 48);
				}

				if (Setting::Bone)
				{
					AActor.ChestPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 4 * 48);
					AActor.PelvisPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 1 * 48);
					AActor.lSholderPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 11 * 48);
					AActor.rSholderPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 32 * 48);
					AActor.lElbowPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 12 * 48);
					AActor.rElbowPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 33 * 48);
					AActor.lWristPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 63 * 48);
					AActor.rWristPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 62 * 48);
					AActor.lThighPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 52 * 48);
					AActor.rThighPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 56 * 48);
					AActor.lKneePos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 53 * 48);
					AActor.rKneePos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 57 * 48);
					AActor.lAnklePos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 54 * 48);
					AActor.rAnklePos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 58 * 48);
				}

				AActorList.push_back(AActor);
			}


			if (Setting::Item)
			{
				ItemType = GetItemType(EntityType);
				if (ItemType.find("Unknown") == std::string::npos)
				{
					Item Item;
					Item.Name = ItemType;
					Item.Position = Tools::ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);
					ItemList.emplace_back(Item);
				}
			}

			if (Setting::BombAlert)
			{
				ItemType = GetGrenadeType(EntityType);
				if (ItemType.find(("tatti")) == std::string::npos)
				{
					if (GrenadesCD.find(EntityAddress) == GrenadesCD.end())
					{
						GrenadesCD.insert({ EntityAddress,  ElapsedTime + 7 });
					}
					int CurrentTime = GrenadesCD.at(EntityAddress) - ElapsedTime;
					if (CurrentTime > 0) {

						BombAlert Bomb;
						Bomb.Name = ItemType;
						Bomb.timeLeft = CurrentTime;
						Bomb.Position = Tools::ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);
						BombAlertList.emplace_back(Bomb);
						continue;
					}
				}
			}

			if (Setting::Vehicle)
			{
				VehicleType = GetVehicleType(EntityType);
				if (VehicleType.find("Unknown") == std::string::npos)
				{
					Vehicle Vehicle;
					Vehicle.Name = VehicleType;
					Vehicle.Position = Tools::ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);
					DWORD veh = Tools::ReadMemoryEx<DWORD>(EntityAddress + Offset::VehicleCommon);
					float HP = Tools::ReadMemoryEx<float>(veh + Offset::HP);
					float HPMax = Tools::ReadMemoryEx<float>(veh + Offset::HPMax);
					Vehicle.hp = (int)(HP * 100 / HPMax);
					if (Vehicle.hp < 0 || Vehicle.hp>100) continue;
					float Fuel = Tools::ReadMemoryEx<float>(veh + Offset::Fuel);
					float FuelMax = Tools::ReadMemoryEx<float>(veh + Offset::FuelMax);
					Vehicle.oil = (int)(Fuel * 100 / FuelMax);
					if (Vehicle.oil < 0 && Vehicle.oil>100)continue;


					Vehicle.driving = Tools::ReadMemoryEx<DWORD>(EntityAddress + Offset::bIsEngineStarted);
					VehicleList.push_back(Vehicle);
				}
			}
			if (Setting::airdrop)
			{
				if (AirrDrop(EntityType))
				{
					g_pEsp->airdrp.Position = Tools::ReadMemoryEx<VECTOR3>(Tools::ReadMemoryEx<UINT>(EntityAddress + Offset::RootComponent) + Offset::Position);
					g_pEsp->airdropi.push_back(g_pEsp->airdrp);
					DWORD  count = Tools::ReadMemoryEx<DWORD>(EntityAddress + Offset::boxItemsCount);
					if (count > 30)
						count = 30;
					g_pEsp->airdrp.Aiditem.clear();
					if (count > 0)

					{
						long itemBase = Tools::ReadMemoryEx<DWORD>(EntityAddress + Offset::itemBase);
						long itemAddv;
						for (int t = 0; t < count; t++)
						{
							itemAddv = itemBase + t * 48;
							std::string bitm = GetBoxItems(Tools::ReadMemoryEx<DWORD>(itemAddv + 0x4));
							if (bitm.find("tatti") == std::string::npos)
							{
								Itemb temo;
								bitm.append("  :  ").append(std::to_string(Tools::ReadMemoryEx<DWORD>(itemAddv + 0x18)));
								temo.colorcod = Setting::colorcode;
								temo.Displayname = bitm;
								g_pEsp->airdrp.Aiditem.push_back(temo);
							}
						}
					}


				}

			}
			if (Setting::deadbox)
			{
				if (IsBox(EntityType))
				{
					g_pEsp->lbox.Position = Tools::ReadMemoryEx<VECTOR3>(Tools::ReadMemoryEx<UINT>(EntityAddress + Offset::RootComponent) + Offset::Position);
					g_pEsp->lootbox.push_back(g_pEsp->lbox);
					DWORD  count = Tools::ReadMemoryEx<DWORD>(EntityAddress + Offset::boxItemsCount);
					if (count > 30)
						count = 30;
					g_pEsp->lbox.boxitem.clear();
					if (count > 0)
					{
						long itemBase = Tools::ReadMemoryEx<DWORD>(EntityAddress + Offset::itemBase);
						long itemAddv;
						for (int t = 0; t < count; t++)
						{
							itemAddv = itemBase + t * 48;
							std::string bitm = GetBoxItems(Tools::ReadMemoryEx<DWORD>(itemAddv + 0x4));
							if (bitm.find("tatti") == std::string::npos)
							{
								Itemb temo;
								bitm.append("  :  ").append(std::to_string(Tools::ReadMemoryEx<DWORD>(itemAddv + 0x18)));
								temo.colorcod = Setting::colorcode;
								temo.Displayname = bitm;
								g_pEsp->lbox.boxitem.push_back(temo);
							}
						}
					}
				}

			}
		}

		Data::AActorList.clear();
		Data::ItemList.clear();
		Data::VehicleList.clear();
		Data::AActorList = AActorList;
		Data::BombAlertList = BombAlertList;
		Data::ItemList = ItemList;
		Data::VehicleList = VehicleList;
		g_pEsp->Airdropis = g_pEsp->airdropi;
		g_pEsp->lootboxr = g_pEsp->lootbox;
		AActorList.clear();
		BombAlertList.clear();
		ItemList.clear();
		VehicleList.clear();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	}
}

