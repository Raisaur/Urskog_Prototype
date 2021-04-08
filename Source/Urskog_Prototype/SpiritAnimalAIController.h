// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SpiritAnimalAIController.generated.h"

/**
 *
 */
UCLASS()
class URSKOG_PROTOTYPE_API ASpiritAnimalAIController : public AAIController
{
	GENERATED_BODY()

public:
	void Tick(float DeltaTime) override;
protected:
	void BeginPlay() override;
};
