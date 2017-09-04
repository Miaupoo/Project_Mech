// Fill out your copyright notice in the Description page of Project Settings.

#include "Mech_Base.h"


// Sets default values
AMech_Base::AMech_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMech_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMech_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMech_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    

}
void AMech_Base::Shoot_Begin()
{
	// wait to implment
	m_IsShooting = true;

}
void AMech_Base::Shoot_End()
{
	// wait to implment
	m_IsShooting = false;


}
void AMech_Base::Dash_Begin()
{
	m_IsDashing = true;
}

void AMech_Base::Dash_End()
{
	m_IsDashing = false;

}