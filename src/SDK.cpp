#include "pch.h"

bool InitSDK()
{
	return InitSDK(std::wstring(MODULE_NAME), OBJECTS_OFFSET, NAMES_OFFSET, WORLD_OFFSET);
}

bool InitSDK(const std::wstring& ModuleName, uintptr_t gObjectsOffset, uintptr_t gNamesOffset, uintptr_t gWorldOffset)
{
	auto mBaseAddress = reinterpret_cast<uintptr_t>(GetModuleHandleW(ModuleName.c_str()));
	if (!mBaseAddress)
		return false;

	UObject::GObjects = reinterpret_cast<TUObjectArray*>(mBaseAddress + gObjectsOffset);
	FName::GNames = reinterpret_cast<FNamePool*>(mBaseAddress + gNamesOffset);
	UWorld::GWorld = reinterpret_cast<UWorld**>(mBaseAddress + gWorldOffset);

	return true;
}

float UGameplayStatics::GetWorldDeltaSeconds(const UObject* WorldContextObject)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.GameplayStatics.GetWorldDeltaSeconds")));

	struct UGameplayStatics_GetWorldDeltaSeconds_Params
	{
	public:
		const class UObject* WorldContextObject;                                // 0x0000(0x0008)(ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		float ReturnValue;                                       // 0x0008(0x0004)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		uint8_t Pad_C[0x4];                                        // 0x000C(0x0004)(Fixing Struct Size After Last Property [ Dumper-7 ])
	};

	UGameplayStatics_GetWorldDeltaSeconds_Params params{};
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

