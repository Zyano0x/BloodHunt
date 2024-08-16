#pragma once

#define M_PI 3.14159265358979323846
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

class Game
{
public:
	explicit Game();
	~Game() noexcept;

	void Hook();
	void UnHook();

	bool Check();
	void Visual();
	void Aimbot();
	void Misc();
	void Radar();

	float CalcHeadCircleRadius(float Distance);
	void LootName(bool Setting, bool Rarity, std::string Name, int Distance, FVector2D Position, ImVec4 Color);
	FVector2D WorldToRadar(FRotator Rotation, FVector Location, FVector EntityLocation, FVector2D RadarCenter, float RadarRadius);
	FRotator CalcAngle(FVector Target);
	FVector CalcPrediction(float BulletVelocity, float BulletGravity, float TargetDistance, FVector TargetPosition, FVector TargetVelocity);
	FVector Prediction(ATigerCharacter* LocalCharacter, ATigerCharacter* TargetCharacter, AWorldSettings* World);
	FVector GetAimWorldLocation(ATigerCharacter* Player);
	ATigerCharacter* GetBestPlayer();
	ImVec4 GetItemRarityColor(ETigerItemRarity Quality);

	int m_ScreenWidth = 0;
	int m_ScreenHeight = 0;

private:
	ImVec4 m_Color{};
	FVector PredictLocation{};
	FVector OriginalLocation{};
	FRotator OriginalRotation{};
	ATigerCharacter* BestPlayer = nullptr;
	ATigerCharacter* LocalCharacter = nullptr;
	APlayerController* LocalPlayerController = nullptr;
	APlayerCameraManager* LocalPlayerCamera = nullptr;
	UKismetSystemLibrary* UKSystemLib = nullptr;
	UKismetMathLibrary* UKMathLib = nullptr;
	UGameplayStatics* UGStatics = nullptr;

private:
	typedef void(*tGetViewPoint)(ULocalPlayer*, FMinimalViewInfo*);
	tGetViewPoint GetViewPoint = nullptr;
	uint64_t GetViewPointAddr = 0;

	typedef void(*tGetPlayerViewPoint)(APlayerController*, FVector*, FRotator*);
	tGetPlayerViewPoint GetPlayerViewPoint = nullptr;
	uint64_t GetPlayerViewPointAddr = 0;

	static void GetViewPointHook(ULocalPlayer* LocalPlayer, FMinimalViewInfo* OutViewInfo);
	static void GetPlayerViewPointHook(APlayerController* PlayerController, FVector* Location, FRotator* Rotation);

	static bool IsValid(UObject* Obj);
};
inline std::unique_ptr<Game> g_Game = std::make_unique<Game>();