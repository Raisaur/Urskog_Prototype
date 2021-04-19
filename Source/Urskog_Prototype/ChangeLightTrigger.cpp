// Fill out your copyright notice in the Description page of Project Settings.

#include "ChangeLightTrigger.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Components/SkyLightComponent.h"
#include "Engine/SkyLight.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Engine/ExponentialHeightFog.h"


// Sets default values
AChangeLightTrigger::AChangeLightTrigger() :
	b_start_lerp_(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	b_change_directional_light = b_change_skylight = b_directional_tick_ = b_skylight_tick_ = false;
	directional_light_ = nullptr;
	sky_light_ = nullptr;
	fog_ = nullptr;

	lerp_time_ = 0.0f;
	timer_ = 0.0f;
	OnActorBeginOverlap.AddDynamic(this, &AChangeLightTrigger::BeingOverlap);
}

// Called when the game starts or when spawned
void AChangeLightTrigger::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AChangeLightTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (b_start_lerp_) {
		timer_ += DeltaTime;

		if (timer_ / lerp_time_ >= 1.0f)
		{
			if (b_directional_tick_) b_directional_tick_ = false;

			if (b_skylight_tick_) b_skylight_tick_ = false;

			if (b_fog_tick_) b_fog_tick_ = false;
			b_start_lerp_ = false;
		}

		if (b_directional_tick_)
		{
			if (timer_ / lerp_time_ < 1.0f)
			{
				FRotator rotation = FMath::Lerp(initial_rotation_, new_rotation_, timer_ / lerp_time_);
				directional_light_->SetActorRotation(rotation);

				float intensity = FMath::Lerp(initial_directional_intensity_, new_directional_intensity, timer_ / lerp_time_);
				directional_light_->GetLightComponent()->SetIntensity(intensity);
			}
		}

		if (b_skylight_tick_)
		{
			if (timer_ / lerp_time_ < 1.0f)
			{
				float intensity = FMath::Lerp(initial_skylight_intensity_, new_skylight_intensity_, timer_ / lerp_time_);
				sky_light_->GetLightComponent()->SetIntensity(intensity);
			}
		}

		if (b_fog_tick_)
		{
			if (timer_ / lerp_time_ < 1.0f)
			{
				float density = FMath::Lerp(initial_fog_density_, new_fog_density_, timer_ / lerp_time_);
				fog_->GetComponent()->SetFogDensity(density);

				float extinction_scale = FMath::Lerp(initial_fog_extinction_scale_, new_fog_exctinction_scale_, timer_ / lerp_time_);
				fog_->GetComponent()->SetVolumetricFogExtinctionScale(extinction_scale);
			}
		}

		if (timer_ / lerp_time_ < 1.0f) {
			LerpSkySphereValues();
		}
	}
}

void AChangeLightTrigger::BeingOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this) && OtherActor->ActorHasTag("Player")) {
		b_start_lerp_ = true;
		if (b_change_directional_light && !b_directional_tick_)
		{
			if (directional_light_)
			{
				b_directional_tick_ = true;
				initial_rotation_ = directional_light_->GetActorRotation();
				initial_directional_intensity_ = directional_light_->GetLightComponent()->Intensity;
			}
		}

		if (b_change_skylight && !b_skylight_tick_)
		{
			if (sky_light_)
			{
				b_skylight_tick_ = true;
				initial_skylight_intensity_ = sky_light_->GetLightComponent()->Intensity;
			}
		}

		if (b_change_fog_ && !b_fog_tick_)
		{
			if (fog_)
			{
				b_fog_tick_ = true;
				initial_fog_density_ = fog_->GetComponent()->FogDensity;
				initial_fog_extinction_scale_ = fog_->GetComponent()->VolumetricFogExtinctionScale;
			}
		}
		SetSkySphereInitialValues();
	}
}