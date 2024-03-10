#pragma once
#include "Includes.h"


namespace weapon {


	extern ImVec4 m16;
	extern ImVec4 AKM;
	extern ImVec4 AWM;
	extern ImVec4 AWMimmo;
	extern ImVec4 scarl;
	extern ImVec4 m762;
	extern ImVec4 M24;
	extern ImVec4 GROZZA;
	extern ImVec4 scope8x;
	extern ImVec4 kar98;
	extern ImVec4 Airdrop;
	extern ImVec4 Flare;
	extern ImVec4 Flaregun;
}

namespace Colors {

	extern ImVec4 dp;
	extern ImVec4 mg3;
	extern ImVec4 scope4x;
	extern ImVec4  scope3x;
	extern	ImVec4  bag;
	extern	ImVec4  armer;
	extern	ImVec4  helmat;
	extern	ImVec4  mosin;
	extern ImVec4  aug;
	extern ImVec4  g36;
	extern ImVec4  assm;

	extern	ImVec4  Grandes;
	extern	ImVec4  ammo7;
	extern	ImVec4  ammo5;
	extern ImVec4  madkit;

	/////////////////////////
	extern ImVec4 itemcolors;
	// ARGB playr
	extern	ImVec4  playerline;

	extern	ImVec4  playercorner;
	extern	ImVec4  playerbox;
	extern	ImVec4  lotbox;
	extern	ImVec4  Whait;
	// ARGB
	extern ImVec4  helthbar;
	extern ImVec4  boxColor;
	extern ImVec4  cornerColor;
	extern ImVec4  crosshairColor;
	extern	ImVec4  bot;
	extern	ImVec4  botbone;
	extern	ImVec4  skelec;
	extern	ImVec4  playerbone;
	extern	ImVec4  player;
	extern ImVec4  vehicle;


	//RGB
	extern ImVec4  botcorner;
	extern ImVec4  botline;
	extern	ImVec4 circle;
	extern	ImVec4  enemy;
	extern	ImVec4  botbox;
	extern	ImVec4  bone;
	extern	 ImVec4  fillrect;
	extern	 ImVec4  nam;
	extern	 ImVec4  cWeaponn;
	extern	 ImVec4  nambar;
	extern	 ImVec4  bothealth;
	extern	ImVec4  botname;
	extern	ImVec4  playerhealth;
	extern	ImVec4  textcolor;

	extern	ImVec4 Granades;
	extern	ImVec4 health;
	extern	ImVec4 deadbox;
	extern	ImVec4 deadboxitem;
	extern	ImVec4 airdrop;
	extern	ImVec4 airdropitem;
	extern	ImVec4 scopetextcolor;
	extern	ImVec4  allitem;
	extern	ImVec4  scope6x;
	extern	ImVec4  magicline;
	extern	ImVec4  bgcorner;
	extern	ImVec4  fovcirclecolor;
	extern	ImVec4 M249;
	extern	ImVec4 MK12;
	extern	ImVec4 hpt;
	extern	ImVec4 weapont;
	extern	ImVec4 NearBy;

}
namespace Settings
{
	extern bool ShowMenu;
	extern bool isLogin;	
	extern int Tab;
}
namespace Setting
{
	extern int espTick;
	extern bool Ipadview;
	extern bool knocked;
	extern bool SkipBots;
	extern int EnableKey;
	extern int godviewup;
	extern int godviewdown;
	extern int godviewFr;
	extern int Flycarkey;
	extern int AimbotKey;
	extern int Fastcarkey;

	extern int GodUp;
	extern int GodDown;
	extern int landspeed;
	extern int Backcarkey;
	extern int FastParachutekey;
	extern int fastrunkey;
	extern int PositionKey;
	extern	bool dots;
	extern	bool bg;
	extern int  redioption;
	extern bool  redioption2;
	extern	bool IsMagicInitialize;
	extern FLOAT Aimspeed;
	extern float fovcircleredus;
	extern bool aimbotposition;
	extern bool MagicInsideFOV;
	extern bool AimPrediction;
	extern bool fovcircle;
	extern ImVec4 colorcode;
	extern bool Magntic;
	extern int	curraim;
	extern bool Legitrack;
	extern bool	engine;
	extern bool	skele;
	extern bool MAgicline;
	extern char filename[];
	extern float Normalfontsize;
	extern float fontsize;
	extern float plinesize;
	extern float pfullboxsize;
	extern float pcornersize;
	extern float pbonesize;

	extern float instantPower;
	extern float landPower;
	extern float ipadPower;

	extern float speedCarPower;
	extern float flyCarPower;
	extern float flyManPower;
	extern float fastRunPower;

	extern float blinesize;
	extern float bfullboxsize;
	extern float bcornersize;
	extern float bbonesize;
	extern bool silent;
	extern bool bortext;
	extern bool ShowMenu2;


