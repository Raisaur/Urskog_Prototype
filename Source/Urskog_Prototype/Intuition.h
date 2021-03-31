// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Intuition.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class URSKOG_PROTOTYPE_API UIntuition : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UIntuition();

	UPROPERTY(EditDefaultsOnly)
		int IntuitionBlend = 0;

	UPROPERTY(EditDefaultsOnly)
		UMaterialParameterCollection* Asset = nullptr;

	UPROPERTY(EditDefaultsOnly)
		FName IntuitionKey = "Intuitionmode_blend";

	UPROPERTY(EditDefaultsOnly)
		float WideFieldOfView = 120;

	UPROPERTY(EditDefaultsOnly)
		float NormalFieldOfView = 90;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ToggleIntuition();

private:
	UMaterialParameterCollectionInstance* Material = nullptr;
	UCameraComponent* Camera = nullptr;

	void BindAction();
	void FindMaterial();
	void FindCamera();
	void ChangeFOV();
	void ChangeMaterial();

};
