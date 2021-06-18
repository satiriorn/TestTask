// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSphere.h"

// Sets default values
ASpawnSphere::ASpawnSphere()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxX, MaxY, MaxZ, MinX, MinY, MinZ = 0.f;
	CountSphere, Wave = 0;
	MaxCountSphere = 15;
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
		FVector a = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		for (int i = CountSphere; i <= MaxCountSphere; i++) {
			FVector Location;
			Location.Set(a.X + RandomFloat(MaxX, MinX), a.Y + RandomFloat(MaxY, MinY), a.Z + RandomFloat(MaxZ, MinZ));
			v.Add(Location);
			if(i>0){
				for (int j = i; j >= 0; j--){
					if (FVector::Distance(v[i], v[j])<80.f) {
						Location.Set(a.X + RandomFloat(MaxX, MinX), a.Y + RandomFloat(MaxY, MinY), a.Z + RandomFloat(MaxZ, MinZ));
						v[i] = Location;
						j = i;
					}
				}
			}
				FRotator rotation = GetActorRotation();
				World->SpawnActor<ASpawnableSphere>(ActorToSpawn, v[i], rotation);
			
		}
	}
}

float ASpawnSphere::RandomFloat(float& a, float& b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
// Called every frame
void ASpawnSphere::UpPercent(float& value, float percentage_value) {
	value += (value / 100 * (percentage_value));
}
void ASpawnSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnableSphere::StaticClass(), FoundActors);
	if (FoundActors.Num() == 5) {
		v.Empty();
		for (int i = 0; i < FoundActors.Num(); i++) {
			v.Add(FoundActors[i]->GetActorLocation());
		}
		CountSphere = v.Num();
		Wave++;
		float countSphere = float(CountSphere);
		UpPercent(countSphere, 10);
		CountSphere = uint8(countSphere);
		UpPercent(MaxX, 5);
		UpPercent(MaxY, 5);
		UpPercent(MaxZ, 5);
		Spawner();
	}

}

