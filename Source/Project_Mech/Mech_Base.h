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

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// shoot them up !!!
	virtual void Shoot_Begin();

	virtual void Shoot_End();

	virtual void Dash_Begin();

	virtual void Dash_End();

	FORCEINLINE bool GetIsDashing() { return m_IsDashing; }
private:

	// the current hp of the mech
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float m_CurrentHp;

	// the max hp of the mech
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float m_MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool m_IsShooting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool m_IsDashing;
	





	
	
};
