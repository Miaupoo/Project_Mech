// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Instant.generated.h"
USTRUCT(BlueprintType)
struct FInstantWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "WeaponData")
	int m_ShootingRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int m_MaxSpreadDegree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int m_DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int m_SpreadSeed;

	FInstantWeaponData()
	{
		m_ShootingRange = 100;
	}
};

UCLASS()
class PROJECT_MECH_API AWeapon_Instant : public AWeapon_Base
{
	GENERATED_BODY()
public:
	AWeapon_Instant();

	void WeaponTrace();

	virtual void FireWeapon()override;

private:

	FHitResult m_HitResult;

	FVector m_EndTracePoint;

	FInstantWeaponData m_InstantWeaponData;

	float m_CurrentSpreadDegree;
	
};
