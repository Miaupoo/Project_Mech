// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Instant.h"
#include "Kismet/KismetSystemLibrary.h"


AWeapon_Instant::AWeapon_Instant()
{

}

void AWeapon_Instant::WeaponTrace()
{
	//UKismetSystemLibrary::LineTraceSingle(this, GetMuzzleLocation(), m_EndTracePoint,ETraceTypeQuery::TraceTypeQuery1,true,NULL,)
}
void AWeapon_Instant::FireWeapon()
{
	FRandomStream RandomStream(m_InstantWeaponData.m_SpreadSeed);
	float HalfCone = FMath::DegreesToRadians(m_CurrentSpreadDegree * 0.5);
	m_EndTracePoint = GetMuzzleLocation() + (RandomStream.VRandCone(GetMuzzleDirection(), HalfCone, HalfCone) * m_InstantWeaponData.m_ShootingRange);
	m_CurrentSpreadDegree++;
	WeaponTrace();

}
