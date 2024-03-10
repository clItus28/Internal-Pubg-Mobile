#include "Memory.h"

#include "Algorithm.h"
#include "Data.h"
#include "Offsets.h"
#include "Aimbot.h"
BYTE MagicBulletShell[60] =
{
0xC7, 0x45, 0x78, 0x00, 0x00, 0x00, 0x00,                        // mov[ebp + 78],00000000 
0x83, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x01,                        // cmp dword ptr[00000000],01 
0x74, 0x0E,                                                      // je 0000001E
0x60,                                                            // pushad
0x8B, 0x5D, 0x50,                                                // mov ebx,[ebp + 50]
0x8B, 0x53, 0x18,                                                // mov edx,[ebx + 18]
0x8A, 0x02,                                                      // mov al,[edx]
0x3C, 0x2C,                                                      // cmp al,00        //Need Update
0x74, 0x02,                                                      // je 0000001F
0x61,                                                            // popad
0xC3,                                                            // ret
0x8A, 0x42, 0x01,                                                // mov al,[edx + 01]
0x3C, 0x7E,                                                      // cmp al,00        //Need Update
0x75, 0x14,                                                      // jne 0000003A
0xC7, 0x83, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // mov[ebx + 00000270],00000000 
0xC7, 0x83, 0x84, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       // mov[ebx + 00000274],00000000 
0xEB, 0xE1
};


//BYTE MagicBulletSearch1[] = { 0x66, 0x0F, 0x7E, '?', 0x28, 0x02, 0x00, 0x00, 0xC7, 0x45, 0x78 };// Need update 
BYTE MagicBulletSearch1[] = { 0x66, 0x0F, 0x7E, '?', 0x88, 0x02, 0x00, 0x00, 0xC7, 0x45, 0x78, 0x48 }; // Need update
BYTE MagicBulletSearch2[] = { 0x66, 0x0F, 0x7E, '?', 0x88, 0x02, 0x00, 0x00, 0xC7, 0x45, 0x78, 0x48 }; // Need update

DWORD MagicBulletAddress = 0;
vector<DWORD_PTR> MagicBulletList = {};
INT MagicBulletHook = 0;
BYTE RealByteCode[7];
DWORD FlyCarAddress = 0;
VOID GetMagicAddress()
{
	std::vector<DWORD_PTR> FoundedBase;


	Tools::MemSearch(MagicBulletSearch1, sizeof(MagicBulletSearch1), 0x0D000000, 0x10000000, 0, 0, FoundedBase);


	for (int i = 0; i < FoundedBase.size(); i++)
	{

		if (Tools::ReadMemoryEx<BYTE>(FoundedBase[i] + 0xC) == 0x86) // Need update  
		{
			MagicBulletList.push_back(FoundedBase[i]);
			MagicBulletAddress = FoundedBase[i];
		}
	}



	FoundedBase.clear();
}




