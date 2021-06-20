// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "SpawnableSphere.generated.h"

UCLASS()
class TESTTASK_API ASpawnableSphere : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnableSphere();
	UStaticMeshComponent * SphereMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystemComponent* PSC;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeDestroy;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool destroy = false;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};