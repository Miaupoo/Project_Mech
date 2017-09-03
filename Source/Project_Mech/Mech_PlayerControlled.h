// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mech_Base.h"
#include "Mech_PlayerControlled.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MECH_API AMech_PlayerControlled : public AMech_Base
{
	GENERATED_BODY()
public:

	AMech_PlayerControlled();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move_Forward(float direction);

	void Move_Right(float direction);

	void TurnCamera(float direction);

	void Shoot();

private:
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float m_RotateSpeed;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Camera" , meta = (AllowPrivateAccess = "true"))
	class UCameraComponent * m_PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Camera" , meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_SpringArm;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<UCameraShake>m_CameraShake;
	
};