VOID InitializeMagic()
{
	INT Addv = MagicBulletAddress;

	MagicBulletHook = (INT)VirtualAllocEx(Tools::GameProcess, 0, 500, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(Tools::GameProcess, (LPVOID)MagicBulletHook, &MagicBulletShell, sizeof(MagicBulletShell), 0);


	Tools::WriteMemoryEx<BYTE>(MagicBulletHook + 0x13, 0x50);


	Tools::WriteMemoryEx<INT>(MagicBulletHook + 9, MagicBulletHook + 0x5E);
	ReadProcessMemory(Tools::GameProcess, (LPCVOID)(Addv + 0x8), &RealByteCode, sizeof(RealByteCode), 0);
	WriteProcessMemory(Tools::GameProcess, (LPVOID)(MagicBulletHook), &RealByteCode, sizeof(RealByteCode), 0);
}

VOID HookCall(INT Address, INT HookAdress)
{
	BYTE Shell[7] = { 0xE8, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90 };
	*(INT*)(Shell + 1) = (INT)(HookAdress - Address - 5);
	WriteProcessMemory(Tools::GameProcess, (LPVOID)Address, &Shell, sizeof(Shell), 0);
}

bool IsEqual(BYTE Array1[], BYTE Array2[])
{
	for (int i = 0; i < 6; i++)
	{
		if (Array1[i] != Array2[i])
		{
			return false;
		}
	}

	return true;
}

bool Hooked(int Address)
{
	unsigned char Tmp[7];
	ReadProcessMemory(Tools::GameProcess, (LPCVOID)(Address + 0x8), &Tmp, sizeof(Tmp), 0);

	if ((Tmp[0] == 0xE8 && Tmp[5] == 0x90 && Tmp[6] == 0x90))
	{
		return true;
	}

	return false;
}


VOID HookMagic()
{
	for (DWORD_PTR& Addv : MagicBulletList)
	{
		BYTE Tmp[7];
		ReadProcessMemory(Tools::GameProcess, (LPCVOID)((int)Addv + 0x8), &Tmp, sizeof(Tmp), 0);

		if (IsEqual(Tmp, RealByteCode))
		{
			HookCall((INT)(Addv + 0x8), (INT)MagicBulletHook);
		}
	}
}

VOID Memory::RestoreHook()
{
	for (DWORD_PTR& Addv : MagicBulletList)
	{
		if (Hooked(Addv))
		{
			WriteProcessMemory(Tools::GameProcess, (LPVOID)(Addv + 0x8), &RealByteCode, sizeof(RealByteCode), 0);
		}
	}
}

VECTOR3 Subtract(VECTOR3 Src, VECTOR3 Dst)
{
	VECTOR3 Result;
	Result.X = Src.X - Dst.X;
	Result.Y = Src.Y - Dst.Y;
	Result.Z = Src.Z - Dst.Z;

	return Result;
}

float Magnitude(VECTOR3 Vec)
{
	return sqrtf(Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z);
}

float GetDistance(VECTOR3 Src, VECTOR3 Dst)
{
	VECTOR3 Result = Subtract(Src, Dst);
	return Magnitude(Result);
}

VECTOR3 NormalizeVec(VECTOR3 Vector)
{
	float Length = Magnitude(Vector);

	Vector.X /= Length;
	Vector.Y /= Length;
	Vector.Z /= Length;

	return Vector;
}
float Distance(VECTOR3 myPos, VECTOR3 enPos)
{
	return sqrt((myPos.X - enPos.X) * (myPos.X - enPos.X) + (myPos.Y - enPos.Y) * (myPos.Y - enPos.Y) + (myPos.Z - enPos.Z) * (myPos.Z - enPos.Z));
}
float BulletDrop(float TravelTime)
{
	return (TravelTime * TravelTime * 980 / 2);
}

//bool Fov(float OverlayScreenWidth, float OverlayScreenHeight, VECTOR2 PlayerW2SBone, float FovRadius)
//{
//	VECTOR2 Cenpoint;
//	Cenpoint.X = PlayerW2SBone.X - (OverlayScreenWidth / 2);
//	Cenpoint.Y = PlayerW2SBone.Y - (OverlayScreenHeight / 2);
//
//	if (Cenpoint.X * Cenpoint.X + Cenpoint.Y * Cenpoint.Y <= FovRadius * FovRadius)
//	{
//		return true;
//	}
//
//
//	return false;
//}

bool InsideFov(float OverlayScreenWidth, float OverlayScreenHeight, VECTOR2 PlayerW2SBone, float FovRadius)
{
	VECTOR2 Cenpoint;
	Cenpoint.X = PlayerW2SBone.X - (OverlayScreenWidth / 2);
	Cenpoint.Y = PlayerW2SBone.Y - (OverlayScreenHeight / 2);

	if (Cenpoint.X * Cenpoint.X + Cenpoint.Y * Cenpoint.Y <= FovRadius * FovRadius)
	{
		return true;
	}


	return false;
}

VECTOR3 GetPrediction(VECTOR3 TargetPos, float Distance, VECTOR3 TargetVelocity, float ProjectileSpeed, float m_gravity) {

	//float BaseFlyTime = Distance / BulletSpeed;
	//	float SecFlyTime = BaseFlyTime * AddTime;

	float temp = (0.2 * Distance / ProjectileSpeed) + 1.5;
	float flyTimee = Distance / ProjectileSpeed;
	float	flyTime = flyTimee * temp;
	TargetPos.X = TargetPos.X + TargetVelocity.X * flyTime;
	TargetPos.Y = TargetPos.Y + TargetVelocity.Y * flyTime;
	TargetPos.Z = TargetPos.Z + TargetVelocity.Z + 0.5 * m_gravity * pow(flyTime, 2) * ((Distance * 45 / 25) / 2) / 10;
	return TargetPos;
}




VECTOR2 GetAimPrediction()
{
	VECTOR2 Coordinate;
	Coordinate.X = 0;
	Coordinate.Y = 0;
	VECTOR3 HeadPos;
	HeadPos.X = 0;
	HeadPos.Y = 0;
	HeadPos.Z = 0;
	VECTOR2 Screen;
	Screen.X = 0;
	Screen.Y = 0;
	VECTOR3 Velocity;
	Velocity.X = 0;
	Velocity.Y = 0;
	Velocity.Z = 0;
	FLOAT TargetDistance = 9999.0f;
	FLOAT CrossDist = 0;
	INT Distance4 = 0;
	VECTOR3 posi;
	FLOAT xDif;
	FLOAT yDif;
	FLOAT zDif;


	for (AActor& AActor : Data::AActorList)
	{
		if (Setting::knocked == true && AActor.Health <= 0 && AActor.IsDead == false)continue;
		if (Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.ChestPos, Screen, &Distance4))
		{

			if (Setting::MagicInsideFOV)
			{
				if (InsideFov(DX11Window::Width, DX11Window::Height, Screen, Setting::fovcircleredus/*FovRadius*/))
				{

					CrossDist = sqrt(pow(Screen.X - DX11Window::Width / 2, 2) + pow(Screen.Y - DX11Window::Height / 2, 2));

					if (CrossDist < TargetDistance)
					{
						if (Setting::curraim == 0)
						{
							HeadPos = AActor.HeadPos;
							//HeadPos.Z += 1.50f;
							HeadPos.Z += 18;// && Setting::magicv;
						}
						if (Setting::curraim == 1)
						{
							HeadPos = AActor.ChestPos;
						}
						if (Setting::curraim == 2)
						{
							HeadPos = AActor.PelvisPos;
						}

						TargetDistance = CrossDist;
						Velocity = AActor.Velocity;
					}

				}


			}
			else
			{


				CrossDist = sqrt(pow(Screen.X - DX11Window::Width / 2, 2) + pow(Screen.Y - DX11Window::Height / 2, 2));

				if (CrossDist < TargetDistance)
				{
					if (Setting::curraim == 0)
					{
						HeadPos = AActor.HeadPos;
						//HeadPos.Z += 0.50f;
						HeadPos.Z += 18; //&& Setting::magicv;
					}
					if (Setting::curraim == 1)
					{
						HeadPos = AActor.ChestPos;
					}
					if (Setting::curraim == 2)
					{
						HeadPos = AActor.PelvisPos;
					}

					TargetDistance = CrossDist;
					Velocity = AActor.Velocity;
				}

			}

		}
	}
	if (HeadPos.X == 0.0f && HeadPos.Y == 0.0f && HeadPos.Z == 0.0f)
	{
		Screen.X = -999.0f;
		Screen.Y = -999.0f;
		return Screen;
	}
	if (Setting::MagicInsideFOV)
	{

		if (!Algorithm::WorldToScreenBone(Data::viewMatrix, HeadPos, Screen, &Distance4))
		{
			Screen.X = -999.0f;
			Screen.Y = -999.0f;
			return Screen;

		}
		if (!InsideFov(DX11Window::Width, DX11Window::Height, Screen, Setting::fovcircleredus/*FovRadius*/))
		{
			Screen.X = -999.0f;
			Screen.Y = -999.0f;
			return Screen;
		}
	}



	DWORD tmpAddv = Tools::ReadMemoryEx<INT>(Data::LocalPlayer + Offset::Mesh);
	DWORD bodyAddv = tmpAddv + Offset::BodyAddv;
	DWORD boneAddv = Tools::ReadMemoryEx<INT>(tmpAddv + Offset::MinLOD) + 48;

	VECTOR3 MyPosition = Algorithm::GetBoneWorldPosition(bodyAddv, boneAddv + 5 * 48);


	DWORD CurrentReloadWeapon = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::CurrentReloadWeapon);
	DWORD ShootWeaponEntity = Tools::ReadMemoryEx<DWORD>(CurrentReloadWeapon + Offset::ShootWeaponEntity);
	float BulletSpeed = Tools::ReadMemoryEx<FLOAT>(ShootWeaponEntity + Offset::BulletFireSpeed) / 100.0f;
	float Distancee = Distance(MyPosition, HeadPos) / 100;
	VECTOR3 mY_wp_pos = Tools::ReadMemoryEx<VECTOR3>(Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::CurrentReloadWeapon) + Offset::RootComponent) + Offset::Position);
	float Gravity = 5.72f;
	VECTOR3 enemyPos = GetPrediction(HeadPos, Distancee, Velocity, BulletSpeed, Gravity);
	//VECTOR3 enemyPos = Predict(HeadPos, MyPosition, Velocity, BulletSpeed);

	/*xDif = enemyPos.X - g_pEsp->mypos.X;
	yDif = enemyPos.Y - g_pEsp->mypos.Y;
	zDif = enemyPos.Z - g_pEsp->mypos.Z;


	float Hyp = sqrt(xDif * xDif + yDif * yDif);
	Coordinate.X = atan2(zDif, Hyp) * 180.0f / 3.1415926535897f;
	Coordinate.Y = atan2(yDif, xDif) * 180.0f / 3.1415926535897f;*/


	xDif = enemyPos.X - MyPosition.X;
	yDif = enemyPos.Y - MyPosition.Y;
	zDif = enemyPos.Z - MyPosition.Z;

	float Hyp = sqrt(xDif * xDif + yDif * yDif);
	Coordinate.X = atan2(zDif, Hyp) * 180.0f / 3.1415926535897f;
	Coordinate.Y = atan2(yDif, xDif) * 180.0f / 3.1415926535897f;

	return Coordinate;

}

