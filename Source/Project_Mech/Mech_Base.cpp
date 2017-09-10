// Fill out your copyright notice in the Description page of Project Settings.

#include "Mech_Base.h"
#include "Weapon_Base.h"
#include "UnrealNetwork.h"

// Sets default values
AMech_Base::AMech_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_DashSpeed = 1.5;
	m_CurrentWeapon = CreateDefaultSubobject<AWeapon_Base>(TEXT("Weapon"));
}

// Called when the game starts or when spawned
void AMech_Base::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;
	m_CurrentWeapon = GetWorld()->SpawnActor<AWeapon_Base>(m_WeaponClass);
	//m_CurrentWeapon = Cast<AWeapon_Base>(m_WeaponClass->GetDefaultObject());
}

// Called every frame
void AMech_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Role == GetRemoteRole())
	{

		UE_LOG(LogTemp, Warning, TEXT("Role"));

	}
	/*if (CheckIsMovingForward() && m_IsWantToRun)
	{
		SetDashing(true);
	}
	else 
	{
		SetDashing(false);
	}*/

}
void AMech_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMech_Base, m_IsDashing);
	
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
	m_IsShooting = false;

}
void AMech_Base::Dash_Begin()
{
	m_IsWantToRun = true;
}

void AMech_Base::Dash_End()
{
	m_IsWantToRun = false;
	SetDashing(false);

}
void  AMech_Base::SetDashing(bool CanRun)
{
	
	if (Role < ROLE_Authority)
    {
		
		ServerSetDashing(CanRun);
		UE_LOG(LogTemp, Warning, TEXT("Call on the serve"));
	}
	m_IsDashing = CanRun;


}
bool  AMech_Base::ServerSetDashing_Validate(bool CanRun)
{
	return true;
}
void  AMech_Base::ServerSetDashing_Implementation(bool CanRun)
{
	SetDashing(CanRun);
}
void AMech_Base::Reload()
{
	m_CurrentWeapon->Reload();
}
bool AMech_Base::CheckIsMovingForward()
{
	return FVector::DotProduct(GetVelocity().GetSafeNormal(), GetActorForwardVector()) > 0.6;
}