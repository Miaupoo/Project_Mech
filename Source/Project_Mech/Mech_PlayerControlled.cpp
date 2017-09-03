// Fill out your copyright notice in the Description page of Project Settings.

#include "Mech_PlayerControlled.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

AMech_PlayerControlled::AMech_PlayerControlled()
{
	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_SpringArm->AttachTo(RootComponent);
	m_PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	m_PlayerCamera->SetupAttachment(m_SpringArm, USpringArmComponent::SocketName);
}

void AMech_PlayerControlled::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMech_PlayerControlled::Move_Forward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMech_PlayerControlled::Move_Right);
	PlayerInputComponent->BindAxis("TurnCamera", this, &AMech_PlayerControlled::TurnCamera);
	PlayerInputComponent->BindAction("Shoot",IE_Pressed, this, &AMech_PlayerControlled::Shoot_Begin);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMech_PlayerControlled::Shoot_End);

}

void AMech_PlayerControlled::Move_Forward(float direction)
{
	if (direction)
	{
		AddMovementInput(GetActorForwardVector(), direction * m_MoveSpeed * GetWorld()->DeltaTimeSeconds);
		// make camera shake during the character movement 
		UGameplayStatics::PlayWorldCameraShake(this, m_CameraShake, m_PlayerCamera->GetComponentLocation(), 0, 1000);
	}

}

void AMech_PlayerControlled::Move_Right(float direction)
{
	if (direction)
	{
		AddMovementInput(GetActorRightVector(), direction * m_MoveSpeed * GetWorld()->DeltaTimeSeconds);
		UGameplayStatics::PlayWorldCameraShake(this, m_CameraShake, m_PlayerCamera->GetComponentLocation(), 0, 1000);
	}

}

void AMech_PlayerControlled::TurnCamera(float direction)
{
	if (direction)
	{
		AddActorWorldRotation(FRotator(0, direction * m_RotateSpeed * GetWorld()->DeltaTimeSeconds, 0));
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