VECTOR2 GetMagicCoordinates()
{
	if (Data::AActorList.size() > 0)
	{
		VECTOR2 Coordinate;
		Coordinate.X = 0;
		Coordinate.Y = 0;
		VECTOR3 HeadPos;
		HeadPos.X = 0;
		HeadPos.Y = 0;
		HeadPos.Z = 0;
		VECTOR2 Screen;
		Screen.X = 0;
		Screen.Y = 0;
		VECTOR3 Velocity;
		Velocity.X = 0;
		Velocity.Y = 0;
		Velocity.Z = 0;
		FLOAT TargetDistance = 9999.0f;
		FLOAT CrossDist = 0;
		INT Distance4 = 0;
		VECTOR3 posi;


		for (AActor& AActor : Data::AActorList)
		{
			if (AActor.Health > 0 && !AActor.PlayerDead) //Alive
			{
				if (Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.ChestPos, Screen, &Distance4))
				{
					if (Setting::fovcircle)
					{
						//if (Aimbot::InsideFov(DX11Window::Width, DX11Window::Height, Screen, Setting::fovcircleredus/*FovRadius*/))
						{
							HookMagic();
							CrossDist = sqrt(pow(Screen.X - DX11Window::Width / 2, 2) + pow(Screen.Y - DX11Window::Height / 2, 2));
							if (CrossDist < TargetDistance)
							{
								if (Setting::curraim == 0)
								{
									HeadPos = AActor.HeadPos;
									HeadPos.Z += 18; //&& Setting::magicv;
								}
								if (Setting::curraim == 1)
								{
									HeadPos = AActor.ChestPos;
									HeadPos.Z += 3;
								}
								if (Setting::curraim == 2)
								{
									HeadPos = AActor.PelvisPos;
									HeadPos.Z += 1;
								}

								TargetDistance = CrossDist;
								Velocity = AActor.Velocity;
							}

						}
						//else
						//{
						//	Memory::RestoreHook();
						//	MagicBulletList.clear();
						//	VirtualFreeEx(Tools::GameProcess, (LPVOID)MagicBulletHook, 0, MEM_RELEASE);
						//	MagicBulletAddress = 0;
						//	MagicBulletHook = 0;
						//	ZeroMemory(RealByteCode, sizeof(RealByteCode));

						//	//MagicRested = true;
						//	Memory::IsMagicInitialized = false;

						//}
					}
					else /// feen ? 
					{
						HookMagic();
						if (Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.ChestPos, Screen, &Distance4))
						{

							CrossDist = sqrt(pow(Screen.X - DX11Window::Width / 2, 2) + pow(Screen.Y - DX11Window::Height / 2, 2));

							if (CrossDist < TargetDistance)
							{
								if (Setting::curraim == 0)
								{
									HeadPos = AActor.HeadPos;
									HeadPos.Z += 18; //&& Setting::magicv;
								}
								if (Setting::curraim == 1)
								{
									HeadPos = AActor.ChestPos;
									HeadPos.Z += 3;
								}
								if (Setting::curraim == 2)
								{
									HeadPos = AActor.PelvisPos;
									HeadPos.Z += 1;
								}

								TargetDistance = CrossDist;
								Velocity = AActor.Velocity;
							}
						}
					}


				}
			}
			if (AActor.Health <= 0 && !AActor.PlayerDead)
			{
				if (Setting::knocked)/////
				{
					if (Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.ChestPos, Screen, &Distance4))
					{

						if (Setting::fovcircle)
						{
							//if (Aimbot::InsideFov(DX11Window::Width, DX11Window::Height, Screen, Setting::fovcircleredus/*FovRadius*/))
							{
								HookMagic();

								CrossDist = sqrt(pow(Screen.X - DX11Window::Width / 2, 2) + pow(Screen.Y - DX11Window::Height / 2, 2));
								if (CrossDist < TargetDistance)
								{
									if (Setting::curraim == 0)
									{
										HeadPos = AActor.HeadPos;
										HeadPos.Z += 7 && Setting::magicv;
									}
									if (Setting::curraim == 1)
									{
										HeadPos = AActor.ChestPos;
										HeadPos.Z += 3;
									}
									if (Setting::curraim == 2)
									{
										HeadPos = AActor.PelvisPos;
										HeadPos.Z += 1;
									}

									TargetDistance = CrossDist;
									Velocity = AActor.Velocity;
								}

							}

						}
						else
						{
							HookMagic();
							if (Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.ChestPos, Screen, &Distance4))
							{

								CrossDist = sqrt(pow(Screen.X - DX11Window::Width / 2, 2) + pow(Screen.Y - DX11Window::Height / 2, 2));

								if (CrossDist < TargetDistance)
								{
									if (Setting::curraim == 0)
									{
										HeadPos = AActor.HeadPos;
										HeadPos.Z += 7 && Setting::magicv;
									}
									if (Setting::curraim == 1)
									{
										HeadPos = AActor.ChestPos;
										HeadPos.Z += 3;
									}
									if (Setting::curraim == 2)
									{
										HeadPos = AActor.PelvisPos;
										HeadPos.Z += 1;
									}

									TargetDistance = CrossDist;
									Velocity = AActor.Velocity;
								}
							}
						}

					}
				}


			}
			if (AActor.Health <= 0 && AActor.PlayerDead)
			{
				//Memory::RestoreHook();
				//MagicBulletList.clear();
				//VirtualFreeEx(Tools::GameProcess, (LPVOID)MagicBulletHook, 0, MEM_RELEASE);
				//MagicBulletAddress = 0;
				//MagicBulletHook = 0;
				//ZeroMemory(RealByteCode, sizeof(RealByteCode));

				////MagicRested = true;
				//Memory::IsMagicInitialized = false;
			}
		}

		DWORD MeshAddv = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Mesh);
		DWORD BodyAddv = MeshAddv + Offset::BodyAddv;
		DWORD BoneAddv = Tools::ReadMemoryEx<DWORD>(MeshAddv + Offset::MinLOD) + 48;
		VECTOR3 MyPosition = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 5 * 48);

		float AddTime = 30 / 10.0f + 1.0f;
		float Gravity = 5.72f;
		float distance = GetDistance(MyPosition, HeadPos) / 100.0f;
		float zAssist;
		if (distance < 5000.f)
			zAssist = 1.8f;
		else if (distance < 10000.f)
			zAssist = 1.72f;
		else if (distance < 15000.f)
			zAssist = 1.23f;
		else if (distance < 20000.f)
			zAssist = 1.24f;
		else if (distance < 25000.f)
			zAssist = 1.25f;
		else if (distance < 30000.f)
			zAssist = 1.26f;
		else if (distance < 35000.f)
			zAssist = 1.27f;
		else if (distance < 50000.f)
			zAssist = 1.28f;
		else if (distance < 45000.f)
			zAssist = 1.29f;
		else if (distance < 50000.f)
			zAssist = 1.30f;


		DWORD CurrentReloadWeapon = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::CurrentReloadWeapon);
		DWORD ShootWeaponEntity = Tools::ReadMemoryEx<DWORD>(CurrentReloadWeapon + Offset::ShootWeaponEntity);
		float BulletSpeed = Tools::ReadMemoryEx<FLOAT>(ShootWeaponEntity + Offset::BulletFireSpeed);
		float BulletTravelTime = distance / Offset::BulletFireSpeed;
		//DWORD SceneComponent = Tools::ReadMemoryEx<INT>(Offset::RootComponent + 0x14C);
		//DWORD VehicleCommon = Tools::ReadMemoryEx<INT>(Offset::VehicleCommon + 0x6dc);


		HeadPos.X += Velocity.X * BulletTravelTime;
		HeadPos.Y += Velocity.Y * BulletTravelTime;
		HeadPos.Z += Velocity.Z * BulletTravelTime * zAssist + 50.5f * 5.72f * BulletTravelTime * BulletTravelTime;


		FLOAT xDif = HeadPos.X - MyPosition.X;
		FLOAT yDif = HeadPos.Y - MyPosition.Y;
		FLOAT zDif = HeadPos.Z - MyPosition.Z;

		float Hyp = sqrt(xDif * xDif + yDif * yDif);
		Coordinate.X = atan2(zDif, Hyp) * 180.0f / 3.1415926535897f;
		Coordinate.Y = atan2(yDif, xDif) * 180.0f / 3.1415926535897f;

		return Coordinate;
	}
	else
	{
		//Memory::RestoreHook();
		//MagicBulletList.clear();
		//VirtualFreeEx(Tools::GameProcess, (LPVOID)MagicBulletHook, 0, MEM_RELEASE);
		//MagicBulletAddress = 0;
		//MagicBulletHook = 0;
		//ZeroMemory(RealByteCode, sizeof(RealByteCode));

		////MagicRested = true;
		//Memory::IsMagicInitialized = false;
	}

}

