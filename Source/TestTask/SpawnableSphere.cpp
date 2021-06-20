// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableSphere.h"

// Sets default values
ASpawnableSphere::ASpawnableSphere()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	RootComponent = SphereMesh;
	SphereMesh->OnComponentHit.AddDynamic(this, &ASpawnableSphere::OnHit);
	//set particle system
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/effect/bang.bang'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(RootComponent);
	PSC->SetVisibility(false);
	TimeDestroy = 0.5f;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnableSphere::BeginPlay()
{
	Super::BeginPlay();

}

//a function that triggers a hit and destroy actor(sphere)
void ASpawnableSphere::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("hit"));
	PSC->SetVisibility(true);
	destroy = true;
}

// Called every frame
void ASpawnableSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//count time to destroy
	if (TimeDestroy <=0 && destroy)
		Destroy();
	else if (destroy)
		TimeDestroy -= DeltaTime;
}

