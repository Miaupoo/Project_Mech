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

	void LookUpCamera(float direction);


	UFUNCTION(reliable, server, WithValidation)
	void ServerTurnCamera(float direction);


	void CameraUpdate();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	virtual void Shoot_Begin()override;

	virtual void Shoot_End()override;
	
	virtual void Dash_Begin()override;

	virtual void Dash_End()override;

	virtual void ToggleAimming();

	class UCameraComponent * GetCamera() { return m_PlayerCamera; }
private:


	// the speed of rotating the character and camera
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float m_RotateSpeed;

	// the speed of character movement
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float m_CurrentDashSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool m_IsAimming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraTrick", meta = (AllowPrivateAccess = "true"))
	FVector m_NormalCameraLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraTrick", meta = (AllowPrivateAccess = "true"))
	FVector m_AimmingCameraLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraTrick", meta = (AllowPrivateAccess = "true"))
	FVector m_CurrentCameraLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraTrick", meta = (AllowPrivateAccess = "true"))
	FVector m_DashCameraLocation;

	// the camera of the camera
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Camera" , meta = (AllowPrivateAccess = "true"))
	class UCameraComponent * m_PlayerCamera;

	// the spring arm of the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Camera" , meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_SpringArm;
    
	// the class pointer to the camerashake component to make the camera shake.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraTrick", meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<UCameraShake>m_CameraShake;
	
	
};