VECTOR3 GetMagicRunningCoordinatesVip()
{
	VECTOR3 Coordinate;
	Coordinate.X = 0;
	Coordinate.Y = 0;
	VECTOR3 HeadPos;
	HeadPos.X = 0;
	HeadPos.Y = 0;
	HeadPos.Z = 0;
	VECTOR2 Screen;
	Screen.X = 0;
	Screen.Y = 0;
	VECTOR3 Velocity;
	Velocity.X = 0;
	Velocity.Y = 0;
	Velocity.Z = 0;
	FLOAT TargetDistance = 9999.0f;
	FLOAT CrossDist = 0;
	INT Distance4 = 0;
	VECTOR3 posi;
	//bool isEnemyInsideFOV = false;
	/**/
	for (AActor& AActor : Data::AActorList)
	{
		/*if (Screen.Z < 0.001f || Distance < 10)
			continue;*/
		if (Setting::knocked == true && AActor.Health < 0)
		{
			continue;
		}
		if (Setting::SkipBots == true && AActor.IsBot == true)
		{
			continue;
		}
		if (Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.ChestPos, Screen, &Distance4))
		{
			if (Setting::fovcircle)
			{
				//if (Aimbot::InsideFov(DX11Window::Width, DX11Window::Height, Screen, Setting::fovcircleredus/*FovRadius*/))
				{
					//no will fix your prop
					HookMagic();
					CrossDist = sqrt(pow(Screen.X - DX11Window::Width / 2, 2) + pow(Screen.Y - DX11Window::Height / 2, 2));
					if (CrossDist < TargetDistance)
					{
						if (Setting::curraim == 0)
						{
							HeadPos = AActor.HeadPos;
							HeadPos.Z += 7;
						}
						if (Setting::curraim == 1)
						{
							HeadPos = AActor.ChestPos;
						}
						if (Setting::curraim == 2)
						{
							HeadPos = AActor.PelvisPos;
						}
						if (Setting::curraim == 3)
						{
							HeadPos = AActor.rAnklePos;
						}
						//if (Setting::knocked)
						//{
						//	if (AActor.Health <= 0)
						//	{
						//		Memory::RestoreHook();
						//		continue;
						//	}
						//}
						//if (Setting::SkipBots)
						//{
						//	if (AActor.IsBot)
						//	{
						//		Memory::RestoreHook();
						//		continue;
						//	}
						//}
						TargetDistance = CrossDist;
						Velocity = AActor.Velocity;
					}

				}

			}
			else
			{
				HookMagic();
				if (Setting::knocked == true && AActor.Health < 0)
				{
					continue;
				}
				if (Setting::SkipBots == true && AActor.IsBot == true)
				{
					continue;
				}
				if (Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.ChestPos, Screen, &Distance4))
				{
					CrossDist = sqrt(pow(Screen.X - DX11Window::Width / 2, 2) + pow(Screen.Y - DX11Window::Height / 2, 2));

					if (CrossDist < TargetDistance)
					{
						if (Setting::curraim == 0)
						{
							HeadPos = AActor.HeadPos;
							HeadPos.Z += 14;
						}
						if (Setting::curraim == 1)
						{
							HeadPos = AActor.ChestPos;
						}
						if (Setting::curraim == 2)
						{
							HeadPos = AActor.PelvisPos;
						}
						if (Setting::curraim == 3)
						{
							HeadPos = AActor.rAnklePos;
						}
						/*if (Setting::knocked)
						{
							if (AActor.Health <= 0)
							{
								Memory::RestoreHook();
								continue;
							}
						}
						if (Setting::SkipBots)
						{
							if (AActor.IsBot)
							{
								Memory::RestoreHook();
								continue;
							}
						}*/
						TargetDistance = CrossDist;
						Velocity = AActor.Velocity;
					}
				}
			}

			if (Setting::fovcircle)
			{
				if (!Algorithm::WorldToScreenBone(Data::viewMatrix, HeadPos, Screen, &Distance4))
				{
					Memory::RestoreHook();
					continue;

				}
				if (!Aimbot::InsideFov(DX11Window::Width, DX11Window::Height, Screen, Setting::fovcircleredus/*FovRadius*/))
				{
					Memory::RestoreHook();
					continue;
				}
			}
		}
	}

	DWORD MeshAddv = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Mesh);
	DWORD BodyAddv = MeshAddv + Offset::BodyAddv;
	DWORD BoneAddv = Tools::ReadMemoryEx<DWORD>(MeshAddv + Offset::MinLOD) + 48;

	VECTOR3 MyPosition = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 5 * 48);
	//float Gravity = 5.24f;
	//float AddTime = 30 / 10.0f + 1.0f;
	//float Distance = GetDistance(MyPosition, HeadPos) / 100.0f;
	//float temp = 1.23f;
	//DWORD CurrentReloadWeapon = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + 0x21fc);
	//DWORD ShootWeaponEntity = Tools::ReadMemoryEx<DWORD>(CurrentReloadWeapon + Offset::ShootWeaponEntity);
	//float BulletSpeed = Tools::ReadMemoryEx<FLOAT>(ShootWeaponEntity + Offset::BulletFireSpeed) / 650.f;
	////DWORD SceneComponent = Tools::ReadMemoryEx<INT>(Offset::RootComponent + 0x140);//SceneComponent* HomingTargetComponent? old 14c
	////DWORD VehicleCommon = Tools::ReadMemoryEx<INT>(Offset::VehicleCommon + 0x6f8);//VehicleCommonComponent* VehicleCommon? old 6a0
	//FLOAT BaseFlyTime = Distance / BulletSpeed;
	//FLOAT SecFlyTime = BaseFlyTime * temp;
	//float BulletTravelTime = Distance / Offset::BulletFireSpeed;
	//float zAssist;

	//if (Distance < 5000.f)
	//	zAssist = 1.8f;
	//else if (Distance < 10000.f)
	//	zAssist = 1.72f;
	//else if (Distance < 15000.f)
	//	zAssist = 1.23f;
	//else if (Distance < 20000.f)
	//	zAssist = 1.24f;
	//else if (Distance < 25000.f)
	//	zAssist = 1.25f;
	//else if (Distance < 30000.f)
	//	zAssist = 1.26f;
	//else if (Distance < 35000.f)
	//	zAssist = 1.27f;
	//else if (Distance < 40000.f)
	//	zAssist = 1.28f;
	//else if (Distance < 45000.f)
	//	zAssist = 1.29f;
	//else if (Distance < 50000.f)
	//	zAssist = 1.30f;

	//HeadPos.X += Velocity.X * BulletTravelTime;
	//HeadPos.Y += Velocity.Y * BulletTravelTime;
	//HeadPos.Z += Velocity.Z * BulletTravelTime * zAssist + 50.5f * 5.72f * BulletTravelTime * BulletTravelTime;

	FLOAT xDif = HeadPos.X - MyPosition.X;
	FLOAT yDif = HeadPos.Y - MyPosition.Y;
	FLOAT zDif = HeadPos.Z - MyPosition.Z;

	float Hyp = sqrt(xDif * xDif + yDif * yDif);
	Coordinate.X = atan2(zDif, Hyp) * 180.0f / 3.1415926535897f;
	Coordinate.Y = atan2(yDif, xDif) * 180.0f / 3.1415926535897f;

	return Coordinate;
}

