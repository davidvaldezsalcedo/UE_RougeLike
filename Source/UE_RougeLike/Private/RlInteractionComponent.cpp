// Fill out your copyright notice in the Description page of Project Settings.


#include "RlInteractionComponent.h"
#include "RlGameplayInterface.h"

// Sets default values for this component's properties
URlInteractionComponent::URlInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URlInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URlInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URlInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* myOwner = GetOwner();
	
	FVector eyeLocation;
	FRotator eyeRotation;
	myOwner->GetActorEyesViewPoint(eyeLocation, eyeRotation);
	
	FVector endPos = eyeLocation + (eyeRotation.Vector() * 1000);
	
	/*FHitResult hit;
	bool didBlockingHit = GetWorld()->LineTraceSingleByObjectType(hit, eyeLocation, endPos, objectQueryParams);*/

	TArray<FHitResult> hits;

	float radius = 30.0f;
	
	FCollisionShape shape;
	shape.SetSphere(radius);
	
	bool didBlockingHit = GetWorld()->SweepMultiByObjectType(hits, eyeLocation, endPos, FQuat::Identity, objectQueryParams, shape);

	FColor lineColor = didBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult hit : hits)
	{
		AActor* hitActor = hit.GetActor();
		if(hitActor)
		{
			if(hitActor->Implements<URlGameplayInterface>())
			{
				APawn* myPawn = Cast<APawn>(myOwner);
				IRlGameplayInterface::Execute_Interact(hitActor, myPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), hit.ImpactPoint, radius, 32, lineColor, false, 2.0f);
	}	
	DrawDebugLine(GetWorld(), eyeLocation, endPos, lineColor, false, 2.0f, 0, 2.0f);
}
