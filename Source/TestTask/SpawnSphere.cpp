// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSphere.h"

// Sets default values
ASpawnSphere::ASpawnSphere()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxX, MaxY, MaxZ, MinX, MinY, MinZ = 0.f;
	CountSphere = 15;
}

// Called when the game starts or when spawned
void ASpawnSphere::BeginPlay()
{
	Super::BeginPlay();
	Spawner();
}

void ASpawnSphere::Spawner() {
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		FVector Location = GetRandomLocation();
		FRotator rotation = GetActorRotation();
		World->SpawnActor<ASpawnableSphere>(ActorToSpawn, Location, rotation);
	}
}
FVector ASpawnSphere::GetRandomLocation(){
	FVector b;
	FVector a = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	b[0] = a[0] + RandomFloat(MaxX, MinX);
	b[1] = a[1] + RandomFloat(MaxY, MinY);
	b[2] = a[2] + RandomFloat(MaxZ, MinZ);
	return b;
}

float ASpawnSphere::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
// Called every frame
void ASpawnSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnableSphere::StaticClass(), FoundActors);
	if (FoundActors.Num() == 0) {
		for(int i = 0; i<CountSphere;i++){
			Spawner();
		}
	}

}

