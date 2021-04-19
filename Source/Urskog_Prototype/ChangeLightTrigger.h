// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ChangeLightTrigger.generated.h"

UCLASS()
class URSKOG_PROTOTYPE_API AChangeLightTrigger : public ATriggerBox
{
	GENERATED_BODY()

		UPROPERTY()
		FRotator initial_rotation_;

	UPROPERTY()
		float initial_directional_intensity_;

	UPROPERTY()
		float initial_skylight_intensity_;

	UPROPERTY()
		float initial_fog_density_;

	UPROPERTY()
		float initial_fog_extinction_scale_;

	UPROPERTY()
		bool b_start_lerp_;

	UPROPERTY()
		bool b_directional_tick_;
	UPROPERTY()
		bool b_skylight_tick_;
	UPROPERTY()
		bool b_fog_tick_;


public:
	// Sets default values for this actor's properties
	AChangeLightTrigger();

	UPROPERTY(BlueprintReadOnly)
		float timer_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float lerp_time_;

	// Directional Light
	UPROPERTY(EditAnywhere, Category = "DirectionalLight")
		bool b_change_directional_light;

	UPROPERTY(EditAnywhere, Category = "DirectionalLight")
		class ADirectionalLight* directional_light_;

	UPROPERTY(EditAnywhere, Category = "DirectionalLight")
		FRotator new_rotation_;

	UPROPERTY(EditAnywhere, Category = "DirectionalLight")
		float new_directional_intensity;

	// Skylight
	UPROPERTY(EditAnywhere, Category = "SkyLight")
		bool b_change_skylight;

	UPROPERTY(EditAnywhere, Category = "SkyLight")
		class ASkyLight* sky_light_;

	UPROPERTY(EditAnywhere, Category = "SkyLight")
		float new_skylight_intensity_;

	// Exponential Height Fog
	UPROPERTY(EditAnywhere, Category = "ExponentialHeightFog")
		bool b_change_fog_;

	UPROPERTY(EditAnywhere, Category = "ExponentialHeightFog")
		class AExponentialHeightFog* fog_;

	UPROPERTY(EditAnywhere, Category = "ExponentialHeightFog")
		float new_fog_density_;

	UPROPERTY(EditAnywhere, Category = "ExponentialHeightFog")
		float new_fog_exctinction_scale_;

	//Skysphere Values
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Skysphere Values")
		struct FLinearColor zenith_color_;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Skysphere Values")
		FLinearColor horizon_color_;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Skysphere Values")
		float star_brightness_;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Skysphere Values")
		float sun_brightness_;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Skysphere Values")
		float cloud_opacity_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void SetSkySphereInitialValues();

	UFUNCTION(BlueprintImplementableEvent)
		void LerpSkySphereValues();
private:
	UFUNCTION()
		void BeingOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
