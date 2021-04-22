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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WideFieldOfView = 110;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NormalFieldOfView = 90;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Alpha01 = 0.1f;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ToggleIntuition();

private:
	UDirectionalLightComponent* DirectionalLight = nullptr;
	UCameraComponent* Camera = nullptr;
	float LightIntensity = 1.0f;
	int IntuitionBlend = 0;
	void BindAction();
	void FindCamera();
	void ChangeFOV();
	void FindDirectionalLight();
	void ChangeLightIntensity();
};
