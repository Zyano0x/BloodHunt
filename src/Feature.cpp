#include "pch.h"

Game::Game() {}

Game::~Game() {}

void __fastcall Game::GetViewPointHook(ULocalPlayer* LocalPlayer, FMinimalViewInfo* OutViewInfo)
{
	g_Game->GetViewPoint(LocalPlayer, OutViewInfo);
	if (Settings[AIM_MODE].Value.iValue == 1 && Settings[AIM_ENABLED].Value.bValue) {
		if (g_Game->BestPlayer) {
			if (GetKeyPress(VK_LBUTTON, true) && g_Game->PredictLocation.IsValid()) {
				OutViewInfo->Location = g_Game->OriginalLocation;
				OutViewInfo->Rotation = g_Game->OriginalRotation;
			}
		}
	}
}

void __fastcall Game::GetPlayerViewPointHook(APlayerController* PlayerController, FVector* Location, FRotator* Rotation)
{
	g_Game->GetPlayerViewPoint(PlayerController, Location, Rotation);
	g_Game->OriginalLocation = *Location;
	g_Game->OriginalRotation = *Rotation;

	if (Settings[AIM_MODE].Value.iValue == 1 && Settings[AIM_ENABLED].Value.bValue) {
		if (g_Game->BestPlayer) {
			if (GetKeyPress(VK_LBUTTON, true) && g_Game->PredictLocation.IsValid()) {
				FRotator AimRotation = g_Game->CalcAngle(g_Game->PredictLocation);
				*Rotation = AimRotation;
			}
		}
	}
}

bool Game::IsValid(UObject* Obj)
{
	return Obj && g_Game->UKSystemLib->IsValid(Obj);
}

void Game::Hook()
{
	VIRTUALIZER_TIGER_LONDON_START;
	InitSDK();

	UKSystemLib = reinterpret_cast<UKismetSystemLibrary*>(UKismetSystemLibrary::StaticClass());
	UKMathLib = reinterpret_cast<UKismetMathLibrary*>(UKismetMathLibrary::StaticClass());

	GetViewPointAddr = Signature("4C 8B DC 49 89 5B ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 41 0F 29 73").GetPointer();
	GetPlayerViewPointAddr = Signature("48 89 5C 24 ? 48 89 74 24 ? 55 41 56 41 57 48 8B EC 48 83 EC ? 48 8B F2").GetPointer();

	if (GetViewPointAddr && GetPlayerViewPointAddr) {
		Hooking::CreateHook(reinterpret_cast<LPVOID>(GetViewPointAddr), &GetViewPointHook, reinterpret_cast<LPVOID*>(&GetViewPoint));
		Hooking::CreateHook(reinterpret_cast<LPVOID>(GetPlayerViewPointAddr), &GetPlayerViewPointHook, reinterpret_cast<LPVOID*>(&GetPlayerViewPoint));
	}
	VIRTUALIZER_TIGER_LONDON_END;
}

void Game::UnHook()
{
	VIRTUALIZER_TIGER_LONDON_START;
	Hooking::DisableHook(reinterpret_cast<LPVOID>(GetViewPointAddr));
	Hooking::DisableHook(reinterpret_cast<LPVOID>(GetPlayerViewPointAddr));
	VIRTUALIZER_TIGER_LONDON_END;
}

bool Game::Check()
{
	VIRTUALIZER_TIGER_LONDON_START;
	UWorld* World = UWorld::GetWorld();
	if (!IsValid(World))
		return false;

	UGameInstance* GameInstance = World->OwningGameInstance;
	if (!IsValid(GameInstance))
		return false;

	ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayers();
	if (!IsValid(LocalPlayer))
		return false;

	LocalPlayerController = LocalPlayer->PlayerController;
	if (!IsValid(LocalPlayerController))
		return false;

	LocalPlayerCamera = LocalPlayerController->PlayerCameraManager;
	if (!IsValid(LocalPlayerCamera))
		return false;

	LocalCharacter = static_cast<ATigerCharacter*>(LocalPlayerController->AcknowledgedPawn);
	if (!IsValid(LocalCharacter))
		return false;

	LocalPlayerController->GetViewportSize(&m_ScreenWidth, &m_ScreenHeight);
	VIRTUALIZER_TIGER_LONDON_END;
	return true;
}

