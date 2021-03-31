// Fill out your copyright notice in the Description page of Project Settings.


#include "Intuition.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollectionInstance.h"

UIntuition::UIntuition()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UIntuition::BeginPlay()
{
	Super::BeginPlay();

	BindAction();
	//FindMaterial();
	FindCamera();
}

void UIntuition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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

void UIntuition::FindMaterial()
{
	if (Asset == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Missing material asset"));
		return;
	}
	Material = GetWorld()->GetParameterCollectionInstance(Asset);
}

void UIntuition::FindCamera()
{
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
}

void UIntuition::ToggleIntuition()
{
	IntuitionBlend = IntuitionBlend == 0 ? 1 : 0;
	//ChangeMaterial();
	ChangeFOV();
}

void UIntuition::ChangeMaterial()
{
	if (Material == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing material asset instance"));
		return;
	}

	Material->SetScalarParameterValue("Intuitionmode_blend", IntuitionBlend);
}

void UIntuition::ChangeFOV()
{
	if (Camera == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing camera componentt"));
		return;
	}

	if (IntuitionBlend == 0)
	{
		Camera->SetFieldOfView(NormalFieldOfView);
	}
	else
	{
		Camera->SetFieldOfView(WideFieldOfView);
	}
}
