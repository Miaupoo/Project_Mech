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

	// Dash Function
	// modify the dashing speed and change the movement state
	virtual void Dash_Begin();

	virtual void Dash_End();

	// 
	virtual void SetDashing(bool IsDashing);

	// call on the server 
	UFUNCTION(reliable, server, WithValidation)
	virtual void ServerSetDashing(bool IsDashing);

	FORCEINLINE bool GetIsDashing() { return m_IsDashing; }

	FORCEINLINE float GetDashSpeed() { return m_DashSpeed; }



private:

	// the current hp of the mech
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
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

	





	
	
};
