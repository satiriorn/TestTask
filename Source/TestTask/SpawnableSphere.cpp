// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableSphere.h"

// Sets default values
ASpawnableSphere::ASpawnableSphere()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	SphereMesh->OnComponentHit.AddDynamic(this, &ASpawnableSphere::OnHit);
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnableSphere::BeginPlay()
{
	Super::BeginPlay();

}

//a function that triggers a hit and destroy actor(sphere)
void ASpawnableSphere::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("hit"));
}

// Called every frame
void ASpawnableSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

