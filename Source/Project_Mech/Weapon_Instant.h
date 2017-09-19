
#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Instant.generated.h"
USTRUCT(BlueprintType)
struct FInstantWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int m_ShootingRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int m_MaxSpreadDegree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int m_DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int m_SpreadSeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float m_DeltaSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	TSubclassOf<UDamageType>m_DamageType;


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

	virtual FVector GetMuzzleDirection();

	virtual FVector GetMuzzleLocation();


private:

	FHitResult m_HitResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData", meta = (AllowPrivateAccess = "true"))
	FVector m_EndTracePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData", meta = (AllowPrivateAccess = "true"))
	FInstantWeaponData m_InstantWeaponData;

	


};