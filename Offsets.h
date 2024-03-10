#pragma once

#include "Includes.h"

namespace Offset
{
	const DWORD UE4 = 0;
	const DWORD Gname = 0x7827A58 + 0x88;
	const DWORD Gworld = 0x7B28F74 + 0x3C;

	const DWORD Nation = 0x68c;
	const DWORD PersistentLevel = 0x20;
	const DWORD NetDriver = 0x24;
	const DWORD ServerConnection = 0x60;
	const DWORD PlayerController = 0x20;
	const DWORD AcknowledgedPawn = 0x368;
	const DWORD EntityList = 0x70;
	//const DWORD EntityCount = 0x74;
	const DWORD EntityCount = EntityList + 4;

	const DWORD RootComponent = 0x158;		// SceneComponent* RootComponent;//[Offset:
	const DWORD CurrentStates = 0xb50;		//uint64 CurrentStates;//[Offset:
	//speed car and fly
	const DWORD WheeledVehicleMovementComponent = 0x1100; // WheeledVehicleMovementComponent* WheeledVehicleMovementComponent; -> WheeledVehicleMovementComponent* VehicleMovementComponent;//[Offset:
	const DWORD AnimInstance = 0x820;                    // AnimInstance* AnimScriptInstance;

	// AActor
	const DWORD TeamId = 0x6b4;				//Class: UAECharacter.Character.Pawn.Actor.Object -> int TeamID;//[Offset:
	const DWORD PoseState = 0x104c;			//Class: STExtraBaseCharacter.STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object -> byte PoseState;//[Offset:
	const DWORD IsBot = 0x74d;				// bool bIsAI;//(ByteOffset: 
	const DWORD Name = 0x680;				// Class: UAECharacter.Character.Pawn.Actor.Object -> FString PlayerName;//[Offset:
	const DWORD Status = 0xaa0;				// FString PlayerName;//[Offset:
	//const DWORD Nation = 0x674;
	const DWORD Health = 0xa0c;				// float Health;//[Offset:
	const DWORD HealthMax = 0xa10;			// float HealthMax;//[Offset:
	const DWORD bDead = 0xa24;				// bool bDead;//(ByteOffset: 0, ByteMask: 1, FieldMask: 1)[Offset: 0x978, Size: 1]
	// magic prediction
	const DWORD CharacterMovement = 0x358;	// CharacterMovementComponent* CharacterMovement;//[Offset:
	const DWORD LastUpdateVelocity = 0x2c0;	// Vector LastUpdateVelocity;//[Offset:
	const DWORD Velocity = 0xc8;			//Class: MovementComponent.ActorComponent.Object-> Vector Velocity;//[Offset:

	//const DWORD RelativeLocation = 0x118;	// Vector RelativeLocation;//[Offset: 0x120,
	//const DWORD RelativeRotation = 0x124;	// Rotator RelativeRotation;//[Offset: 0x12c,
	const DWORD Position = 0x160;

	// Lot BOX 
	const DWORD itemBase = 0x6b0;			// PickUpItemData[] PickUpDataList;//[Offset:
	const DWORD boxItemsCount = 0x6c8;		// enum BoxType;//[Offset: 

	// Bone
	const DWORD Mesh = 0x354;				// SkeletalMeshComponent* Mesh;//[Offset: 0x320,  /  tmpOffset
	const DWORD BodyAddv = 0x150;	 		// ActorOffset 
	const DWORD MinLOD = 0x6a0;				// int MinLOD;//[Offset: 0x5b0,  / boneOffset

	// Camera
	const DWORD PlayerCameraManager = 0x378;// Class: PlayerController.Controller.Actor.Object -> PlayerCameraManager* PlayerCameraManager;//[Offset: 0x340,
	const DWORD CameraCache = 0x380;		// Class: PlayerCameraManager.Actor.Object -> CameraCacheEntry CameraCache;//[Offset: 0x350,
	const DWORD POV = 0x10;					// Class: CameraCacheEntry -> MinimalViewInfo POV;//[Offset: 0x10,
	const DWORD Location = 0x0;				// Class: MinimalViewInfo -> Vector Location;//[Offset: 0x0,
	const DWORD Rotation = 0x18;			// Class: MinimalViewInfo -> Rotator Rotation;//[Offset: 0x18,
	const DWORD FOV = 0x24;					// Class: MinimalViewInfo -> float FOV;//[Offset: 0x24,
	const DWORD LocalController = 0x30c4;	//STExtraPlayerController* STPlayerController;//[Offset:

	// Instant hit
	const DWORD CurrentReloadWeapon = 0x1DAC; //STExtraWeapon* CurrentReloadWeapon;//[Offset: 0x --- or 	PostProcessSettings[] PostProcessBlendCache;//[Offset: 0x1a98, Size: 12]
	const DWORD ShootWeaponEntity = 0xc88;  // ShootWeaponEntity* ShootWeaponEntityComp;//[Offset:  ShootWeaponEntity* ShootWeaponEntityComp;//[Offset: 
	const DWORD BulletFireSpeed = 0x418; /// Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object -> float BulletFireSpeed

	/*const DWORD ShootInterval = 0x428;
	const DWORD ShootWeaponEntityComp = 0xb40;
	const DWORD AccessoriesVRecoilFactor = 0x848;
	const DWORD AccessoriesHRecoilFactor = 0x818;
	const DWORD AccessoriesRecoveryFactor = 0x81c;
	const DWORD RecoilKickADS = 0x920;
	const DWORD AnimationKick = 0x938;
	const DWORD ShotGunVerticalSpread = 0x868;
	const DWORD ShotGunHorizontalSpread = 0x86c;
	const DWORD GameDeviationFactor = 0x870;
	const DWORD LaunchGravityScale = 0x318;
	const DWORD SwitchWeaponSpeedScale = 0x1940;
	const DWORD bEnablePlayerPickUpAnim = 0x12e0;*/

	//////SPEED OFFSETS/////
	const DWORD CharacterOverrideAttrs = 0xd68; //CharacterOverrideAttrs CharacterOverrideAttrs;
	//////FastLanding OFFSETS/////
	const DWORD ParachuteComponent = 0xfb8; // CharacterParachuteComponent* ParachuteComponent;//[Offset: 0xe88,
	const DWORD CurrentFallSpeed = 0xfa0; // CharacterParachuteComponent* ParachuteComponent;//[Offset: 0xe88,


	/*const DWORD Controller = 0x31c;
	const DWORD ControlRotation = 0x318;*/


	////vehicle
	const  DWORD VehicleCommon = 0x784;            // VehicleCommonComponent* VehicleCommon;//[Offset: 0x698,
	const  DWORD HP = 0x1e8;                    // Class: VehicleCommonComponent.VehicleComponent.LuaActorComponent.ActorComponent.Object -> float HP;//[Offset: 0x11c, Size: 4]
	const  DWORD HPMax = 0x1e4;                    // Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object -> float HPMax;//[Offset: 0x118,
	const  DWORD FuelMax = 0x240;                // Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object -> float FuelMax;//[Offset: 0x130,
	const  DWORD Fuel = 0x244;					// Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object -> float Fuel;//[Offset: 0x134,
	const DWORD bIsEngineStarted = 0x765;		// bool bIsEngineStarted;//(ByteOffset: 

	///ipad
	const float IpadOffset = 0x3CB57A4;

	///magic
	const DWORD uObjectPosition = 0x120;				// Vector RelativeLocation;//[Offset: 0x120 , Size: 12]
	const DWORD CurrentWeaponReplicated = 0x40c;         // STExtraWeapon* CurrentWeaponReplicated;//[Offset: 0x41c , Size: 4]
	const DWORD CharacterWeaponManager = 0x1a70;         // CharacterWeaponManagerComponent* CharacterWeaponManager;//[Offset: 0x28a8 , Size: 4]

	const DWORD GameStateBase = 0x13c;
	const DWORD ElapsedTime = 0x7fc; //int ElapsedTime;//[Offset:

}