	extern bool style1;
	extern bool style2;
	extern bool ShowMenu;
	extern bool profree;
	extern	bool botname, bothealth, botline, botfullbox, botblood, botcorner;
	//playr
	extern	bool pline, phealth, pfullbox, pname, pblood, pcorner, deadbox;
	extern bool fightmode;
	extern bool Name;
	extern bool Distance;
	extern bool Distancee;
	extern bool TotalEnemy;
	extern bool Line;
	extern bool Box;
	extern bool botBone;
	extern bool playerBone;
	extern bool  Bone;
	extern bool Health;
	extern bool BombAlert;
	extern bool Item;
	extern bool Vehicle;
	extern bool hp;
	extern bool weapon;
	extern bool feul;


	extern bool impitems;
	extern bool graned;
	extern bool healthitem;
	extern bool scope;
	extern bool allitemss;

	extern bool instanthit;
	extern bool FastParachute;
	extern bool fly;
	extern bool carfly;
	extern bool speedcar;
	extern bool recoil;
	extern bool loofy;
	extern bool MagicX;
	extern bool GodView;
	extern bool fastrun;
	extern bool fastland;
	extern bool ipad;
	extern bool handgun;
	extern bool plr_wpn;
	extern bool luffy;

	extern bool xEffect;

	//pangy
	extern bool sortitem;
	extern bool aimwarning;
	extern bool plan;
	extern bool airdrop;
	extern bool airdropitem;
	extern bool playerdeadbox;
	extern bool itemrect;
	extern bool Bags;
	extern bool Helmat;
	extern bool Armer;

	extern	bool Esp_Item_M249;
	extern	bool Esp_Item_Mk12;

	extern ImVec4 plancolor;
	extern ImVec4 dotss;
	extern bool vahicle_item;
	extern bool Esp_Item_AKM;
	extern float Esp_Item_AKM_Color[4];
	extern float Esp_Item_AKM_TextSize;

	extern bool Esp_Item_M762;
	extern float Esp_Item_M762_Color[4];
	extern float Esp_Item_M762_TextSize;

	extern bool Esp_Item_Mk47Mutant;
	extern float Esp_Item_Mk47Mutant_Color[4];
	extern float Esp_Item_Mk47Mutant_TextSize;

	extern bool Esp_Item_DP28;
	extern float Esp_Item_DP28_Color[4];
	extern float Esp_Item_DP28_TextSize;

	extern bool Esp_Item_SCARL;
	extern float Esp_Item_SCARL_Color[4];
	extern float Esp_Item_SCARL_TextSize;

	extern bool Esp_Item_M416;
	extern float Esp_Item_M416_Color[4];
	extern float Esp_Item_M416_TextSize;

	extern bool Esp_Item_M16A4;
	extern float Esp_Item_M16A4_Color[4];
	extern float Esp_Item_M16A4_TextSize;

	extern bool Esp_Item_G36C;
	extern float Esp_Item_G36C_Color[4];
	extern float Esp_Item_G36C_TextSize;

	extern bool Esp_Item_QBZ;
	extern float Esp_Item_QBZ_Color[4];
	extern float Esp_Item_QBZ_TextSize;

	extern bool Esp_Item_QBU;
	extern float Esp_Item_QBU_Color[4];
	extern float Esp_Item_QBU_TextSize;

	extern bool Esp_Item_SLR;
	extern float Esp_Item_SLR_Color[4];
	extern float Esp_Item_SLR_TextSize;

	extern bool Esp_Item_SKS;
	extern float Esp_Item_SKS_Color[4];
	extern float Esp_Item_SKS_TextSize;

	extern bool Esp_Item_Mini14;
	extern float Esp_Item_Mini14_Color[4];
	extern float Esp_Item_Mini14_TextSize;

	extern bool Esp_Item_M24;
	extern float Esp_Item_M24_Color[4];
	extern float Esp_Item_M24_TextSize;
	extern bool Esp_Item_Awm;
	extern bool Esp_Item_Awmimo;
	extern bool Esp_Item_Kar98k;
	extern float Esp_Item_Kar98k_Color[4];
	extern float Esp_Item_Kar98k_TextSize;

	extern bool Esp_Item_PP19;
	extern float Esp_Item_PP19_Color[4];
	extern float Esp_Item_PP19_TextSize;

	extern bool Esp_Item_TommyGun;
	extern float Esp_Item_TommyGun_Color[4];
	extern float Esp_Item_TommyGun_TextSize;

	extern bool Esp_Item_MP5K;
	extern float Esp_Item_MP5K_Color[4];
	extern float Esp_Item_MP5K_TextSize;

	extern bool Esp_Item_UMP9;
	extern float Esp_Item_UMP9_Color[4];
	extern float Esp_Item_UMP9_TextSize;

	extern bool Esp_Item_Vector;
	extern float Esp_Item_Vector_Color[4];
	extern float Esp_Item_Vector_TextSize;

	extern bool Esp_Item_Uzi;
	extern float Esp_Item_Uzi_Color[4];
	extern float Esp_Item_Uzi_TextSize;

	extern bool Esp_Item_762mm;
	extern float Esp_Item_762mm_Color[4];
	extern float Esp_Item_762mm_TextSize;