float UKismetMathLibrary::Vector_Distance(const FVector& v1, const FVector& v2)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.KismetMathLibrary.Vector_Distance")));

	struct UKismetMathLibrary_Vector_Distance_Params
	{
	public:
		struct FVector v1; // 0x0000(0x000C)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct FVector v2; // 0x000C(0x000C)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		float ReturnValue; // 0x0018(0x0004)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	UKismetMathLibrary_Vector_Distance_Params params{};
	params.v1 = v1;
	params.v2 = v2;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FRotator UKismetMathLibrary::FindLookAtRotation(const FVector& Start, const FVector& Target)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.KismetMathLibrary.FindLookAtRotation")));

	struct UKismetMathLibrary_FindLookAtRotation_Params
	{
	public:
		struct FVector Start; // 0x0000(0x000C)  (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct FVector Target; // 0x000C(0x000C)  (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct FRotator ReturnValue; // 0x0018(0x000C)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	};

	UKismetMathLibrary_FindLookAtRotation_Params params{};
	params.Start = Start;
	params.Target = Target;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FRotator UKismetMathLibrary::RInterpTo(const FRotator& Current, const FRotator& Target, float DeltaTime, float InterpSpeed)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.KismetMathLibrary.RInterpTo")));

	struct UKismetMathLibrary_RInterpTo_Params
	{
	public:
		struct FRotator                               Current;                                           // 0x0000(0x000C)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
		struct FRotator                               Target;                                            // 0x000C(0x000C)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
		float                                         DeltaTime;                                         // 0x0018(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		float                                         InterpSpeed;                                       // 0x001C(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct FRotator                               ReturnValue;                                       // 0x0020(0x000C)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	};

	UKismetMathLibrary_RInterpTo_Params params{};
	params.Current = std::move(Current);
	params.Target = std::move(Target);
	params.DeltaTime = DeltaTime;
	params.InterpSpeed = InterpSpeed;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

int32_t UKismetMathLibrary::RandomIntegerInRange(int32_t Min, int32_t Max)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.KismetMathLibrary.RandomIntegerInRange")));

	struct UKismetMathLibrary_RandomIntegerInRange_Params
	{
	public:
		int32_t Min; // 0x0000(0x0004)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		int32_t Max; // 0x0004(0x0004)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		int32_t ReturnValue; // 0x0008(0x0004)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	UKismetMathLibrary_RandomIntegerInRange_Params params{};
	params.Min = Min;
	params.Max = Max;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

bool UKismetSystemLibrary::IsValid(UObject* Object)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.KismetSystemLibrary.IsValid")));

	struct UKismetSystemLibrary_IsValid_Params
	{
	public:
		class UObject* Object; // 0x0000(0x0008)  (ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool ReturnValue; // 0x0008(0x0001)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	UKismetSystemLibrary_IsValid_Params params{};
	params.Object = Object;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FString UKismetSystemLibrary::GetObjectName(UObject* Object)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.KismetSystemLibrary.GetObjectName")));

	struct UKismetSystemLibrary_GetObjectName_Params
	{
	public:
		class UObject* Object; // 0x0000(0x0008)  (ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		class FString ReturnValue; // 0x0008(0x0010)  (Parm, OutParm, ZeroConstructor, ReturnParm, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	UKismetSystemLibrary_GetObjectName_Params params{};
	params.Object = Object;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

UWorld* UWorld::GetWorld()
{
	if (!GWorld)
		return nullptr;
	else
		return *GWorld;
}

AWorldSettings* UWorld::GetWorldSettings()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.World.K2_GetWorldSettings")));

	struct World_K2_GetWorldSettings
	{
	public:
		class AWorldSettings* ReturnValue; // 0x0000(0x0008)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	World_K2_GetWorldSettings params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

void UEngine::FreeMemory(void* AllocatedMemory)
{
	static uint64_t FreeMemoryAddress = 0;
	if (!FreeMemoryAddress) {
		FreeMemoryAddress = Signature(std::string(skCrypt("48 85 C9 74 ? 53 48 83 EC ? 48 8B D9 48 8B 0D"))).GetPointer();
		if (!FreeMemoryAddress)
			return;
	}

	reinterpret_cast<void(__fastcall*)(void*)>(FreeMemoryAddress)(AllocatedMemory);
}

int32_t ULevel::MaxPacket()
{
	if (!this)
		return 0;

	return *reinterpret_cast<int32_t*>(reinterpret_cast<uint64_t>(this) + 0xA0);
}

ULocalPlayer* UGameInstance::GetLocalPlayers()
{
	if (!this)
		return nullptr;

	uint64_t LocalPlayerArray = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint64_t>(this) + 0x38);
	if (!LocalPlayerArray)
		return nullptr;

	return *reinterpret_cast<ULocalPlayer**>(LocalPlayerArray);
}

void APlayerController::GetViewportSize(int32_t* SizeX, int32_t* SizeY)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.PlayerController.GetViewportSize")));

	struct APlayerController_GetViewportSize_Params
	{
	public:
		int32_t SizeX; // 0x0000(0x0004)  (Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		int32_t SizeY; // 0x0004(0x0004)  (Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	APlayerController_GetViewportSize_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	if (SizeX != nullptr)
		*SizeX = params.SizeX;
	if (SizeY != nullptr)
		*SizeY = params.SizeY;
}

bool APlayerController::IsInputKeyDown(const FKey& Key)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.PlayerController.IsInputKeyDown")));

	struct APlayerController_IsInputKeyDown_Params
	{
	public:
		struct FKey Key; // 0x0000(0x0018)  (Parm, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool ReturnValue; // 0x0018(0x0001)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	APlayerController_IsInputKeyDown_Params params{};
	params.Key = Key;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

bool APlayerController::ProjectWorldLocationToScreen(const FVector& WorldLocation, FVector2D* ScreenLocation, bool bPlayerViewportRelative)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.PlayerController.ProjectWorldLocationToScreen")));

	struct APlayerController_ProjectWorldLocationToScreen_Params
	{
	public:
		struct FVector WorldLocation; // 0x0000(0x000C)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct FVector2D ScreenLocation; // 0x000C(0x0008)  (Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool bPlayerViewportRelative; // 0x0014(0x0001)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool ReturnValue; // 0x0015(0x0001)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	APlayerController_ProjectWorldLocationToScreen_Params params{};
	params.WorldLocation = WorldLocation;
	params.bPlayerViewportRelative = bPlayerViewportRelative;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	if (ScreenLocation != nullptr)
		*ScreenLocation = params.ScreenLocation;

	return params.ReturnValue;
}

void AController::SetControlRotation(const FRotator& NewRotation)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.Controller.SetControlRotation")));

	struct AController_SetControlRotation_Params
	{
	public:
		struct FRotator NewRotation; // 0x0000(0x000C)  (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	};

	AController_SetControlRotation_Params params{};
	params.NewRotation = NewRotation;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;
}

APawn* AController::GetPawn()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.Controller.K2_GetPawn")));

	struct AController_K2_GetPawn_Params
	{
	public:
		class APawn* ReturnValue; // 0x0000(0x0008)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	AController_K2_GetPawn_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

bool AController::LineOfSightTo(AActor* Other, const FVector& ViewPoint, bool bAlternateChecks)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.Controller.LineOfSightTo")));

	struct AController_LineOfSightTo_Params
	{
	public:
		class AActor* Other; // 0x0000(0x0008)  (ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct FVector ViewPoint; // 0x0008(0x000C)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool bAlternateChecks; // 0x0014(0x0001)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool ReturnValue; // 0x0015(0x0001)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	AController_LineOfSightTo_Params params{};
	params.Other = Other;
	params.ViewPoint = ViewPoint;
	params.bAlternateChecks = bAlternateChecks;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

float ATigerCharacter::GetCurrentHealth()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerCharacter.GetCurrentHealth")));

	struct ATigerCharacter_GetCurrentHealth_Params
	{
	public:
		float ReturnValue; // 0x0000(0x0004)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	ATigerCharacter_GetCurrentHealth_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

float ATigerCharacter::GetCurrentShield()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerCharacter.GetCurrentShield")));

	struct ATigerCharacter_GetCurrentShield_Params
	{
	public:
		float ReturnValue; // 0x0000(0x0004)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	ATigerCharacter_GetCurrentShield_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

float ATigerCharacter::GetMaxHealth()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerCharacter.GetMaxHealth")));

	struct ATigerCharacter_GetMaxHealth_Params
	{
	public:
		float ReturnValue; // 0x0000(0x0004)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	ATigerCharacter_GetMaxHealth_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

float ATigerCharacter::GetMaxShield()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerCharacter.GetMaxShield")));

	struct ATigerCharacter_GetMaxShield_Params
	{
	public:
		float ReturnValue; // 0x0000(0x0004)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	ATigerCharacter_GetMaxShield_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

bool ATigerCharacter::IsDead()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerCharacter.IsDead")));

	struct ATigerCharacter_IsDead_Params
	{
	public:
		bool ReturnValue; // 0x0000(0x0001)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	ATigerCharacter_IsDead_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

bool ATigerCharacter::IsDowned()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerCharacter.IsDowned")));

	struct ATigerCharacter_IsDowned_Params
	{
	public:
		bool ReturnValue; // 0x0000(0x0001)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	ATigerCharacter_IsDowned_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

bool ATigerCharacter::IsFriendlyWith(const ATigerCharacter* OtherCharacter)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerCharacter.IsFriendlyWith")));

	struct TigerCharacter_IsFriendlyWith
	{
	public:
		const class ATigerCharacter* OtherCharacter; // 0x0000(0x0008)(ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool ReturnValue; // 0x0008(0x0001)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		uint8_t Pad_9[0x7]; // 0x0009(0x0007)(Fixing Struct Size After Last Property [ Dumper-7 ])
	};

	TigerCharacter_IsFriendlyWith params{};
	params.OtherCharacter = OtherCharacter;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FVector APlayerCameraManager::GetCameraLocation()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.PlayerCameraManager.GetCameraLocation")));

	struct APlayerCameraManager_GetCameraLocation_Params
	{
	public:
		struct FVector ReturnValue; // 0x0000(0x000C)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	APlayerCameraManager_GetCameraLocation_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FRotator APlayerCameraManager::GetCameraRotation()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.PlayerCameraManager.GetCameraRotation")));

	struct APlayerCameraManager_GetCameraRotation_Params
	{
	public:
		struct FRotator ReturnValue; // 0x0000(0x000C)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	};

	APlayerCameraManager_GetCameraRotation_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FString APlayerState::GetPlayerName()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.PlayerState.GetPlayerName")));

	struct APlayerState_GetPlayerName_Params
	{
	public:
		class FString ReturnValue; // 0x0000(0x0010)  (Parm, OutParm, ZeroConstructor, ReturnParm, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	APlayerState_GetPlayerName_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

bool APlayerState::IsOfSameTeam(APlayerState* OtherState)
{
	static uint64_t IsOfSameTeamAddress = NULL;
	if (IsOfSameTeamAddress == NULL) {
		IsOfSameTeamAddress = Signature(std::string(skCrypt("40 53 48 83 EC ? 48 8B DA 48 85 D2 75 ? 32 C0"))).GetPointer();

		if (IsOfSameTeamAddress == NULL)
			return false;
	}

	return reinterpret_cast<bool(__fastcall*)(APlayerState*, APlayerState*)>(IsOfSameTeamAddress)(this, OtherState);
}

void AActor::GetActorBounds(bool bOnlyCollidingComponents, FVector* Origin, FVector* BoxExtent, bool bIncludeFromChildActors)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.Actor.GetActorBounds")));

	struct AActor_GetActorBounds_Params
	{
	public:
		bool bOnlyCollidingComponents; // 0x0000(0x0001)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		unsigned char UnknownData_LVOC[0x3]; // 0x0001(0x0003) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY) ()
		struct FVector Origin; // 0x0004(0x000C)  (Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct FVector BoxExtent; // 0x0010(0x000C)  (Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool bIncludeFromChildActors; // 0x001C(0x0001)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	AActor_GetActorBounds_Params params{};
	params.bOnlyCollidingComponents = bOnlyCollidingComponents;
	params.bIncludeFromChildActors = bIncludeFromChildActors;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	if (Origin != nullptr)
		*Origin = params.Origin;
	if (BoxExtent != nullptr)
		*BoxExtent = params.BoxExtent;
}

float AActor::GetDistanceTo(AActor* OtherActor)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.Actor.GetDistanceTo")));

	struct AActor_GetDistanceTo_Params
	{
	public:
		class AActor* OtherActor; // 0x0000(0x0008)  (ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		float ReturnValue; // 0x0008(0x0004)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	AActor_GetDistanceTo_Params params{};
	params.OtherActor = OtherActor;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FVector AActor::GetActorLocation()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.Actor.K2_GetActorLocation")));

	struct AActor_K2_GetActorLocation_Params
	{
	public:
		struct FVector ReturnValue; // 0x0000(0x000C)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	AActor_K2_GetActorLocation_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FRotator AActor::GetActorRotation()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.Actor.K2_GetActorRotation")));

	struct AActor_K2_GetActorRotation_Params
	{
	public:
		struct FRotator ReturnValue; // 0x0000(0x000C)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	};

	AActor_K2_GetActorRotation_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

USceneComponent* AActor::GetRootComponent()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.Actor.K2_GetRootComponent")));

	struct AActor_K2_GetRootComponent_Params
	{
	public:
		class USceneComponent* ReturnValue; // 0x0000(0x0008)  (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	AActor_K2_GetRootComponent_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FTigerFireSettings UTigerRangedWeaponComponent::GetCurrentFireSettings()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerRangedWeaponComponent.GetCurrentFireSettings")));

	struct UTigerRangedWeaponComponent_GetCurrentFireSettings_Params
	{
	public:
		struct FTigerFireSettings ReturnValue; // 0x0000(0x00D8)  (ConstParm, Parm, OutParm, ReturnParm, ReferenceParm, NoDestructor, NativeAccessSpecifierPublic)
	};

	UTigerRangedWeaponComponent_GetCurrentFireSettings_Params params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

ATigerProjectile* UTigerRangedWeaponComponent::GetCurrentProjectileType()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerRangedWeaponComponent.GetCurrentProjectileType")));

	struct TigerRangedWeaponComponent_GetCurrentProjectileType
	{
	public:
		class ATigerProjectile* ReturnValue; // 0x0000(0x0008)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	TigerRangedWeaponComponent_GetCurrentProjectileType params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

UTigerRangedWeapon* UTigerRangedWeaponComponent::GetEquippedOrWantedWeapon()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerRangedWeaponComponent.GetEquippedOrWantedWeapon")));

	struct TigerRangedWeaponComponent_GetEquippedOrWantedWeapon
	{
	public:
		class UTigerRangedWeapon* ReturnValue; // 0x0000(0x0008)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	TigerRangedWeaponComponent_GetEquippedOrWantedWeapon params{};

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

void UTigerOutlineComponent::DeactivateOutline(ETigerOutlineMode InMode)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerOutlineComponent.DeactivateOutline")));

	struct UTigerOutlineComponent_DeactivateOutline_Params
	{
	public:
		ETigerOutlineMode InMode; // 0x0000(0x0001)  (ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	UTigerOutlineComponent_DeactivateOutline_Params params{};
	params.InMode = InMode;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;
}

void UTigerOutlineComponent::ActivateOutline(ETigerOutlineMode InMode)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerOutlineComponent.ActivateOutline")));

	struct UTigerOutlineComponent_ActivateOutline_Params
	{
	public:
		ETigerOutlineMode InMode; // 0x0000(0x0001)  (ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	UTigerOutlineComponent_ActivateOutline_Params params{};
	params.InMode = InMode;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;
}

bool UTigerOutlineComponent::IsOutlineActivated(const ETigerOutlineMode InMode)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Tiger.TigerOutlineComponent.IsOutlineActivated")));

	struct TigerOutlineComponent_IsOutlineActivated
	{
	public:
		ETigerOutlineMode InMode; // 0x0000(0x0001)(ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		bool ReturnValue; // 0x0001(0x0001)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	TigerOutlineComponent_IsOutlineActivated params{};
	params.InMode = InMode;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FName USkinnedMeshComponent::GetBoneName(int32_t BoneIndex)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.SkinnedMeshComponent.GetBoneName")));

	struct USkinnedMeshComponent_GetBoneName_Params
	{
	public:
		int32_t BoneIndex; // 0x0000(0x0004)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		class FName ReturnValue; // 0x0004(0x0008)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	USkinnedMeshComponent_GetBoneName_Params params{};
	params.BoneIndex = BoneIndex;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

int32_t USkinnedMeshComponent::GetBoneIndex(const FName& BoneName)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.SkinnedMeshComponent.GetBoneIndex")));

	struct USkinnedMeshComponent_GetBoneIndex_Params
	{
	public:
		class FName BoneName; // 0x0000(0x0008)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		int32_t ReturnValue; // 0x0008(0x0004)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	USkinnedMeshComponent_GetBoneIndex_Params params{};
	params.BoneName = BoneName;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FVector USceneComponent::GetSocketLocation(const FName& InSocketName)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>(std::string(skCrypt("Function Engine.SceneComponent.GetSocketLocation")));

	struct USceneComponent_GetSocketLocation_Params
	{
	public:
		class FName InSocketName; // 0x0000(0x0008)  (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct FVector ReturnValue; // 0x0008(0x000C)  (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	USceneComponent_GetSocketLocation_Params params{};
	params.InSocketName = InSocketName;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}