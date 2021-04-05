// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DirectionalLight.h"
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
		float WideFieldOfView = 110;

	UPROPERTY(EditDefaultsOnly)
		float NormalFieldOfView = 90;

	UPROPERTY(EditAnywhere)
		float Alpha01 = 0.1f;
	UPROPERTY(EditAnyWhere)
		UDirectionalLightComponent* DirectionalLight = nullptr;


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ToggleIntuition();

private:
	UCameraComponent* Camera = nullptr;
	float LightIntensity = 1.0f;
	void BindAction();
	void FindCamera();
	void ChangeFOV();
	void FindDirectionalLight();
	void ChangeLightIntensity();
};
