#pragma once 
#include "Includes.h"
#include "Algorithm.h"
struct AActor
{
	bool IsBot;
	VECTOR3 Position;
	FLOAT Health;
	FLOAT IsDead;
	FLOAT HealthMax;
	std::string Name;

	string weapon, stateInt;
	string Nation;
	INT TeamId;
	DWORD Address;
	VECTOR3 Velocity;
	FLOAT PlayerDead;
	VECTOR3 HeadPos;
	VECTOR3 ChestPos;
	VECTOR3 PelvisPos;
	VECTOR3 lSholderPos;
	VECTOR3 rSholderPos;
	VECTOR3 lElbowPos;
	VECTOR3 rElbowPos;
	VECTOR3 lWristPos;
	VECTOR3 rWristPos;
	VECTOR3 lThighPos;
	VECTOR3 rThighPos;
	VECTOR3 lKneePos;
	VECTOR3 rKneePos;
	VECTOR3 lAnklePos;
	VECTOR3 rAnklePos;
};

struct BombAlert
{
	string Name;
	VECTOR3 Position;
	int timeLeft;
};

struct Item
{
	string Name;
	VECTOR3 Position;
};
struct IsBotLists
{
	string Name;
	VECTOR3 Position;
};
struct impItem
{
	string Name;
	VECTOR3 Position;
};
struct Vehicle
{
	float oil;
	float hp;
	string Name;
	VECTOR3 Position;
	bool driving;
};

struct Itemb {
	std::string Displayname;
	ImVec4 colorcod;

};
struct Airdrop
{
	string Name;
	VECTOR3 Position;
	std::vector<Itemb> Aiditem;
};
struct Deadbox
{
	int picid;
	std::vector<Itemb> boxitem;
	string Name;
	VECTOR3 Position;
};


class Espp {
public:
	std::vector<Airdrop> airdropi, Airdropis;
	Airdrop airdrp;

	std::vector<Deadbox> lootbox, lootboxr;
	Deadbox lbox;
	VECTOR3 mypos;
};
extern Espp* g_pEsp;

namespace Data
{
	extern DWORD GameState;
	extern int ElapsedTime;

	extern DWORD Ue4base;
	extern DWORD ViewMatrixBase;
	extern DWORD UWorld;
	extern DWORD NetDriver;
	extern DWORD LocalPlayer;
	extern DWORD PlayerController;
	extern DWORD EntityAddress;
	extern vector<AActor> AActorList;
	extern vector<BombAlert> BombAlertList;
	extern vector<Item> ItemList;
	extern vector<Vehicle> VehicleList;
	extern vector<impItem> impItemList;
	extern vector<IsBotLists> IsBotList;
	DWORD GetViewMatrixBase(DWORD StartAddress, DWORD EndAddress);
	DWORD GetUe4Base(DWORD StartAddress, DWORD EndAddress);
	VOID QueryThread();

	extern D3DMATRIX viewMatrix;
};
