// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"
USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Ammo")
	bool m_IsInfiniteAmmo;

	UPROPERTY(BlueprintReadWrite, Category = "Ammo")
	bool m_IsInfiniteClip;

	UPROPERTY(BlueprintReadWrite, Category = "Ammo")
	int m_MaxAmmo;

	UPROPERTY(BlueprintReadWrite, Category = "Ammo")
	int m_AmmoPerClip;

	UPROPERTY(BlueprintReadWrite, Category = "Ammo")
	int m_InitialClips;


	/** time between two consecutive shots */
	//UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		//float TimeBetweenShots;

	/** failsafe reload duration if weapon doesn't have any animation for it */
	//UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		//float NoAnimReloadDuration;
	
	/** defaults */
	/*
	FWeaponData()
	{
		bInfiniteAmmo = false;
		bInfiniteClip = false;
		MaxAmmo = 100;
		AmmoPerClip = 20;
		InitialClips = 4;
		TimeBetweenShots = 0.2f;
		NoAnimReloadDuration = 1.0f;
	}*/
};
/*UENUM()
enum EWeaponState
{
	Idle,
	Shooting,
	Reloading
};*/

UENUM(BlueprintType)		
enum class EWeaponState : uint8
{
	Idle,
	Shooting,
	Reloading
};

UCLASS()
class PROJECT_MECH_API AWeapon_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
   virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;


	void Reload();

	UFUNCTION(reliable, server, WithValidation)
	void ServeReload();


private:
	UPROPERTY(BlueprintReadWrite , EditAnywhere,Category = "Weapon" , meta = (AllowPrivateAccess = "true"))
	FWeaponData m_Weapondate;

	UPROPERTY(BlueprintReadWrite , EditAnywhere = "Weapon" , meta = (AllowPrivateAccess = "true"))
	EWeaponState m_WeaponState;

	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category = "Aniamtion" , meta = (AllowPrivateAccess = "true"))
	UAnimMontage * m_ReloadAnimation;

	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category = "Aniamtion" , meta = (AllowPrivateAccess = "true"))
	UAnimMontage * m_ShootAnimation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase * m_ReloadSound;

	UPROPERTY(Replicated , BlueprintReadWrite , EditAnywhere , Category = "Ammo" , meta = (AllowPrivateAccess = "true"))
	int m_CurrentAmmo;

	UPROPERTY(Replicated , BlueprintReadWrite , EditAnywhere , Category = "Ammo" , meta = (AllowPrivateAccess = "true"))
	int m_CurrentClip;

	class AMech_PlayerControlled * m_OwnerCharacter;
	
};
