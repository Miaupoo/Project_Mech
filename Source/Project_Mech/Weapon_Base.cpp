// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Base.h"
#include "Mech_PlayerControlled.h"
#include "UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Animation/AnimMontage.h"

AWeapon_Base::AWeapon_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	m_WeaponData = FWeaponData();
	m_CurrentAmmo = m_WeaponData.m_AmmoPerClip;
	m_CurrentClip = m_WeaponData.m_InitialClips;
	m_AmmosInClip = m_WeaponData.m_MaxAmmo - m_WeaponData.m_AmmoPerClip;
	m_WeaponState = EWeaponState::Idle;
	m_PreWeaponState = EWeaponState::Idle;
	bReplicates = true;
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	//SetOwner(m_OwnerCharacter);

}

void AWeapon_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (m_CurrentFireColdDown > 0)
	{
	m_CurrentFireColdDown -= DeltaTime;
	}
	if (m_IsShooting && CanFire())
	{
	HandleFire();
	}*/


}

void AWeapon_Base::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWeapon_Base, m_CurrentAmmo);
	DOREPLIFETIME(AWeapon_Base, m_CurrentClip);
	DOREPLIFETIME(AWeapon_Base, m_OwnerCharacter);


}

void AWeapon_Base::Reload()
{
	if (CanReload())
	{

		if (Role < ROLE_Authority)
		{
			UE_LOG(LogTemp, Warning, TEXT("ServeReloading"), m_CurrentAmmo);

			ServeReload();
		}
		//UE_LOG(LogTemp, Warning, TEXT("localReload"));
		StopFire();
		SetWeaponState(EWeaponState::Reloading);
		float AnimationDuration = PlayWeaponAnimation(m_ReloadAnimation);
		//GetWorldTimerManager().SetTimer(m_ReloadTimerHandle , &AWeapon_Base::StopReload , AnimationDuration, false);
		//GetWorldTimerManager().SetTimer(m_ReloadTimerHandle, &AWeapon_Base::AddAmmo, AnimationDuration, false);
		AddAmmo();
		if (m_OwnerCharacter && m_OwnerCharacter->IsLocallyControlled())
		{
			PlayWeaponSound(m_ReloadSound);
		}
		SetWeaponState(EWeaponState::Idle);

	}

}

bool AWeapon_Base::ServeReload_Validate()
{
	return true;
}

void AWeapon_Base::ServeReload_Implementation()
{
	Reload();

}

void AWeapon_Base::StopReload()
{
	SetWeaponState(EWeaponState::Idle);

}

void AWeapon_Base::AddAmmo()
{

	int DeltaAmmo = m_WeaponData.m_AmmoPerClip - m_CurrentAmmo;

	m_CurrentAmmo = m_WeaponData.m_AmmoPerClip;

	m_AmmosInClip -= DeltaAmmo;

	m_CurrentClip = m_AmmosInClip / m_WeaponData.m_AmmoPerClip + 1;

}

void AWeapon_Base::UseAmmo()
{
	if (m_WeaponData.m_IsInfiniteAmmo || m_WeaponData.m_IsInfiniteClip)
	{
		return;
	}
	else
	{
		m_CurrentAmmo -= m_WeaponData.m_AmmoPerShoot;
	}

}

void AWeapon_Base::SetWeaponState(EWeaponState NewState)
{
	m_WeaponState = NewState;
	HandleNewState(NewState);
}

void AWeapon_Base::HandleNewState(EWeaponState NewState)
{
	switch (NewState)
	{
	case EWeaponState::Idle:
	{
		m_CurrentSpreadDegree = 0;
		break;
	}
	case EWeaponState::Shooting:
	{

		break;

	}

	case EWeaponState::Reloading:
	{

		break;

	}

	default:

		break;
	}
}

void AWeapon_Base::SetOwningPawn(AMech_Base * NewOwner)
{
	if (m_OwnerCharacter != NewOwner)
	{
		m_OwnerCharacter = NewOwner;
		SetOwner(NewOwner);
		Instigator = NewOwner;
		AttachToActor(NewOwner, FAttachmentTransformRules::KeepRelativeTransform, "Weapon");
	}

}


void AWeapon_Base::StartFire()
{
	if (CanFire())
	{
		SetWeaponState(EWeaponState::Shooting);
		//PlayWeaponAnimation(m_ShootAnimation);

		HandleFire();
	}
}

void AWeapon_Base::StopFire()
{
	if (Role < ROLE_Authority)
	{
		ServeStopFire();
	}
	m_CurrentSpreadDegree = 0;
	SetWeaponState(EWeaponState::Idle);
	GetWorldTimerManager().ClearTimer(m_FiringTimerHandle);
}

bool AWeapon_Base::ServeStopFire_Validate()
{
	return true;
}

void AWeapon_Base::ServeStopFire_Implementation()
{
	StopFire();
}

void AWeapon_Base::HandleFire()
{
	if (Role < ROLE_Authority)
	{
		ServeHandleFire();
		UE_LOG(LogTemp, Warning, TEXT("ServeFire"), m_CurrentAmmo);

	}
	if (m_OwnerCharacter->IsLocallyControlled())
	{
		PlayWeaponSound(m_ShootSound);
	}
	UseAmmo();
	FireWeapon();
	GetWorldTimerManager().SetTimer(m_FiringTimerHandle, this, &AWeapon_Base::HandleFire, 1, true, m_WeaponData.m_FireRate);

}

bool AWeapon_Base::ServeHandleFire_Validate()
{
	return true;
}

void AWeapon_Base::ServeHandleFire_Implementation()
{
	HandleFire();
}

bool AWeapon_Base::CanReload()
{
	if (m_CurrentClip == 0 || m_CurrentAmmo == m_WeaponData.m_AmmoPerClip || m_WeaponState == EWeaponState::Reloading)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AWeapon_Base::CanFire()
{
	if (m_WeaponState == EWeaponState::Reloading || m_CurrentAmmo == 0)
	{
		return false;
	}
	return true;
}

float AWeapon_Base::PlayWeaponAnimation(UAnimMontage * WeaponAnimation)
{
	float Duration = m_OwnerCharacter->PlayAnimMontage(WeaponAnimation);
	return Duration;
}

void AWeapon_Base::PlayWeaponSound(USoundBase * WeaponSound)
{
	UGameplayStatics::PlaySoundAtLocation(this, WeaponSound, GetActorLocation());
}