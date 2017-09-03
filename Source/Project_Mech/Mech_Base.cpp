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

