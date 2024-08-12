#pragma once

#include "UECore.h"

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE]

bool InitSDK();
bool InitSDK(const std::wstring& ModuleName, uintptr_t gObjectsOffset, uintptr_t gNamesOffset, uintptr_t gWorldOffset);

enum class ETigerOutlineMode : uint8_t
{
	HeightenedSenses = 0,
	Lure = 1,
	EnemyPlayer = 2,
	ScoutingFamiliarsGroupMember = 3,
	ScoutingFamiliars = 4,
	BloodHuntedHSReveal = 5,
	BloodHunted = 6,
	CapturingHaven = 7,
	CharmingUs = 8,
	GroupMember = 9,
	ExtendedGroupMember = 10,
	LocalPlayer = 11,
	Count = 12,
	None = 13,
	MAX = 14
};

enum class ETigerCharacterType : uint8_t
{
	Player = 0,
	Npc = 1,
	TutorialTrainer = 2,
	PlayerBot = 3,
	TargetDummy = 4,
	Count = 5,
	ETigerCharacterType_MAX = 6,
};

enum class ETigerInventoryItemType : uint8_t
{
	TigerInventoryItem_Firearm = 0,
	TigerInventoryItem_Melee = 1,
	TigerInventoryItem_Unarmed = 2,
	TigerInventoryItem_Outfit = 3,
	TigerInventoryItem_Amulet = 4,
	TigerInventoryItem_Artifact = 5,
	TigerInventoryItem_BodyArmor = 6,
	TigerInventoryItem_Relic = 7,
	TigerInventoryItem_Ammo = 8,
	TigerInventoryItem_CombinedAmmo = 9,
	TigerInventoryItem_Consumable = 10,
	TigerInventoryItem_Mod = 11,
	TigerInventoryItem_Collectible = 12,
	TigerInventoryItem_Key = 13,
	TigerInventoryItem_Size = 14,
	TigerInventoryItem_MAX = 15
};

enum class ETigerItemRarity : uint8_t
{
	TigerItemRarity_Common = 0,
	TigerItemRarity_Uncommon = 1,
	TigerItemRarity_Rare = 2,
	TigerItemRarity_Epic = 3,
	TigerItemRarity_Legendary = 4,
	TigerItemRarity_Size = 5,
	TigerItemRarity_MAX = 6,
};

enum class ETigerWeaponType : uint8_t
{
	AssaultRifle = 0,
	Revolver = 1,
	Rifle = 2,
	SMG = 3,
	Pistol = 4,
	Axe = 5,
	Bat = 6,
	Knife = 7,
	Shotgun = 8,
	Sword = 9,
	Bow = 10,
	Crossbow = 11,
	Count = 12,
	ETigerWeaponType_MAX = 13,
};

enum class ETigerWeaponFireMode : uint8_t
{
	Single = 0,
	Burst = 1,
	Automatic = 2,
	Count = 3,
	MAX = 4
};

enum class ETigerSpreadIncreaseMode : uint8_t
{
	Add = 0,
	Multiply = 1,
	MAX = 2
};