int Memory::AimFindBestTarget() {
	float targetDistance = 9999.0;
	VECTOR2 retval;
	int dist, headdist;
	int ret;
	for (int i = 0; i < Data::AActorList.size(); i++)
	{
		DWORD tmpAddv = Tools::ReadMemoryEx<INT>(Data::AActorList[i].Address + Offset::Mesh);
		DWORD bodyAddv = tmpAddv + Offset::BodyAddv;
		DWORD boneAddv = Tools::ReadMemoryEx<INT>(tmpAddv + Offset::MinLOD) + 48;
		VECTOR2 chest;
		VECTOR2 head;
		VECTOR3 chestPos = Algorithm::GetBoneWorldPosition(bodyAddv, boneAddv + 4 * 48);


		if (Algorithm::WorldToScreenBone(Data::viewMatrix, chestPos, chest, &dist))
		{
			if (Setting::fovcircle)
			{
				if (Aimbot::InsideFov(DX11Window::Width, DX11Window::Height, chest, Setting::fovcircleredus/*FovRadius*/))
				{
					float cross_dist = sqrt(pow(chest.X - DX11Window::Width / 2, 2) + pow(chest.Y - DX11Window::Height / 2, 2));
					if (cross_dist < targetDistance)
					{
						ret = i;
						targetDistance = cross_dist;

					}
				}
			}
			else
			{

				float cross_dist = sqrt(pow(chest.X - DX11Window::Width / 2, 2) + pow(chest.Y - DX11Window::Height / 2, 2));

				if (cross_dist < targetDistance)
				{
					ret = i;
					targetDistance = cross_dist;

				}

			}
		}
	}
	return ret;

}

