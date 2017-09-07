// Fill out your copyright notice in the Description page of Project Settings.

#include "Mech_Base.h"
#include "UnrealNetwork.h"

// Sets default values
AMech_Base::AMech_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_DashSpeed = 1.5;
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
void AMech_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Here we list the variables we want to replicate + a condition if wanted 
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
	// wait to implment
	m_IsShooting = false;


}
void AMech_Base::Dash_Begin()
{
	SetDashing(true);
	//m_IsDashing = true;
}

void AMech_Base::Dash_End()
{
	SetDashing(false);
	//m_IsDashing = false;

}
void  AMech_Base::SetDashing(bool IsDashing)
{
	m_IsDashing = IsDashing;
	if (Role < ROLE_Authority)
	{
		ServerSetDashing(IsDashing);
		UE_LOG(LogTemp, Warning, TEXT("Call on the serve"));
	}
}
bool  AMech_Base::ServerSetDashing_Validate(bool IsDashing)
{
	return true;
}
void  AMech_Base::ServerSetDashing_Implementation(bool IsDashing)
{
	SetDashing(IsDashing);
}
