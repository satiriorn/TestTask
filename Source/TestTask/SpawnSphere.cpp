// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSphere.h"

// Sets default values
ASpawnSphere::ASpawnSphere()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxX, MaxY, MaxZ, MinX, MinY, MinZ, ReductionStep = 0.f;
	CountSphere, Score = 0;
	Wave = 1;
	MaxCountSphere, LastCountSphere = 15;
	scale.Set(1, 1, 1);
	MinScale.Set(0.3f, 0.3f, 0.3f);
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
		FVector a = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();//get location of the player
		for (int i = CountSphere; i <= MaxCountSphere; i++) {
			FVector Location;
			Location.Set(a.X + RandomFloat(MaxX, MinX), a.Y + RandomFloat(MaxY, MinY), a.Z + RandomFloat(MaxZ, MinZ));//create location sphere
			v.Add(Location);//add location to array sphere
			if(i>0){
				for (int j = i; j >= 0; j--){
					if (FVector::Distance(v[i], v[j])<80.f) {//distance check
						Location.Set(a.X + RandomFloat(MaxX, MinX), a.Y + RandomFloat(MaxY, MinY), a.Z + RandomFloat(MaxZ, MinZ));
						v[i] = Location;
						j = i;
					}
				}
			}
			//spawn actor by the location via sphere array
			FRotator rotation = GetActorRotation();
			if (scale != MinScale) {
				scale.X -= ReductionStep;
				scale.Y -= ReductionStep;
				scale.Z -= ReductionStep;
			}
			World->SpawnActor<ASpawnableSphere>(ActorToSpawn, v[i], rotation)->SetActorScale3D(scale);;
			
		}
		LastCountSphere = v.Num();
	}
}

//randomizer function
float ASpawnSphere::RandomFloat(float& a, float& b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
// Called every frame
void ASpawnSphere::UpPercent(float& value, float percentage_value) {
	value += (value / 100 * (percentage_value));//increase value by percent
}
void ASpawnSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnableSphere::StaticClass(), FoundActors);
	//FString TheFloatStr = FString::SanitizeFloat(LastCountSphere);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, *TheFloatStr);
	if (LastCountSphere > FoundActors.Num()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Score"));
		Score++;
		LastCountSphere = FoundActors.Num();
	}
	if (FoundActors.Num() == 5) {
		v.Empty();
		//save the location of the sphere
		for (int i = 0; i < FoundActors.Num(); i++) {
			v.Add(FoundActors[i]->GetActorLocation());
		}
		//increase data with a new wave
		CountSphere = v.Num();
		Wave++;
		float maxcountSphere = float(MaxCountSphere);
		UpPercent(maxcountSphere, 10);
		MaxCountSphere = uint8(maxcountSphere);
		LastCountSphere = uint16(MaxCountSphere);
		UpPercent(MaxX, 5);
		UpPercent(MaxY, 5);
		UpPercent(MaxZ, 5);
		Spawner();

	}


}	

