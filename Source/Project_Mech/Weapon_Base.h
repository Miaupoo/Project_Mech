// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Ammo")
	bool m_IsInfiniteAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	bool m_IsInfiniteClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int m_MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int m_AmmoPerClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int m_InitialClips;
	
	FWeaponData()
	{
		m_IsInfiniteAmmo = false;
		m_IsInfiniteClip = false;
		m_MaxAmmo = 100;
		m_AmmoPerClip = 20;
		m_InitialClips = m_MaxAmmo / m_AmmoPerClip - 1;

	}
};
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

	void AddAmmo();

	void UseAmmo();

	float PlayWeaponAnimation(UAnimMontage * WeaponAnimation);

	void PlayWeaponSound(USoundBase * WeaponSound);

	bool CanReload();

	void SetWeaponState(EWeaponState NewState);

	void HandleNewState(EWeaponState NewState);

	void StopReload();
private:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FWeaponData m_WeaponData;

	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category = "Weapon" , meta = (AllowPrivateAccess = "true"))
	EWeaponState m_WeaponState;

	EWeaponState m_PreWeaponState;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aniamtion", meta = (AllowPrivateAccess = "true"))
	UAnimMontage * m_ReloadAnimation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aniamtion", meta = (AllowPrivateAccess = "true"))
	UAnimMontage * m_ShootAnimation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase * m_ReloadSound;

	FTimerHandle m_ReloadTimerHandle;



	UPROPERTY(Replicated , BlueprintReadWrite, EditAnywhere, Category = "ammo", meta = (AllowPrivateAccess = "true"))
	int m_CurrentAmmo;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "ammo", meta = (AllowPrivateAccess = "true"))
	int m_CurrentClip;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ammo", meta = (AllowPrivateAccess = "true"))
	int m_AmmosInClip;

	int m_ShootCount;

	class AMech_PlayerControlled * m_OwnerCharacter;

	
};
