// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mech_Base.generated.h"

UCLASS()
class PROJECT_MECH_API AMech_Base : public ACharacter
{
	GENERATED_BODY()

public:
	AMech_Base();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// shoot them up !!!
	virtual void Shoot_Begin();

	virtual void Shoot_End();

	virtual void Reload();

	void EquipWeapon(AWeapon_Base * weapon);

	UFUNCTION(reliable, server, WithValidation)
	void ServerEquipWeapon(AWeapon_Base * weapon);


	// Dash Function
	// modify the dashing speed and change the movement state

	UFUNCTION()
	void GotShoot(AActor* DamagedActor, float Damage, class AController* InstigatedBy,  FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName,  FVector ShotFromDirection, const class UDamageType* DamageType, AActor*  DamageCauser);


	virtual void Dash_Begin();
	virtual void Dash_End();

	// 
	virtual void SetDashing(bool CanRun);

	// call on the server 
	UFUNCTION(reliable, server, WithValidation)
	virtual void ServerSetDashing(bool CanRun);

	bool GetIsWantToRun() { return m_IsDashing; }

	FORCEINLINE bool GetIsDashing() { return m_IsWantToRun; }

	FORCEINLINE float GetDashSpeed() { return m_DashSpeed; }

	FORCEINLINE bool CheckIsMovingForward();

	UFUNCTION()
	void OnRep_CurrentWeapon(AWeapon_Base * weapon);

	void ModifyHp(float DeltaHp);
private:

	// the current hp of the mech
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float m_CurrentHp;

	// the max hp of the mech
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float m_MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float m_DashSpeed;

	// player is shooting or not . 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool m_IsShooting;

	// player is dashing or not. use to determine player movement speed and animation
	UPROPERTY(Replicated , EditAnywhere , BlueprintReadWrite , Category = "State" , meta = (AllowPrivateAccess = "true"))
	bool m_IsDashing;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool m_IsWantToRun;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentWeapon, EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class AWeapon_Base * m_CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon_Base> m_WeaponClass;



	
	
};
