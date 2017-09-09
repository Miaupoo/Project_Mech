// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Base.h"
#include "Mech_PlayerControlled.h"
#include "UnrealNetwork.h"
#include "Animation/AnimMontage.h"

// Sets default values
AWeapon_Base::AWeapon_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Base::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWeapon_Base, m_CurrentAmmo);
	DOREPLIFETIME(AWeapon_Base, m_CurrentClip);

}


void AWeapon_Base::Reload()
{
	//
}


bool AWeapon_Base::ServeReload_Validate()
{
	return true;
}

void AWeapon_Base::ServeReload_Implementation()
{
	Reload();
	
}