void Game::Visual()
{
	if (!Check())
		return;

	UWorld* GWorld = UWorld::GetWorld();
	if (!IsValid(GWorld))
		return;

	std::vector<ATigerCharacter*> Players{};
	std::vector<ATigerItemWorldRepresentation*> Items{};
	int32_t Count = GWorld->PersistentLevel->MaxPacket();
	TArray<AActor*> Actors = GWorld->PersistentLevel->Actors;
	for (int i = 0; i < Count; ++i) {
		AActor* Actor = Actors[i];
		if (!Actor)
			continue;

		FString ObjectName = UKSystemLib->GetObjectName(Actor);
		if (!ObjectName.IsValid())
			continue;

		if (Actor->IsA(ATigerCharacter::StaticClass())) {
			Players.push_back(static_cast<ATigerCharacter*>(Actor));
		}

		if (wcsstr(ObjectName.wc_str(), skCrypt(L"TBP_Item_C"))) {
			Items.push_back(static_cast<ATigerItemWorldRepresentation*>(Actor));
		}

		UEngine::FreeMemory(ObjectName.Data());
	}

	for (ATigerCharacter* Player : Players) {
		if (!Settings[ESP_ENABLED].Value.bValue)
			return;

		if (!IsValid(Player))
			return;

		USkeletalMeshComponent* MeshComponent = Player->Mesh;
		if (!IsValid(MeshComponent))
			continue;

		APlayerState* PlayerState = Player->PlayerState;
		if (!IsValid(PlayerState))
			continue;

		if (Player == LocalCharacter)
			continue;

		if (Player->CharacterType == ETigerCharacterType::Npc || Player->CharacterType == ETigerCharacterType::TargetDummy || Player->CharacterType == ETigerCharacterType::TutorialTrainer)
			continue;

		if (Player->IsDead())
			continue;

		FVector Location, Extend;
		Player->GetActorBounds(true, &Location, &Extend, false);

		bool IsTeammate = Player->IsFriendlyWith(LocalCharacter);

		bool ShowEnemy = !IsTeammate && Settings[ESP_ENEMY].Value.bValue;
		bool ShowFriendly = IsTeammate && Settings[ESP_FRIENDLY].Value.bValue;

		if (!(ShowEnemy || ShowFriendly))
			continue;

		if (ShowEnemy) {
			if (LocalPlayerController->LineOfSightTo(Player, { 0.0f, 0.0f, 0.0f }, false))
				VEC4CPY(Settings[ESP_VISIBLE_COLOR].Value.v4Value, m_Color);
			else
				VEC4CPY(Settings[ESP_ENEMY_COLOR].Value.v4Value, m_Color);
		}
		else if (ShowFriendly) {
			VEC4CPY(Settings[ESP_FRIENDLY_COLOR].Value.v4Value, m_Color);
		}

		FVector2D HeadPos, FootPos;
		if (LocalPlayerController->ProjectWorldLocationToScreen({ Location.X, Location.Y, Location.Z - Extend.Z }, &FootPos, false)
			&& LocalPlayerController->ProjectWorldLocationToScreen({ Location.X, Location.Y, Location.Z + Extend.Z }, &HeadPos, false)) {
			const float Distance = Player->GetDistanceTo(LocalCharacter) / 100.0f;
			const float H = FootPos.Y - HeadPos.Y;
			const float W = H / 2.0f;
			const float X = HeadPos.X - W * 0.5f;
			const float Y = HeadPos.Y;

			if (Settings[ESP_NAME].Value.bValue) {
				if (Player->CharacterType == ETigerCharacterType::PlayerBot) {
					Draw::DrawString(ImGui::GetIO().FontDefault, std::string(skCrypt("BOT")), (X + (HeadPos.X + W * 0.5f)) / 2, Y - 20, 15.0f, true, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
				}
				else if (Player->CharacterType == ETigerCharacterType::Player) {
					FString PlayerName = PlayerState->GetPlayerName();
					if (PlayerName.IsValid()) {
						Draw::DrawString(ImGui::GetIO().FontDefault, PlayerName.ToString(), (X + (HeadPos.X + W * 0.5f)) / 2, Y - 20, 15.0f, true, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
					}
					UEngine::FreeMemory(PlayerName.Data());
				}
			}

			if (Settings[ESP_SKELETON].Value.bValue) {
				std::vector<std::pair<const char*, const char*>> SkeletonConnections = {
					{ skCrypt("neck_01"), skCrypt("Head") },

					{ skCrypt("Spine_02"), skCrypt("neck_01") },
					{ skCrypt("Spine_01"), skCrypt("Spine_02") },
					{ skCrypt("spine_03"), skCrypt("Spine_01") },
					{ skCrypt("pelvis"), skCrypt("spine_03") },

					{ skCrypt("clavicle_r"), skCrypt("Spine_02") },
					{ skCrypt("upperarm_r"), skCrypt("clavicle_r") },
					{ skCrypt("lowerarm_r"), skCrypt("upperarm_r") },
					{ skCrypt("hand_r"), skCrypt("lowerarm_r") },

					{ skCrypt("clavicle_l"), skCrypt("Spine_02") },
					{ skCrypt("upperarm_l"), skCrypt("clavicle_l") },
					{ skCrypt("lowerarm_l"), skCrypt("upperarm_l") },
					{ skCrypt("hand_l"), skCrypt("lowerarm_l") },

					{ skCrypt("calf_r"), skCrypt("pelvis") },
					{ skCrypt("foot_r"), skCrypt("calf_r") },

					{ skCrypt("calf_l"), skCrypt("pelvis") },
					{ skCrypt("foot_l"), skCrypt("calf_l") },
				};

				FVector2D BoneScreen, PrevBoneScreen, HeadScreen;
				for (const std::pair<const char*, const char*>& Connection : SkeletonConnections) {
					auto BONE1 = Connection.first;
					auto BONE2 = Connection.second;

					FVector BoneLoc1 = MeshComponent->GetSocketLocation(MeshComponent->GetBoneName(MeshComponent->GetBoneIndex(FName(BONE1))));
					FVector BoneLoc2 = MeshComponent->GetSocketLocation(MeshComponent->GetBoneName(MeshComponent->GetBoneIndex(FName(BONE2))));

					LocalPlayerController->ProjectWorldLocationToScreen(BoneLoc1, &BoneScreen, false);
					LocalPlayerController->ProjectWorldLocationToScreen(BoneLoc2, &PrevBoneScreen, false);

					if (BoneScreen.IsValid() && PrevBoneScreen.IsValid())
						Draw::DrawLine(BoneScreen.X, BoneScreen.Y, PrevBoneScreen.X, PrevBoneScreen.Y, 1.6f, m_Color);
				}

				float HeadCircleRadius = CalcHeadCircleRadius(Distance);
				FVector Head = MeshComponent->GetSocketLocation(MeshComponent->GetBoneName(MeshComponent->GetBoneIndex(FName(skCrypt("Head")))));
				LocalPlayerController->ProjectWorldLocationToScreen(Head, &HeadScreen, false);

				if (HeadScreen.IsValid())
					Draw::DrawCircleFilled(HeadScreen.X, HeadScreen.Y - 2.5f, HeadCircleRadius, m_Color);
			}

			if (Settings[ESP_SNAP_LINES].Value.bValue) {
				Draw::DrawLine(m_ScreenWidth / 2, m_ScreenHeight, (X + ((HeadPos.X + W * 0.5f))) / 2, FootPos.Y, 1.5f, m_Color);
			}

			if (Settings[ESP_DISTANCE].Value.bValue && !Settings[ESP_WEAPON].Value.bValue) {
				Draw::DrawString(ImGui::GetIO().FontDefault, std::to_string((int)Distance).append(std::string(skCrypt(" M "))), (X + (HeadPos.X + W * 0.5f)) / 2, FootPos.Y + 5, 15.f, true, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (!Settings[ESP_DISTANCE].Value.bValue && Settings[ESP_WEAPON].Value.bValue) {
				std::string WeaponName = std::string(skCrypt("----"));
				UTigerRangedWeaponComponent* WeaponComponent = Player->RangedWeaponComponent;
				if (IsValid(WeaponComponent)) {
					UTigerRangedWeapon* EquippedWeapon = WeaponComponent->GetEquippedOrWantedWeapon();
					if (IsValid(EquippedWeapon)) {
						WeaponName = EquippedWeapon->WeaponName.GetName();
					}
				}
				Draw::DrawString(ImGui::GetIO().FontDefault, WeaponName, (X + (HeadPos.X + W * 0.5f)) / 2, FootPos.Y + 5, 15.f, true, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (Settings[ESP_DISTANCE].Value.bValue && Settings[ESP_WEAPON].Value.bValue) {
				std::string WeaponName = std::string(skCrypt("----"));
				UTigerRangedWeaponComponent* WeaponComponent = Player->RangedWeaponComponent;
				if (IsValid(WeaponComponent)) {
					UTigerRangedWeapon* EquippedWeapon = WeaponComponent->GetEquippedOrWantedWeapon();
					if (IsValid(EquippedWeapon)) {
						WeaponName = EquippedWeapon->WeaponName.GetName();
					}
				}
				Draw::DrawString(ImGui::GetIO().FontDefault, WeaponName, (X + (HeadPos.X + W * 0.5f)) / 2, FootPos.Y + 5, 15.f, true, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
				Draw::DrawString(ImGui::GetIO().FontDefault, std::to_string((int)Distance).append(std::string(skCrypt(" M "))), (X + (HeadPos.X + W * 0.5f)) / 2, FootPos.Y + 20, 15.f, true, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
			}

			if (Settings[ESP_HEALTH].Value.bValue) {
				if (!Player->IsDowned()) {
					float Health = Player->GetCurrentHealth();
					float MaxHealth = Player->GetMaxHealth();
					float Percent = Health * 100.0f / MaxHealth;

					float HWidth = W / 10;
					if (HWidth < 2.0f)
						HWidth = 2.0f;
					if (HWidth > 3.0f)
						HWidth = 3.0f;

					Draw::VerticalHealthBar(HeadPos.X - (W / 2.0f) - 4.0f, HeadPos.Y, HWidth, FootPos.Y - HeadPos.Y, (int)Percent, true, BarType::Health);
				}
			}

			if (Settings[ESP_ARMOR].Value.bValue) {
				if (!Player->IsDowned()) {
					float Shield = Player->GetCurrentShield();
					float MaxShield = Player->GetMaxShield();
					float Percent = Shield * 100.0f / MaxShield;

					float HWidth = W / 10;
					if (HWidth < 2.0f)
						HWidth = 2.0f;
					if (HWidth > 3.0f)
						HWidth = 3.0f;

					if (Shield != 0 && MaxShield != 0) {
						Draw::VerticalHealthBar(HeadPos.X + (W / 2.0f) + 4.0f, HeadPos.Y, HWidth, FootPos.Y - HeadPos.Y, Percent, true, BarType::Shield);
					}
				}
			}

			if (Settings[ESP_GLOW].Value.bValue) {
				UTigerOutlineComponent* OutlineComponent = Player->OutlineComponent;
				if (!IsValid(OutlineComponent))
					continue;

				OutlineComponent->CurrentMode = ETigerOutlineMode::BloodHunted;
				OutlineComponent->ActivateOutline(ETigerOutlineMode::HeightenedSenses);
				OutlineComponent->ActivateOutline(ETigerOutlineMode::BloodHunted);
			}

			if (Settings[ESP_BOX].Value.iValue) {
				if (!Player->IsDowned()) {
					switch (Settings[ESP_BOX].Value.iValue) {
					case 1:
						Draw::DrawBoxOutline(X, Y, W, H, false, m_Color);
						break;
					case 2:
						Draw::DrawBoxOutline(X, Y, W, H, true, m_Color);
						break;
					case 3:
						Draw::DrawCornersBoxOutline(X, Y, W, H, false, m_Color);
						break;
					case 4:
						Draw::DrawCornersBoxOutline(X, Y, W, H, true, m_Color);
						break;
					}
				}
			}
		}
	}

	for (ATigerItemWorldRepresentation* Item : Items) {
		if (!Settings[ESP_LOOT].Value.bValue)
			return;

		if (!IsValid(Item))
			return;

		UTigerItemAsset* ItemType = Item->ItemType;
		if (!IsValid(ItemType))
			continue;

		FVector Location = Item->GetActorLocation();
		if (!Location.IsValid())
			continue;

		FVector2D Position;
		LocalPlayerController->ProjectWorldLocationToScreen(Location, &Position, false);
		if (Position.IsValid()) {
			const float Distance = Item->GetDistanceTo(LocalCharacter) / 100.0f;
			ETigerInventoryItemType LootType = ItemType->ItemType;
			ETigerItemRarity LootRarity = ItemType->ItemRarity;
			ImVec4 RarityColor = GetItemRarityColor(LootRarity);
			std::string Name = ItemType->Name.ToString();

			if (LootType == ETigerInventoryItemType::TigerInventoryItem_Firearm) {
				LootName(Settings[ESP_FIREARM].Value.bValue, static_cast<uint8_t>(LootRarity) >= Settings[ESP_LOOT_LEVEL].Value.iValue, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_Melee) {
				LootName(Settings[ESP_MELEE].Value.bValue, static_cast<uint8_t>(LootRarity) >= Settings[ESP_LOOT_LEVEL].Value.iValue, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_Unarmed) {
				LootName(Settings[ESP_UNARMED].Value.bValue, true, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_Amulet) {
				LootName(Settings[ESP_AMULET].Value.bValue, true, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_Artifact) {
				LootName(Settings[ESP_ARTIFACT].Value.bValue, true, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_BodyArmor) {
				LootName(Settings[ESP_BODYARMOR].Value.bValue, true, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_Relic) {
				LootName(Settings[ESP_RELIC].Value.bValue, true, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_Ammo) {
				LootName(Settings[ESP_AMMO].Value.bValue, true, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_CombinedAmmo) {
				LootName(Settings[ESP_COMBINED_AMMO].Value.bValue, true, Name, Distance, Position, RarityColor);
			}
			else if (LootType == ETigerInventoryItemType::TigerInventoryItem_Consumable) {
				LootName(Settings[ESP_CONSUMABLE].Value.bValue, true, Name, Distance, Position, RarityColor);
			}
		}
	}
}

void Game::Aimbot()
{
	VIRTUALIZER_TIGER_LITE_START;
	if (!Settings[AIM_ENABLED].Value.bValue)
		return;

	if (!Check())
		return;

	UWorld* GWorld = UWorld::GetWorld();
	if (!IsValid(GWorld))
		return;

	AWorldSettings* WorldSettings = GWorld->GetWorldSettings();
	if (!IsValid(WorldSettings))
		return;

	if (Settings[FOV].Value.bValue)
		Draw::DrawCircle(m_ScreenWidth / 2, m_ScreenHeight / 2, Settings[FOV_RADIUS].Value.fValue, Settings[FOV_COLOR].Value.v4Value);

	BestPlayer = g_Game->GetBestPlayer();
	if (!IsValid(BestPlayer))
		return;

	PredictLocation = g_Game->Prediction(LocalCharacter, BestPlayer, WorldSettings);
	if (!PredictLocation.IsValid())
		return;

	FRotator NewRotation = g_Game->CalcAngle(LocalPlayerCamera->GetCameraLocation(), PredictLocation, LocalPlayerCamera->GetCameraRotation(), Settings[AIM_SMOOTH].Value.fValue);

	if (Settings[AIM_MODE].Value.iValue == 0) {
		if (GetKeyPress(VK_LBUTTON, true)) {
			LocalPlayerController->SetControlRotation(NewRotation);
		}
	}
	VIRTUALIZER_TIGER_LITE_END;
}

void Game::Misc()
{
	VIRTUALIZER_TIGER_LITE_START;
	if (!Check())
		return;

	UTigerRangedWeaponComponent* RangedWeaponComponent = LocalCharacter->RangedWeaponComponent;
	if (!IsValid(RangedWeaponComponent))
		return;

	UTigerRangedWeapon* EquippedWeapon = RangedWeaponComponent->GetEquippedOrWantedWeapon();
	if (!IsValid(EquippedWeapon))
		return;

	if (Settings[NO_RECOIL].Value.bValue) {
		EquippedWeapon->VerticalRecoilCurve = nullptr;
		EquippedWeapon->HorizontalRecoilCurve = nullptr;
	}
	VIRTUALIZER_TIGER_LITE_END;
}

void Game::Radar()
{
	if (!Settings[ESP_RADAR].Value.bValue)
		return;

	if (!Check())
		return;

	UWorld* GWorld = UWorld::GetWorld();
	if (!UKSystemLib->IsValid(GWorld))
		return;

	FVector2D RadarCenter = FVector2D(m_ScreenWidth - Settings[ESP_RADAR_X].Value.fValue, m_ScreenHeight - Settings[ESP_RADAR_Y].Value.fValue);
	int32_t Count = GWorld->PersistentLevel->MaxPacket();
	TArray<AActor*> Actors = GWorld->PersistentLevel->Actors;
	for (int i = 0; i < Count; i++) {
		AActor* Actor = Actors[i];
		if (!Actor)
			continue;

		if (Actor->IsA(ATigerCharacter::StaticClass())) {
			ATigerCharacter* Player = static_cast<ATigerCharacter*>(Actor);
			if (!IsValid(Player))
				continue;

			USkeletalMeshComponent* MeshComponent = Player->Mesh;
			if (!IsValid(MeshComponent))
				continue;

			if (Player == LocalCharacter)
				continue;

			if (Player->CharacterType == ETigerCharacterType::Npc || Player->CharacterType == ETigerCharacterType::TargetDummy || Player->CharacterType == ETigerCharacterType::TutorialTrainer)
				continue;

			if (Player->IsDead())
				continue;

			bool IsTeammate = Player->IsFriendlyWith(LocalCharacter);

			bool ShowEnemy = !IsTeammate && Settings[ESP_ENEMY].Value.bValue;
			bool ShowFriendly = IsTeammate && Settings[ESP_FRIENDLY].Value.bValue;

			if (!(ShowEnemy || ShowFriendly))
				continue;

			if (ShowEnemy) {
				if (LocalPlayerController->LineOfSightTo(Player, { 0.0f, 0.0f, 0.0f }, false))
					VEC4CPY(Settings[ESP_VISIBLE_COLOR].Value.v4Value, m_Color);
				else
					VEC4CPY(Settings[ESP_ENEMY_COLOR].Value.v4Value, m_Color);
			}
			else if (ShowFriendly) {
				VEC4CPY(Settings[ESP_FRIENDLY_COLOR].Value.v4Value, m_Color);
			}

			FVector2D RotatePoint = WorldToRadar(LocalCharacter->GetActorRotation(), LocalCharacter->GetActorLocation(), Player->GetActorLocation(), FVector2D(RadarCenter.X, RadarCenter.Y), 95.0f);

			ImGui::GetForegroundDrawList()->AddLine(ImVec2(RadarCenter.X, RadarCenter.Y), ImVec2(RotatePoint.X, RotatePoint.Y), ImGui::GetColorU32(ImVec4(m_Color.x, m_Color.y, m_Color.z, 0.47f)), 1.0f);
			ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(RotatePoint.X, RotatePoint.Y), 4.0f, ImGui::GetColorU32(m_Color));
		}
	}
}

float Game::CalcHeadCircleRadius(float Distance)
{
	VIRTUALIZER_MUTATE_ONLY_START;
	const float MinDistance = 0.0f;
	const float MaxDistance = 100.0f;
	const float MinRadius = 0.5f;
	const float MaxRadius = 6.0f;

	if (Distance > MaxDistance) {
		return MinRadius;
	}
	else if (Distance < MinDistance) {
		return MaxRadius;
	}
	else {
		float t = (Distance - MinDistance) / (MaxDistance - MinDistance);
		return MaxRadius + t * (MinRadius - MaxRadius);
	}
	VIRTUALIZER_MUTATE_ONLY_END;
}

void Game::LootName(bool Setting, bool Rarity, std::string Name, int Distance, FVector2D Position, ImVec4 Color)
{
	VIRTUALIZER_MUTATE_ONLY_START;
	if (Setting && Rarity) {
		Draw::DrawString(
			ImGui::GetIO().FontDefault,
			Name.append(std::to_string(Distance)).append(std::string(skCrypt(" M "))),
			Position.X,
			Position.Y,
			15.0f,
			true,
			Color
		);
	}
	VIRTUALIZER_MUTATE_ONLY_END;
}

FVector2D Game::WorldToRadar(FRotator Rotation, FVector Location, FVector EntityLocation, FVector2D RadarCenter, float RadarRadius)
{
	VIRTUALIZER_TIGER_LITE_START;
	FVector2D DotPos;
	FVector2D Direction;

	// Calculate Direction
	Direction.X = EntityLocation.Y - Location.Y;
	Direction.Y = EntityLocation.X - Location.X;

	// Get Rotation
	float LocalAngles = Rotation.Yaw;
	float Radian = DEG2RAD(LocalAngles);

	// Calculate Raw DotPos
	DotPos.X = Direction.X * cos(Radian) - Direction.Y * sin(Radian);
	DotPos.Y = Direction.X * sin(Radian) + Direction.Y * cos(Radian);

	// Scale DotPos to fit within the radar's radius
	DotPos.X /= 100.0f;
	DotPos.Y /= 100.0f;

	// Adjust DotPos to radar radius
	float Length = sqrt(DotPos.X * DotPos.X + DotPos.Y * DotPos.Y);
	if (Length > RadarRadius) {
		DotPos.X = DotPos.X * RadarRadius / Length;
		DotPos.Y = DotPos.Y * RadarRadius / Length;
	}

	// Convert to radar coordinates (with origin at RadarCenter)
	DotPos.X = DotPos.X + RadarCenter.X;
	DotPos.Y = -DotPos.Y + RadarCenter.Y;
	VIRTUALIZER_TIGER_LITE_END;
	return DotPos;
}

FRotator Game::CalcAngle(FVector Src, FVector Dst, FRotator OldRotation, float Smoothing)
{
	VIRTUALIZER_TIGER_LITE_START;
	FVector Dir = Dst - Src;
	Dir.GetSafeNormal();
	FRotator Yaptr = Dir.ToRotator();
	FRotator CpYaT = OldRotation;
	Yaptr.Pitch -= CpYaT.Pitch;
	Yaptr.Yaw -= CpYaT.Yaw;
	Yaptr.Roll = 0.0f;
	Yaptr.Clamp();
	CpYaT.Pitch += Yaptr.Pitch / Smoothing;
	CpYaT.Yaw += Yaptr.Yaw / Smoothing;
	CpYaT.Roll = 0.0f;
	VIRTUALIZER_TIGER_LITE_END;
	return CpYaT;
}

FRotator Game::CalcAngle(FVector Target)
{
	VIRTUALIZER_TIGER_LITE_START;
	FVector Rotation = LocalPlayerCamera->GetCameraLocation() - Target;
	FRotator NewViewAngle = { 0, 0, 0 };
	float hyp = sqrt(Rotation.X * Rotation.X + Rotation.Y * Rotation.Y);
	NewViewAngle.Pitch = -atan(Rotation.Z / hyp) * (180.0f / M_PI);
	NewViewAngle.Yaw = atan(Rotation.Y / Rotation.X) * (180.0f / M_PI);
	NewViewAngle.Roll = (float)0.0f;

	if (Rotation.X >= 0.f)
		NewViewAngle.Yaw += 180.0f;
	VIRTUALIZER_TIGER_LITE_END;
	return NewViewAngle;
}

FVector Game::CalcPrediction(float BulletVelocity, float BulletGravity, float TargetDistance, FVector TargetPosition, FVector TargetVelocity)
{
	VIRTUALIZER_TIGER_LITE_START;
	FVector Recalculated = TargetPosition;
	float Gravity = fabs(BulletGravity);
	float Time = TargetDistance / fabs(BulletVelocity);
	float BulletDrop = Gravity * Time * Time;
	Recalculated.Z += BulletDrop;
	Recalculated.X += Time * (TargetVelocity.X);
	Recalculated.Y += Time * (TargetVelocity.Y);
	Recalculated.Z += Time * (TargetVelocity.Z);
	VIRTUALIZER_TIGER_LITE_END;
	return Recalculated;
}

FVector Game::Prediction(ATigerCharacter* LocalCharacter, ATigerCharacter* TargetCharacter, AWorldSettings* World)
{
	VIRTUALIZER_MUTATE_ONLY_START;
	FVector Out = FVector();
	FVector TargetLocation = GetAimWorldLocation(TargetCharacter);
	FVector Velocity = TargetCharacter->CharacterMovement->LastUpdateVelocity;

	float BulletSpeed = 200000.000f / 100.0f;
	float Gravity = World->WorldGravityZ;
	float Distance = LocalPlayerCamera->GetCameraLocation().Distance(TargetLocation) / 100.0f;

	Out = CalcPrediction(BulletSpeed, Gravity, Distance, TargetLocation, Velocity);
	VIRTUALIZER_MUTATE_ONLY_END;
	return Out.IsValid() ? Out : FVector();
}

FVector Game::GetAimWorldLocation(ATigerCharacter* Player)
{
	USkeletalMeshComponent* MeshComponent = Player->Mesh;
	if (!IsValid(MeshComponent))
		return FVector();

	switch (Settings[AIM_BONE].Value.iValue) {
	case 0:
		return MeshComponent->GetSocketLocation(MeshComponent->GetBoneName(MeshComponent->GetBoneIndex(FName(skCrypt("Head")))));
	case 1:
		return MeshComponent->GetSocketLocation(MeshComponent->GetBoneName(MeshComponent->GetBoneIndex(FName(skCrypt("neck_01")))));
	case 2:
		return MeshComponent->GetSocketLocation(MeshComponent->GetBoneName(MeshComponent->GetBoneIndex(FName(skCrypt("Spine_01")))));
	case 3:
	{
		std::vector<FName> BoneNames = {
			FName(skCrypt("Head")),
			FName(skCrypt("neck_01")),
			FName(skCrypt("Spine_01")),
			FName(skCrypt("Spine_02")),
			FName(skCrypt("Spine_03"))
		};

		int32_t Index = UKMathLib->RandomIntegerInRange(0, BoneNames.size() - 1);
		FName RandonBoneName = BoneNames[Index];
		return MeshComponent->GetSocketLocation(MeshComponent->GetBoneName(MeshComponent->GetBoneIndex(RandonBoneName)));
	}
	default:
		return FVector();
	}
}

ATigerCharacter* Game::GetBestPlayer()
{
	UWorld* GWorld = UWorld::GetWorld();
	if (!IsValid(GWorld))
		return nullptr;

	float MinDistance = 133713371337.0f;
	ATigerCharacter* Out = nullptr;

	int32_t Count = GWorld->PersistentLevel->MaxPacket();
	TArray<AActor*> Actors = GWorld->PersistentLevel->Actors;
	for (int i = 0; i < Count; i++) {
		AActor* Actor = Actors[i];
		if (!Actor)
			continue;

		if (Actor->IsA(ATigerCharacter::StaticClass())) {
			ATigerCharacter* Player = static_cast<ATigerCharacter*>(Actor);
			if (!IsValid(Player))
				continue;

			USkeletalMeshComponent* MeshComponent = Player->Mesh;
			if (!IsValid(MeshComponent))
				continue;

			if (Player == LocalCharacter)
				continue;

			if (Player->CharacterType == ETigerCharacterType::Npc || Player->CharacterType == ETigerCharacterType::TargetDummy || Player->CharacterType == ETigerCharacterType::TutorialTrainer)
				continue;

			if (Player->IsDead())
				continue;

			if (Settings[IGNORE_DOWNED].Value.bValue && Player->IsDowned())
				continue;

			if (Settings[VISIBLE_CHECK].Value.bValue && !LocalPlayerController->LineOfSightTo(Player, { 0.0f, 0.0f, 0.0f }, false))
				continue;

			if (!Player->IsFriendlyWith(LocalCharacter)) {
				FVector TargetLocation = GetAimWorldLocation(Player);

				FVector2D Pos;
				LocalPlayerController->ProjectWorldLocationToScreen(TargetLocation, &Pos, false);
				if (Pos.IsValid()) {
					float XC = Pos.X - m_ScreenWidth / 2;
					float YC = Pos.Y - m_ScreenHeight / 2;
					float Distance = sqrtf((XC * XC) + (YC * YC));

					if (Distance <= MinDistance && Distance < Settings[FOV_RADIUS].Value.fValue) {
						MinDistance = Distance;
						Out = Player;
					}
				}
			}
		}
	}
	return Out;
}

ImVec4 Game::GetItemRarityColor(ETigerItemRarity Quality)
{
	switch (Quality) {
	case ETigerItemRarity::TigerItemRarity_Common:
		return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	case ETigerItemRarity::TigerItemRarity_Uncommon:
		return ImVec4(0.17f, 1.0f, 0.019f, 1.0f);
	case ETigerItemRarity::TigerItemRarity_Rare:
		return ImVec4(0.38f, 0.58f, 0.93f, 1.0f);
	case ETigerItemRarity::TigerItemRarity_Epic:
		return ImVec4(0.54f, 0.0f, 0.76f, 1.0f);
	case ETigerItemRarity::TigerItemRarity_Legendary:
		return ImVec4(0.93f, 0.74f, 0.015f, 1.0f);
	}
}