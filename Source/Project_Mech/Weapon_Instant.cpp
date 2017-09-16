// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Instant.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Mech_PlayerControlled.h"
#include "Mech_Base.h"

AWeapon_Instant::AWeapon_Instant()
{

}

void AWeapon_Instant::WeaponTrace()
{
	//UKismetSystemLibrary::LineTraceSingle(this, GetMuzzleLocation(), m_EndTracePoint,ETraceTypeQuery::TraceTypeQuery1,true,NULL,)
	GetWorld()->LineTraceSingleByChannel(m_HitResult, GetActorLocation() + GetActorForwardVector() * 50 , GetActorLocation() + (GetActorForwardVector() * m_InstantWeaponData.m_ShootingRange), ECollisionChannel::ECC_Pawn);
}
void AWeapon_Instant::FireWeapon()
{
	
	FRandomStream RandomStream(m_InstantWeaponData.m_SpreadSeed);
	float HalfCone = FMath::DegreesToRadians(GetCurrentSpreadDegree() * 0.5);
	m_EndTracePoint = GetMuzzleLocation() + (RandomStream.VRandCone(GetMuzzleDirection(), HalfCone, HalfCone) * m_InstantWeaponData.m_ShootingRange);
	SetCurrentSpreadDegree(m_InstantWeaponData.m_DeltaSpread);
	WeaponTrace();
	if (m_HitResult.bBlockingHit)
	{
		AMech_Base * GotHitActor = Cast<AMech_Base>(m_HitResult.GetActor());
		if (GotHitActor)
		{
		  UE_LOG(LogTemp, Warning, TEXT("HitActor"));
		}
		UE_LOG(LogTemp, Warning, TEXT("HitSomething"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("nothit"));

	}
   


}