int Width1 = GetSystemMetrics(SM_CXSCREEN);
int Height1 = GetSystemMetrics(SM_CYSCREEN);

static bool BulletKeyState = false;
bool  Memory::IsMagicInitialized = false;
VOID Memory::MemoryThread()
{

	VECTOR3 MagicCoordinate;
	VECTOR3 AimRotation;

	while (true)
	{
		if (Game::isUnloaded)
		{
			break;
		}
		if (Data::NetDriver > 0)
		{
			if (Setting::MagicBullet || Setting::engine == 1)
			{


				if (IsMagicInitialized == false)
				{
					GetMagicAddress();
					InitializeMagic();
					HookMagic();
					IsMagicInitialized = true;
				}
				MagicCoordinate = GetMagicRunningCoordinatesVip();
				//if (Setting::AimPrediction)
				//{
				//	//MagicCoordinate = GetAimPrediction();
				//}
				//else
				//{
				//	MagicCoordinate = GetMagicRunningCoordinatesVip();

				//}

				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{


					Tools::WriteMemoryEx<FLOAT>(MagicBulletHook + 44, MagicCoordinate.X);
					Tools::WriteMemoryEx<FLOAT>(MagicBulletHook + 54, MagicCoordinate.Y);
				}

				// Refresh magic
				if (GetAsyncKeyState(0x52) & 1)
				{
					if (IsMagicInitialized == true)
					{
						if (Data::NetDriver > 0)
						{
							IsMagicInitialized = false;
							RestoreHook();
							GetMagicAddress();
							HookMagic();
							IsMagicInitialized = true;
						}
					}
				}

			}
			else if (Setting::MagicBullet == false && IsMagicInitialized == true)
			{
				RestoreHook();
				MagicBulletList.clear();
				VirtualFreeEx(Tools::GameProcess, (LPVOID)MagicBulletHook, 0, MEM_RELEASE);
				MagicBulletAddress = 0;
				MagicBulletHook = 0;
				ZeroMemory(RealByteCode, sizeof(RealByteCode));
				IsMagicInitialized = false;
			}

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}



//////////// magic 360/////////////////////////

struct FRotator
{
	float Pitch;
	float Yaw;
	float Roll;
};

struct MinimalViewInfo
{
	VECTOR3 Location;
	VECTOR3 LocationLocalSpace;
	FRotator Rotation;
	float FOV;
};

struct CameraCacheEntry
{
	float TimeStamp;
	char chunks[0xC];
	MinimalViewInfo POV;
};

FRotator ToRotator(VECTOR3 local, VECTOR3 target)
{
	VECTOR3 rotation;
	rotation.X = local.X - target.X;
	rotation.Y = local.Y - target.Y;
	rotation.Z = local.Z - target.Z;

	FRotator newViewAngle = { 0 };

	float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

	newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float)3.14159265358979323846);
	newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float)3.14159265358979323846);
	newViewAngle.Roll = (float)0.f;

	if (rotation.X >= 0.f)
		newViewAngle.Yaw += 180.0f;

	return newViewAngle;
}

VECTOR3 ClosestToCrosshair()
{
	Sleep(20);
	float targetDistance = 500.0f;
	VECTOR2 retval;
	int dist, headdist;
	VECTOR3 ret;
	for (int i = 0; i < Data::AActorList.size(); i++) {

		DWORD tmpAddv = Tools::ReadMemoryEx<INT>(Data::AActorList[i].Address + Offset::Mesh);
		DWORD bodyAddv = tmpAddv + Offset::BodyAddv;
		DWORD boneAddv = Tools::ReadMemoryEx<INT>(tmpAddv + Offset::MinLOD) + 48;
		VECTOR2 chest;
		VECTOR2 head;
		//VECTOR3 chestPos = Algorithm::GetBoneWorldPosition(bodyAddv, boneAddv + 3 * 48); 
		VECTOR3 CurrPos = { 0 };
		if (Setting::curraim == 0) {
			CurrPos = Algorithm::GetBoneWorldPosition(bodyAddv, boneAddv + 5 * 48);
			CurrPos.Z += 15;
		}
		if (Setting::curraim == 1)
		{
			CurrPos = Algorithm::GetBoneWorldPosition(bodyAddv, boneAddv + 4 * 48);
		}
		if (Setting::curraim == 2)
		{
			CurrPos = Algorithm::GetBoneWorldPosition(bodyAddv, boneAddv + 1 * 48);
		}
		if (Algorithm::WorldToScreenBone(Data::viewMatrix, CurrPos, chest, &dist))
		{
			if (Algorithm::WorldToScreenBone(Data::viewMatrix, CurrPos, chest, &dist))
			{
				float cross_dist = sqrt(pow(chest.X - DX11Window::Width / 2, 2) + pow(chest.Y - DX11Window::Height / 2, 2));

				if (cross_dist < targetDistance)
				{
					ret = CurrPos;
					targetDistance = cross_dist;

				}
			}

		}
	}
	return ret;
}

void Memory::magnatbullot()
{
	while (true)
	{
		if (Game::isUnloaded)
		{
			break;
		}
		Sleep(5);
		if (Setting::CameraCatch)
		{
			auto LocalController = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::LocalController); //STExtraPlayerController* STPlayerController;//[Offset:
			if (LocalController)
			{

				auto PlayerCameraManager = Tools::ReadMemoryEx<DWORD>(LocalController + Offset::PlayerCameraManager); //PlayerCameraManager* PlayerCameraManager;//[Offset:
				if (PlayerCameraManager)
				{
					CameraCacheEntry CameraCache = Tools::ReadMemoryEx<CameraCacheEntry>(PlayerCameraManager + Offset::CameraCache);

					VECTOR3 HeadPosition = ClosestToCrosshair();
					VECTOR3 currentViewAngle = CameraCache.POV.Location;

					if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						FRotator aimRotation = ToRotator(currentViewAngle, HeadPosition);
						CameraCache.POV.Rotation = aimRotation;
						Tools::WriteMemoryEx<CameraCacheEntry>(PlayerCameraManager + 0x370, CameraCache);

					}
				}
			}
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
}




