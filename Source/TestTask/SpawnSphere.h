// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "SpawnableSphere.h"
#include "TestTaskCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnSphere.generated.h"

UCLASS()
class TESTTASK_API ASpawnSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Spawner();
	float RandomFloat(float& a, float& b);
	TArray<AActor*> FoundActors;
	TArray<FVector> v;
	void UpPercent(float& value, float percentage_value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//location sphere variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		float MinX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorSpawn)
		TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		float MaxX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		float MinY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		float MaxY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		float MinZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		float MaxZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
		uint8 CountSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
		uint8 Wave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
		uint8 MaxCountSphere;

};
