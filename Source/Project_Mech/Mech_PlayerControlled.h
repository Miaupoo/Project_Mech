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

	// vertical  moving
	void Move_Forward(float direction);

	// horizontal moving
	void Move_Right(float direction);

	// rotate the character and camera
	void TurnCamera(float direction);
	virtual void Shoot_Begin();

	virtual void Shoot_End();
	

private:
	// the speed of rotating the character and camera
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float m_RotateSpeed;

	// the speed of character movement
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	// the camera of the camera
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Camera" , meta = (AllowPrivateAccess = "true"))
	class UCameraComponent * m_PlayerCamera;

	// the spring arm of the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Camera" , meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_SpringArm;
    
	// the class pointer to the camerashake component to make the camera shake.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<UCameraShake>m_CameraShake;
	
};
