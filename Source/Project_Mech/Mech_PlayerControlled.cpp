// Fill out your copyright notice in the Description page of Project Settings.

#include "Mech_PlayerControlled.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
AMech_PlayerControlled::AMech_PlayerControlled()
{
	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_SpringArm->AttachTo(RootComponent);
	m_PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	m_PlayerCamera->SetupAttachment(m_SpringArm, USpringArmComponent::SocketName);
	m_RotateSpeed = 50;
	m_MoveSpeed = 20;

}
void AMech_PlayerControlled::BeginPlay()
{
	Super::BeginPlay();
	// the default camera location.
	m_NormalCameraLocation = m_PlayerCamera->RelativeLocation;
	m_DashCameraLocation = FVector(97, 0, 67);
	m_AimmingCameraLocation = FVector(220, 70, 65);
	m_CurrentCameraLocation = m_NormalCameraLocation;
	m_CurrentDashSpeed = 1;
}

void AMech_PlayerControlled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// update the camera location base on player state
	CameraUpdate();
}


void AMech_PlayerControlled::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMech_PlayerControlled::Move_Forward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMech_PlayerControlled::Move_Right);
	PlayerInputComponent->BindAxis("TurnCamera", this, &AMech_PlayerControlled::TurnCamera);
	PlayerInputComponent->BindAction("Shoot",IE_Pressed, this, &AMech_PlayerControlled::Shoot_Begin);
	PlayerInputComponent->BindAxis("LookUpCamera", this, &AMech_PlayerControlled::LookUpCamera);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMech_PlayerControlled::Shoot_End);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMech_PlayerControlled::Dash_Begin);
	PlayerInputComponent->BindAction("Dash", IE_Released, this, &AMech_PlayerControlled::Dash_End);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AMech_PlayerControlled::ToggleAimming);

}

void AMech_PlayerControlled::Move_Forward(float direction)
{
	if (direction && !m_IsAimming)
	{
		if (direction > 0)
		{
			AddMovementInput(GetActorForwardVector(), direction * m_MoveSpeed * GetWorld()->DeltaTimeSeconds * m_CurrentDashSpeed);
		}
		else
		{
			AddMovementInput(GetActorForwardVector(), direction * m_MoveSpeed * GetWorld()->DeltaTimeSeconds);
		}
		// make camera shake during the character movement 
		UGameplayStatics::PlayWorldCameraShake(this, m_CameraShake, m_PlayerCamera->GetComponentLocation(), 0, 1000);
	}

}

void AMech_PlayerControlled::Move_Right(float direction)
{
	if (direction && !m_IsAimming)
	{
		AddMovementInput(GetActorRightVector(), direction * m_MoveSpeed * GetWorld()->DeltaTimeSeconds);
		UGameplayStatics::PlayWorldCameraShake(this, m_CameraShake, m_PlayerCamera->GetComponentLocation(), 0, 1000);
	}

}

void AMech_PlayerControlled::Shoot_Begin()
{
	// wait to implment
	Super::Shoot_Begin();


}
void AMech_PlayerControlled::Shoot_End()
{
	// wait to implment
	Super::Shoot_End();



}
void AMech_PlayerControlled::Dash_Begin()
{

	Super::Dash_Begin();
	m_CurrentDashSpeed = GetDashSpeed();
}

void AMech_PlayerControlled::Dash_End()
{
	Super::Dash_End();
	m_CurrentDashSpeed = 1;

}

void AMech_PlayerControlled::CameraUpdate()
{
	if (GetIsDashing() == true)
	{
		m_CurrentCameraLocation = UKismetMathLibrary::VInterpTo(m_CurrentCameraLocation, m_DashCameraLocation, GetWorld()->DeltaTimeSeconds, 2);
	}
	else if (m_IsAimming == true)
	{
		m_CurrentCameraLocation = UKismetMathLibrary::VInterpTo(m_CurrentCameraLocation, m_AimmingCameraLocation, GetWorld()->DeltaTimeSeconds, 4);
	}
	else
	{
		m_CurrentCameraLocation = UKismetMathLibrary::VInterpTo(m_CurrentCameraLocation, m_NormalCameraLocation, GetWorld()->DeltaTimeSeconds, 2);
	}
	m_PlayerCamera->SetRelativeLocation(m_CurrentCameraLocation);
}


void AMech_PlayerControlled::LookUpCamera(float direction)
{
	/*if (direction)
	{
		//m_PlayerCamera->AddRelativeRotation(FRotator(direction * m_RotateSpeed * GetWorld()->DeltaTimeSeconds, 0, 0));
		AddControllerPitchInput(direction * m_RotateSpeed * GetWorld()->GetDeltaSeconds());

	}*/

}



void AMech_PlayerControlled::TurnCamera(float direction)
{
	if (direction)
	{
		AddControllerYawInput(direction * m_RotateSpeed * GetWorld()->GetDeltaSeconds());

		if (Role < ROLE_Authority)
		{
			ServerTurnCamera(direction);
		}
	}

}

bool AMech_PlayerControlled::ServerTurnCamera_Validate(float direction)
{
	return true;
}

void AMech_PlayerControlled::ServerTurnCamera_Implementation(float direction)
{
	TurnCamera(direction);
}



void AMech_PlayerControlled::ToggleAimming()
{
	if (GetIsDashing())
	{
		SetDashing(false);
	}
	m_IsAimming = (!m_IsAimming);
}
