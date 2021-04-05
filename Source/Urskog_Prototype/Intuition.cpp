// Fill out your copyright notice in the Description page of Project Settings.


#include "Intuition.h"

#include "Camera/CameraComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Kismet/GameplayStatics.h"

UIntuition::UIntuition()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UIntuition::BeginPlay()
{
	Super::BeginPlay();

	BindAction();
	FindCamera();
	FindDirectionalLight();
}

void UIntuition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ChangeFOV();
	ChangeLightIntensity();
}

void UIntuition::BindAction()
{
	const auto inputController = GetOwner<AActor>()->InputComponent;
	if (inputController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing input component"));
		return;
	}
	inputController->BindAction("Intuition", EInputEvent::IE_Pressed, this, &UIntuition::ToggleIntuition);
}

void UIntuition::FindCamera()
{
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
}

void UIntuition::ToggleIntuition()
{
	UE_LOG(LogTemp, Log, TEXT("Toggle"));
	IntuitionBlend = IntuitionBlend == 0 ? 1 : 0;
}

void UIntuition::ChangeFOV()
{
	if (Camera == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing camera component"));
		return;
	}

	if (IntuitionBlend == 0)
	{
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView, NormalFieldOfView, Alpha01));
	}
	else
	{
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView, WideFieldOfView, Alpha01));
	}
}

void UIntuition::FindDirectionalLight()
{
	const auto directionalLightActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass());
	if (directionalLightActor != nullptr)
	{
		DirectionalLight = directionalLightActor->FindComponentByClass<UDirectionalLightComponent>();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't find light actor"));
		return;
	}

	if (DirectionalLight != nullptr)
	{
		LightIntensity = DirectionalLight->Intensity;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't find light component"));
		return;
	}
}


inline void UIntuition::ChangeLightIntensity()
{
	if (DirectionalLight == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing light component"));
		return;
	}

	if (IntuitionBlend == 0)
	{
		DirectionalLight->SetIntensity(FMath::Lerp(DirectionalLight->Intensity, LightIntensity, Alpha01));
	}
	else
	{
		DirectionalLight->SetIntensity(FMath::Lerp(DirectionalLight->Intensity, 0.0f, Alpha01));
	}
}