struct FHitResult
{
public:
	uint8_t                                       bBlockingHit : 1;                                  // 0x0000(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                       bStartPenetrating : 1;                             // 0x0000(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                       Pad_1[0x3];                                        // 0x0001(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32_t                                       FaceIndex;                                         // 0x0004(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Time;                                              // 0x0008(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Distance;                                          // 0x000C(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector								  Location;                                          // 0x0010(0x000C)(NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector								  ImpactPoint;                                       // 0x001C(0x000C)(NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector								  Normal;                                            // 0x0028(0x000C)(NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector								  ImpactNormal;                                      // 0x0034(0x000C)(NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector								  TraceStart;                                        // 0x0040(0x000C)(NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector								  TraceEnd;                                          // 0x004C(0x000C)(NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         PenetrationDepth;                                  // 0x0058(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                       Item;                                              // 0x005C(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                       ElementIndex;                                      // 0x0060(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                       Pad_61[0x3];                                       // 0x0061(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	TWeakObjectPtr<class UPhysicalMaterial>       PhysMaterial;                                      // 0x0064(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TWeakObjectPtr<class AActor>                  Actor;                                             // 0x006C(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TWeakObjectPtr<class UPrimitiveComponent>     Component;                                         // 0x0074(0x0008)(ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FName                                   BoneName;                                          // 0x007C(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FName                                   MyBoneName;                                        // 0x0084(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

struct FMinimalViewInfo
{
public:
	struct FVector Location; // 0x0000(0x000C) Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	struct FRotator Rotation; // 0x000C(0x000C) Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic
	float FOV; // 0x0018(0x0004) Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float DesiredFOV; // 0x001C(0x0004) ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float OrthoWidth; // 0x0020(0x0004) Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float OrthoNearClipPlane; // 0x0024(0x0004) Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float OrthoFarClipPlane; // 0x0028(0x0004) Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float AspectRatio; // 0x002C(0x0004) Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	bool bConstrainAspectRatio : 1; // 0x0030(0x0001) BIT_FIELD Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	bool bUseFieldOfViewForLOD : 1; // 0x0030(0x0001) BIT_FIELD Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_VOZJ[0x3]; // 0x0031(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	unsigned char UnknownData_VOZK[0x1]; // 0x0034(0x0001) Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_MA8F[0x3]; // 0x0035(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	float PostProcessBlendWeight; // 0x0038(0x0004) BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_308J[0x4]; // 0x003C(0x0004) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	unsigned char UnknownData_308K[0x550]; // 0x0040(0x0550) BlueprintVisible, NativeAccessSpecifierPublic
	struct FVector2D OffCenterProjectionOffset; // 0x0590(0x0008) Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, Transient, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_DENC[0x48]; // 0x0598(0x0048) MISSED OFFSET (PADDING)
};

struct FTigerSpreadModifier
{
public:
	ETigerSpreadIncreaseMode Mode; // 0x0000(0x0001) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_VUHK[0x3]; // 0x0001(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	float Speed; // 0x0004(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float Amount; // 0x0008(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
};

struct FTigerFireSettings
{
public:
	float BulletDamage; // 0x0000(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	ETigerWeaponFireMode FireMode; // 0x0004(0x0001) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_9TY8[0x3]; // 0x0005(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	int32_t BurstCount; // 0x0008(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float ShotsFiredPerSecondInBurst; // 0x000C(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	int32_t BulletsFiredSimultaneously; // 0x0010(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float ShotsFiredPerSecond; // 0x0014(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	class UClass* AreaEffect; // 0x0018(0x0008) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float FireStickyTime; // 0x0020(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float VerticalRecoilAmount; // 0x0024(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float HorizontalRecoilAmount; // 0x0028(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float StartingSpread; // 0x002C(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	struct FTigerSpreadModifier SpreadModifiers[0x7]; // 0x0030(0x0054) Edit, NoDestructor, NativeAccessSpecifierPublic
	float TimeUntilSpreadDecreases; // 0x0084(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float BaseMovementSpeedMultiplier; // 0x0088(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float AimingMovementSpeedMultiplier; // 0x008C(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float HipFireMovementSpeedMultiplier; // 0x0090(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_136W[0x4]; // 0x0094(0x0004) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	class UCurveFloat* SpreadIncreaseCurve; // 0x0098(0x0008) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	class UCurveFloat* SpreadDecreaseCurve; // 0x00A0(0x0008) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	class UCurveFloat* FireRateIncreaseCurve; // 0x00A8(0x0008) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	class UCurveFloat* FireRateDecreaseCurve; // 0x00B0(0x0008) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	float MasqueradeNoiseEventRadius; // 0x00B8(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	bool ReverseSpreadChange; // 0x00BC(0x0001) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	bool bPierceCivilians; // 0x00BD(0x0001) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	bool bUsesScope; // 0x00BE(0x0001) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_1BZ4[0x1]; // 0x00BF(0x0001) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	int32_t ResistanceStart; // 0x00C0(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	int32_t ResistanceEnd; // 0x00C4(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	int32_t ResistanceStrength; // 0x00C8(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	int32_t TriggerVibrationFeedbackStrength; // 0x00CC(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	int32_t ADSResistanceStart; // 0x00D0(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	int32_t ADSResistanceStrength; // 0x00D4(0x0004) Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
};

struct FCameraCacheEntry
{
public:
	float Timestamp; // 0x0000(0x0004) ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char UnknownData_L39P[0xC]; // 0x0004(0x000C) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
	struct FMinimalViewInfo POV; // 0x0010(0x05E0) NativeAccessSpecifierPublic
};

class UDataAsset : public UObject
{
public:
	PAD(0x8);
};

class UTigerItemAsset : public UDataAsset
{
public:
	PAD(0x10);
	ETigerInventoryItemType ItemType; // 0x0040
	ETigerItemRarity ItemRarity; // 0x0041
	PAD(0x6);
	FText Name; // 0x0048
	PAD(0xD0);
};

class UActorComponent : public UObject
{
public:
	PAD(0x88);
};

class UMovementComponent : public UActorComponent
{
public:
	PAD(0x40);
};

class UNavMovementComponent : public UMovementComponent
{
public:
	PAD(0x40);
};

class UPawnMovementComponent : public UNavMovementComponent
{
public:
	PAD(0x8);
};

class UCharacterMovementComponent : public UPawnMovementComponent
{
public:
	PAD(0x108);
	FQuat LastUpdateRotation; // 0x0240
	FVector LastUpdateLocation; // 0x0250
	FVector LastUpdateVelocity; // 0x025C
	PAD(0x898);
};

class USceneComponent : public UActorComponent
{
public:
	PAD(0x6C);
	FVector RelativeLocation; // 0x011C
	FRotator RelativeRotation; // 0x0128
	FVector RelativeScale3D; // 0x0134
	FVector ComponentVelocity; // 0x0140
	PAD(0xAC);

public:
	FVector GetSocketLocation(const class FName& InSocketName);
};

class UPrimitiveComponent : public USceneComponent
{
public:
	PAD(0x258);
};

class UMeshComponent : public UPrimitiveComponent
{
public:
	PAD(0x28);
};

class USkinnedMeshComponent : public UMeshComponent
{
public:
	PAD(0x228);

public:
	FName GetBoneName(int32_t BoneIndex);
	int32_t GetBoneIndex(const class FName& BoneName);
};

class USkeletalMeshComponent : public USkinnedMeshComponent
{
public:
	PAD(0x850);
};

class UProjectileMovementComponent : public UMovementComponent
{
public:
	float InitialSpeed; // 0x00F0
	float MaxSpeed; // 0x00F4
	PAD(0xD8);
};

class UTigerOutlineComponent : public UActorComponent
{
public:
	ETigerOutlineMode CurrentMode; // 0x00B0
	PAD(0x4F);

public:
	void DeactivateOutline(ETigerOutlineMode InMode);
	void ActivateOutline(ETigerOutlineMode InMode);
	bool IsOutlineActivated(const ETigerOutlineMode InMode);
};

class UTigerWeapon : public UObject
{
public:
	PAD(0x10);
	ETigerItemRarity Rarity; // 0x0038
	PAD(0x77);
};

class UTigerRangedWeapon : public UTigerWeapon
{
public:
	FName WeaponName; // 0x00B0
	ETigerWeaponType WeaponType; // 0x00B8
	PAD(0x4F);
	void* VerticalRecoilCurve; // 0x0108
	void* HorizontalRecoilCurve; // 0x0110
	PAD(0x10);
	class ATigerProjectile* ProjectileClass;// 0x0128
	PAD(0xD8);
};

class UTigerRangedWeaponComponent : public UActorComponent
{
public:
	PAD(0xC0);
	UTigerRangedWeapon* EquippedWeaponType; // 0x0170
	PAD(0x150);
	class ATigerProjectile* LastFiredProjectile; // 0x02C8
	PAD(0x8);

public:
	FTigerFireSettings GetCurrentFireSettings();
	class ATigerProjectile* GetCurrentProjectileType();
	class UTigerRangedWeapon* GetEquippedOrWantedWeapon();
};

class UScriptViewportClient : public UObject
{
public:
	PAD(0x10);
};

class UGameViewportClient : public UScriptViewportClient
{
public:
	PAD(0x40);
	class UWorld* World; // 0x0078
	PAD(0x2E0);
};

class AActor : public UObject
{
public:
	PAD(0x200);

public:
	void GetActorBounds(bool bOnlyCollidingComponents, struct FVector* Origin, struct FVector* BoxExtent, bool bIncludeFromChildActors);
	float GetDistanceTo(class AActor* OtherActor);
	FVector GetActorLocation();
	FRotator GetActorRotation();
	USceneComponent* GetRootComponent();
};

class AWorldSettings : public AActor
{
public:
	PAD(0x30);
	float WorldGravityZ; // 0x0258
	float GlobalGravityZ; // 0x025C
	PAD(0x148);
};

class ATigerItemWorldRepresentation : public AActor
{
public:
	PAD(0x18);
	UTigerItemAsset* ItemType; // 0x0240
	PAD(0x60);
};

class ATBPItemC : public ATigerItemWorldRepresentation
{
public:
	PAD(0xE4);

public:
	static inline UClass* StaticClass()
	{
		static UClass* ptr = nullptr;
		if (!ptr)
			ptr = UObject::FindClass(std::string(skCrypt("BlueprintGeneratedClass TBP_Item.TBP_Item_C")));
		return ptr;
	}
};

class ATigerProjectile : public AActor
{
public:
	PAD(0x8);
	UProjectileMovementComponent* ProjectileMovement; // 0x0230
	PAD(0x98);
};

class APlayerState : public AActor
{
public:
	PAD(0x100);

public:
	FString GetPlayerName();
	bool IsOfSameTeam(APlayerState* OtherState);
};

class APlayerCameraManager : public AActor
{
public:
	PAD(0x1888);
	FCameraCacheEntry CameraCachePrivate; // 0x1AB0
	PAD(0x720);

public:
	FVector GetCameraLocation();
	FRotator GetCameraRotation();
};

class APawn : public AActor
{
public:
	PAD(0x20);
	APlayerState* PlayerState; // 0x0248
	PAD(0x38);
};

class ACharacter : public APawn
{
public:
	USkeletalMeshComponent* Mesh; // 0x0288
	UCharacterMovementComponent* CharacterMovement; // 0x0290
	PAD(0x220);
};

class ATigerCharacter : public ACharacter
{
public:
	PAD(0x10);
	UTigerRangedWeaponComponent* RangedWeaponComponent; // 0x04C8
	PAD(0x20);
	UTigerOutlineComponent* OutlineComponent; // 0x04F0
	PAD(0x2AE);
	ETigerCharacterType CharacterType; // 0x07A6
	PAD(0xC9);

public:
	float GetCurrentHealth();
	float GetCurrentShield();
	float GetMaxHealth();
	float GetMaxShield();
	bool IsDead();
	bool IsDowned();
	bool IsFriendlyWith(const class ATigerCharacter* OtherCharacter);

public:
	static inline UClass* StaticClass()
	{
		static UClass* ptr = nullptr;
		if (!ptr)
			ptr = UObject::FindClass(std::string(skCrypt("Class Tiger.TigerCharacter")));
		return ptr;
	}
};

class AController : public AActor
{
public:
	PAD(0x8);
	APlayerState* PlayerState; // 0x0230
	PAD(0x68);

public:
	void SetControlRotation(const struct FRotator& NewRotation);
	APawn* GetPawn();
	bool LineOfSightTo(class AActor* Other, const struct FVector& ViewPoint, bool bAlternateChecks = false);
};

class APlayerController : public AController
{
public:
	PAD(0x8);
	APawn* AcknowledgedPawn; // 0x02A8
	PAD(0x10);
	APlayerCameraManager* PlayerCameraManager; // 0x02C0
	PAD(0x2B0);

public:
	void GetViewportSize(int32_t* SizeX, int32_t* SizeY);
	bool IsInputKeyDown(const struct FKey& Key);
	bool ProjectWorldLocationToScreen(const struct FVector& WorldLocation, struct FVector2D* ScreenLocation, bool bPlayerViewportRelative);
};

class UPlayer : public UObject
{
public:
	PAD(0x8);
	APlayerController* PlayerController; // 0x0030
	PAD(0x10);
};

class ULocalPlayer : public UPlayer
{
public:
	PAD(0x28);
	UGameViewportClient* ViewportClient; // 0x0070
	PAD(0x1E0);
};

class UGameInstance : public UObject
{
public:
	PAD(0x10);
	TArray<class ULocalPlayer*> LocalPlayers; // 0x0038
	PAD(0x160);

public:
	ULocalPlayer* GetLocalPlayers();
};

class ULevel : public UObject
{
public:
	PAD(0x70);
	TArray<class AActor*> Actors; // 0x0098
	PAD(0x200);

public:
	int32_t MaxPacket();
};

class UEngine : public UObject
{
public:
	static void FreeMemory(void* AllocatedMemory);
};

class UWorld : public UObject
{
public:
	static inline class UWorld** GWorld = nullptr;

public:
	PAD(0x8);
	ULevel* PersistentLevel; // 0x0030
	PAD(0x148);
	UGameInstance* OwningGameInstance; // 0x0180
	PAD(0x630);

public:
	static UWorld* GetWorld();
	AWorldSettings* GetWorldSettings();
};

class UKismetSystemLibrary : public UObject
{
public:
	bool IsValid(class UObject* Object);
	FString GetObjectName(class UObject* Object);

public:
	static inline UClass* StaticClass()
	{
		static UClass* ptr = nullptr;
		if (!ptr)
			ptr = UObject::FindClass(std::string(skCrypt("Class Engine.KismetSystemLibrary")));
		return ptr;
	}
};

class UKismetMathLibrary : public UObject
{
public:
	float Vector_Distance(const struct FVector& v1, const struct FVector& v2);
	FRotator FindLookAtRotation(const struct FVector& Start, const struct FVector& Target);
	int32_t RandomIntegerInRange(int32_t Min, int32_t Max);

public:
	static inline UClass* StaticClass()
	{
		static UClass* ptr = nullptr;
		if (!ptr)
			ptr = UObject::FindClass(std::string(skCrypt("Class Engine.KismetMathLibrary")));
		return ptr;
	}
};