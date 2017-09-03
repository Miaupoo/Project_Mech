// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mech_Base.generated.h"

UCLASS()
class PROJECT_MECH_API AMech_Base : public ACharacter
{
	GENERATED_BODY()

public:
	AMech_Base();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// the current hp of the mech

	float m_CurrentHp;

	// the max hp of the mech

	float m_MaxHp;

	





	
	
};
