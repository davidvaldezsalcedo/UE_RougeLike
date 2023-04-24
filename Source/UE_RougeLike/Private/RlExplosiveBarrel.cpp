// Fill out your copyright notice in the Description page of Project Settings.


#include "RlExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARlExplosiveBarrel::ARlExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMeshComp"));
	RootComponent = BarrelMeshComp;
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(BarrelMeshComp);
	RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Linear;
	RadialForceComp->Radius = 1000;
	RadialForceComp->ImpulseStrength = 100000;
	RadialForceComp->SetAutoActivate(false);

	BarrelMeshComp->OnComponentHit.AddDynamic(this, &ARlExplosiveBarrel::CreateExplosion);
}

// Called when the game starts or when spawned
void ARlExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARlExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARlExplosiveBarrel::CreateExplosion(UPrimitiveComponent* HitComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}

	RadialForceComp->FireImpulse();
}

