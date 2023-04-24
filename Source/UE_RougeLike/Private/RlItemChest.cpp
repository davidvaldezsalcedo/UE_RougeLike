// Fill out your copyright notice in the Description page of Project Settings.


#include "RlItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARlItemChest::ARlItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	LidTargetPitch = 110;
}

// Called when the game starts or when spawned
void ARlItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARlItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARlItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(LidTargetPitch,0,0));
}