//////////////////////////////////////////////////////////////////
bool IsFlyManInitialized = false;
DWORD FlyManAddress = 0;
BYTE FlyManSearch[] = { 0x00, 0x00, 0x75, 0xC4, 0x00, 0x00, 0x7A, 0x45, 0x9A, 0x99 };

VOID SetFlyManAddress()
{
	std::vector<DWORD_PTR> FoundedBase;
	Tools::FindPattern(FlyManSearch, sizeof(FlyManSearch), 0x10000000, 0xA0000000, 0, 0, FoundedBase);
	FlyManAddress = FoundedBase[0];
} //0x00, 0x00, 0x75, 0xC4, 0x00, 0x00, 0x7A, 0x45, 0x9A, 0x99, 0x99, 0x3E, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x40, 0x00

int	flym = 80000.0f;


////////instant stuck
float instback = 0.0f;
bool instant = false;

#pragma region Memory

VOID Memory::MemoryFung()
{

	while (true)
	{
		if (Game::isUnloaded)
		{
			break;
		}
		
		if (Setting::speedcar)
		{
			///// car speed fly sruck 
			DWORD MyWorld = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::RootComponent);
			DWORD VehicleAnimInstance = Tools::ReadMemoryEx<DWORD>(MyWorld + Offset::AnimInstance); // AnimInstance* AnimScriptInstance;
			DWORD WheeledVehicleMovementComponent = Tools::ReadMemoryEx<DWORD>(VehicleAnimInstance + Offset::WheeledVehicleMovementComponent);
			DWORD ptrCar = Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(WheeledVehicleMovementComponent + 404) + 88);

			for (int x = 0; x <= 8; x++)
			{
				if (GetAsyncKeyState(VK_LSHIFT))
				{
					Tools::WriteMemoryEx<float>(ptrCar + 4 * x, 200);
				}
				else if (GetAsyncKeyState('S'))
				{
					Tools::WriteMemoryEx<float>(ptrCar + 4 * x, -200);
				}
			}
		}
		if (Setting::carfly)
		{
			///// car speed fly sruck 
			DWORD MyWorld = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::RootComponent);
			DWORD VehicleAnimInstance = Tools::ReadMemoryEx<DWORD>(MyWorld + Offset::AnimInstance); // AnimInstance* AnimScriptInstance;
			DWORD WheeledVehicleMovementComponent = Tools::ReadMemoryEx<DWORD>(VehicleAnimInstance + Offset::WheeledVehicleMovementComponent);
			DWORD ptrCar = Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(WheeledVehicleMovementComponent + 404) + 88);

			for (int x = 20; x <= 32; x++)
			{
				if (GetKeyState(VK_SPACE) & 0x8000)
				{
					Tools::WriteMemoryEx<float>(ptrCar + 4 * x, Setting::flyCarPower * -1);
				}
			}
		}


		////////////instanthit////////
		if (Setting::instanthit && instant == false)
		{
			DWORD weaponOffSet = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::CurrentReloadWeapon);
			DWORD shootOffset = Tools::ReadMemoryEx<DWORD>(weaponOffSet + Offset::ShootWeaponEntity);
			instback = Tools::ReadMemoryEx<FLOAT>(shootOffset + Offset::BulletFireSpeed);

			if (weaponOffSet != 0)
			{

				if (shootOffset != Setting::instantPower)
				{
					Tools::WriteMemoryEx<FLOAT>(shootOffset + Offset::BulletFireSpeed, Setting::instantPower);
					instant = true;
				}
			}

		}
		else if (!Setting::instanthit && instant == true)
		{
			DWORD weaponOffSet = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::CurrentReloadWeapon);
			DWORD shootOffset = Tools::ReadMemoryEx<DWORD>(weaponOffSet + Offset::ShootWeaponEntity);

			if (instant)
			{
				Tools::WriteMemoryEx<FLOAT>(shootOffset + Offset::BulletFireSpeed, instback);
				instant = false;
			}
		}

		/////////////////////FastLand//////////////////

		if (Setting::fastland)
		{

			if (GetAsyncKeyState(VK_LSHIFT))
			{
				DWORD characterparchute = Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::ParachuteComponent); //CharacterParachuteComponent* ParachuteComponent
				if (characterparchute != 0)
				{
					Tools::WriteMemoryEx<FLOAT>(characterparchute + Offset::CurrentFallSpeed, 20000.0f); //float CurrentFallSpeed

				}
			}

		}

		//////////////////////FastRun/////////////////
		if (Setting::fastrun)
		{

			if (GetAsyncKeyState(VK_LSHIFT))
			{
				//float write = 3.0f;
				Tools::WriteMemoryEx<float>(Data::LocalPlayer + Offset::CharacterOverrideAttrs, Setting::fastRunPower);
			}
			else if (GetAsyncKeyState(VK_LSHIFT) == 0)
			{
				float write = 1.0f;
				Tools::WriteMemoryEx<float>(Data::LocalPlayer + Offset::CharacterOverrideAttrs, write);

			}

		}


		/////////////////NoRecouil//////////////////
		if (Setting::recoil)
		{
			float writee = 0.0f;
			DWORD weaponOffSet = Tools::ReadMemoryEx<UINT>(Data::LocalPlayer + Offset::CurrentReloadWeapon);
			if (weaponOffSet != 0)
			{
				DWORD shootOffset = Tools::ReadMemoryEx<UINT>(weaponOffSet + Offset::ShootWeaponEntity);

				if (shootOffset != 0)
				{
					Tools::WriteMemoryEx<float>(shootOffset + 2120, writee);
					Tools::WriteMemoryEx<float>(shootOffset + 2124, writee);
					Tools::WriteMemoryEx<float>(shootOffset + 2128, writee);

				}
			}
		}
		/////////////////FlyMan//////////
		if (Setting::fly)
		{
			if (IsFlyManInitialized == false)
			{
				SetFlyManAddress();

				IsFlyManInitialized = true;
			}

			if (GetAsyncKeyState(VK_SPACE) & 1) //0x8000  //VK_SPACE  //0x56
			{
				Tools::WriteMemoryEx<FLOAT>(FlyManAddress, Setting::flyManPower);
			}
			else if (GetAsyncKeyState(VK_SPACE) == 0)
			{
				if (Tools::ReadMemoryEx<float>(FlyManAddress) != -980.0f)
				{
					Tools::WriteMemoryEx<FLOAT>(FlyManAddress, -980.0f);
				}
			}
		}

		//////////////GoodView//////////

		if (Setting::GodView)
		{
			float up = -160.0f;
			float down = 160.0f;

			if (GetAsyncKeyState(Setting::godviewup))
			{

				Tools::ReadMemoryEx<INT>(Data::LocalPlayer + 0x111C); //float ExtraBoostFactor;//[Offset: 0x111c, Size: 4]  //0x1b38
				Tools::WriteMemoryEx<float>(Data::LocalPlayer + 0x1bd8, up); //float StandHalfHeight;//[Offset:
			}
			else if (GetAsyncKeyState(Setting::godviewdown))
			{
				Tools::ReadMemoryEx<INT>(Data::LocalPlayer + 0x111C);
				Tools::WriteMemoryEx<float>(Data::LocalPlayer + 0x1bd8, down);
			}
			else if (GetAsyncKeyState(Setting::godviewFr))
			{
				Tools::ReadMemoryEx<INT>(Data::LocalPlayer + 0x111C);
				Tools::WriteMemoryEx<float>(Data::LocalPlayer + 0x1be0, down);
			}
			else
			{
				Tools::ReadMemoryEx<INT>(Data::LocalPlayer + 0x111C);
				Tools::WriteMemoryEx<float>(Data::LocalPlayer + 0x1bd8, 80.0f);
			}
		}

		////////////////FlyCar/////////
		//if (Setting::carfly)
		//{
		//	if (IsFlyCarInitialized == false)
		//	{
		//		SetFlyCarAddress();

		//		IsFlyCarInitialized = true;
		//	}

		//	if (GetAsyncKeyState(VK_SPACE) & 1)
		//	{
		//		Tools::WriteMemoryEx<FLOAT>(FlyCarAddress, Setting::flyCarPower);
		//	}
		//	else if (GetAsyncKeyState(VK_SPACE) == 0)
		//	{
		//		if (Tools::ReadMemoryEx<float>(FlyCarAddress) != -980.0f)
		//		{
		//			Tools::WriteMemoryEx<FLOAT>(FlyCarAddress, -980.0f);
		//		}
		//	}
		//}

				////////////FastCar////////////
		//if (Setting::speedcar)
		//{
		//	if (GetAsyncKeyState(VK_LSHIFT)) {
		//		DWORD num12 = Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(Data::LocalPlayer + 0x16c) + 0x700) + 0x6f0) + 0x194) + 0x58); //float EnActiveTimeThreshold;//[Offset: 0x6d0,
		//		Tools::WriteMemoryEx<FLOAT>(num12, Setting::speedCarPower);
		//		Tools::WriteMemoryEx<FLOAT>(num12 + 4, Setting::speedCarPower);
		//		Tools::WriteMemoryEx<FLOAT>(num12 + 8, Setting::speedCarPower);
		//		Tools::WriteMemoryEx<FLOAT>(num12 + 12, Setting::speedCarPower);
		//		Tools::WriteMemoryEx<FLOAT>(num12 + 16, Setting::speedCarPower);
		//		Tools::WriteMemoryEx<FLOAT>(num12 + 20, Setting::speedCarPower);
		//		Tools::WriteMemoryEx<FLOAT>(num12 + 24, Setting::speedCarPower);
		//		Tools::WriteMemoryEx<FLOAT>(num12 + 28, Setting::speedCarPower);
		//	}
		//}


		/////xEffects/////
	/*	if (Setting::MagicX)
		{
			Tools::SuperPower(Setting::LibUe4, 0x1C46924, "00 00 00 00");
		}*/

		bool IsChanged = false;
		if (Setting::MagicX && IsChanged == false)
		{
			BYTE pattern[] = { 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x38, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f };
			BYTE patter2[] = { 0x00, 0x08, 0xF3, 0x45, 0x00, 0x00, 0x38, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f };
			Tools::AOBREP(pattern, patter2, sizeof(pattern), sizeof(patter2), 5000);
			IsChanged = true;
		}
		else if (!Setting::MagicX && IsChanged == true)
		{
			BYTE pattern[] = { 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x38, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f };
			BYTE patter2[] = { 0x00, 0x08, 0xF3, 0x45, 0x00, 0x00, 0x38, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f };
			Tools::AOBREP(patter2, pattern, sizeof(patter2), sizeof(pattern), 5000);
			IsChanged = false;
		}


		///////loofy hands/////////
		bool loofy = false;
		if (Setting::loofy && loofy == false) {
			BYTE Scan[] = { 0x95, 0x2D, 0xBC, 0x41, 0x00, 0x80, 0x6F, 0x39, 0x00, 0x90, 0xC7, 0x3B, 0x01, 0x00, 0x00, 0x27 };
			BYTE Replace[] = { 0x00, 0x00, 0xC8, 0x42, 0x00, 0x00, 0x48, 0x43, 0x00, 0x90, 0xC7, 0x3B, 0x01, 0x00, 0x00, 0x27 };
			Tools::AOBREP(Scan, Replace, sizeof(Scan), sizeof(Replace), 5000);
			loofy = true;
		}
		else if (!Setting::loofy && loofy == true)
		{
			BYTE Scan[] = { 0x00, 0x00, 0xC8, 0x42, 0x00, 0x00, 0x48, 0x43, 0x00, 0x90, 0xC7, 0x3B, 0x01, 0x00, 0x00, 0x27 };
			BYTE Replace[] = { 0x95, 0x2D, 0xBC, 0x41, 0x00, 0x80, 0x6F, 0x39, 0x00, 0x90, 0xC7, 0x3B, 0x01, 0x00, 0x00, 0x27 };
			Tools::AOBREP(Scan, Replace, sizeof(Scan), sizeof(Replace), 5000);
			loofy = false;
		}


		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