	extern bool Esp_Item_556mm;
	extern float Esp_Item_556mm_Color[4];
	extern float Esp_Item_556mm_TextSize;

	extern bool Esp_Item_9mm;
	extern float Esp_Item_9mm_Color[4];
	extern float Esp_Item_9mm_TextSize;

	extern bool Esp_Item_45ACP;
	extern float Esp_Item_45ACP_Color[4];
	extern float Esp_Item_45ACP_TextSize;

	extern bool Esp_Item_Holo;
	extern float Esp_Item_Holo_Color[4];
	extern float Esp_Item_Holo_TextSize;

	extern bool Esp_Item_x2;
	extern float Esp_Item_x2_Color[4];
	extern float Esp_Item_x2_TextSize;

	extern bool Esp_Item_x3;
	extern float Esp_Item_x3_Color[4];
	extern float Esp_Item_x3_TextSize;

	extern bool Esp_Item_x4;
	extern float Esp_Item_x4_Color[4];
	extern float Esp_Item_x4_TextSize;

	extern bool Esp_Item_x6;
	extern float Esp_Item_x6_Color[4];
	extern float Esp_Item_x6_TextSize;

	extern bool Esp_Item_x8;
	extern float Esp_Item_x8_Color[4];
	extern float Esp_Item_x8_TextSize;

	extern bool Esp_Item_Bag1;
	extern float Esp_Item_Bag1_Color[4];
	extern float Esp_Item_Bag1_TextSize;

	extern bool Esp_Item_Bag2;
	extern float Esp_Item_Bag2_Color[4];
	extern float Esp_Item_Bag2_TextSize;

	extern bool Esp_Item_Bag3;
	extern float Esp_Item_Bag3_Color[4];
	extern float Esp_Item_Bag3_TextSize;

	extern bool Esp_Item_Armor1;
	extern float Esp_Item_Armor1_Color[4];
	extern float Esp_Item_Armor1_TextSize;

	extern bool Esp_Item_Armor2;
	extern float Esp_Item_Armor2_Color[4];
	extern float Esp_Item_Armor2_TextSize;

	extern bool Esp_Item_Armor3;
	extern float Esp_Item_Armor3_Color[4];
	extern float Esp_Item_Armor3_TextSize;

	extern bool Esp_Item_Helmet1;
	extern float Esp_Item_Helmet1_Color[4];
	extern float Esp_Item_Helmet1_TextSize;

	extern bool Esp_Item_Helmet2;
	extern float Esp_Item_Helmet2_Color[4];
	extern float Esp_Item_Helmet2_TextSize;

	extern bool Esp_Item_Helmet3;
	extern float Esp_Item_Helmet3_Color[4];
	extern float Esp_Item_Helmet3_TextSize;

	extern bool Esp_Item_Frag;
	extern float Esp_Item_Frag_Color[4];
	extern float Esp_Item_Frag_TextSize;

	extern bool Esp_Item_Smoke;
	extern float Esp_Item_Smoke_Color[4];
	extern float Esp_Item_Smoke_TextSize;

	extern bool Esp_Item_Molotof;
	extern float Esp_Item_Molotof_Color[4];
	extern float Esp_Item_Molotof_TextSize;

	extern bool Esp_Item_MedKit;
	extern float Esp_Item_MedKit_Color[4];
	extern float Esp_Item_MedKit_TextSize;

	extern bool Esp_Item_FirstAidKit;
	extern float Esp_Item_FirstAidKit_Color[4];
	extern float Esp_Item_FirstAidKit_TextSize;

	extern bool Esp_Item_Painkiller;
	extern float Esp_Item_Painkiller_Color[4];
	extern float Esp_Item_Painkiller_TextSize;

	extern bool Esp_Item_EnergyDrink;
	extern float Esp_Item_EnergyDrink_Color[4];
	extern float Esp_Item_EnergyDrink_TextSize;

	extern bool Esp_Item_AdrenalineSyringe;
	extern float Esp_Item_AdrenalineSyringe_Color[4];
	extern float Esp_Item_AdrenalineSyringe_TextSize;

	extern bool Esp_Item_FlareGun;
	extern float Esp_Item_FlareGun_Color[4];
	extern float Esp_Item_FlareGun_TextSize;

	extern bool Esp_Item_Flare;
	extern float Esp_Item_Flare_Color[4];
	extern float Esp_Item_Flare_TextSize;

	extern bool Esp_Item_AirDrop;
	extern float Esp_Item_AirDrop_Color[4];
	extern float Esp_Item_AirDrop_TextSize;

	extern bool Aimbot;

	extern bool MagicBullet;
	extern bool spinbot;
	extern bool debugmenu;
	extern bool borderlo;

	extern bool Brutall;

	extern bool CameraCatch;
	extern bool BGMI;
	extern bool grw;
	extern bool molow;
	extern int	magicv;
	//extern int	flycarv;
	//extern int	instantv;
	extern int	carsv;
	extern int	fastrv;
	extern bool magicb;
	extern int	LibUe4;
}