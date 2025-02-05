#include "Weapon_Instant.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Mech_PlayerControlled.h"
#include "Mech_Base.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

AWeapon_Instant::AWeapon_Instant()
{

}

void AWeapon_Instant::WeaponTrace()
{
	//UKismetSystemLibrary::LineTraceSingle(this, GetMuzzleLocation(), m_EndTracePoint,ETraceTypeQuery::TraceTypeQuery1,true,NULL,)

	GetWorld()->LineTraceSingleByChannel(m_HitResult, GetMuzzleLocation(), GetMuzzleLocation() + (GetMuzzleDirection() * m_InstantWeaponData.m_ShootingRange), ECollisionChannel::ECC_Pawn);
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
			UGameplayStatics::ApplyPointDamage(GotHitActor, m_InstantWeaponData.m_DamageAmount, m_HitResult.ImpactNormal, m_HitResult, GetPawn()->Controller, this, m_InstantWeaponData.m_DamageType);

		}
		UE_LOG(LogTemp, Warning, TEXT("HitSomething"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("nothit"));

	}



}
FVector AWeapon_Instant::GetMuzzleDirection()
{
	AMech_PlayerControlled * Owner = Cast<AMech_PlayerControlled>(GetPawn());
	FVector Direction;
	if (Owner)
	{
		Direction = Owner->GetCamera()->GetForwardVector();
	}
	return Direction;
}

FVector AWeapon_Instant::GetMuzzleLocation()
{
	AMech_PlayerControlled * Owner = Cast<AMech_PlayerControlled>(GetPawn());
	FVector Location;

	if (Owner)
	{
		return Location = Owner->GetCamera()->GetComponentLocation();
	}
	return Location;

}