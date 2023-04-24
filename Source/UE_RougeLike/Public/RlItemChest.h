// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RlGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RlItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class UE_ROUGELIKE_API ARlItemChest : public AActor, public IRlGameplayInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float LidTargetPitch;
	
	void Interact_Implementation(APawn* InstigatorPawn);
	
protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	ARlItemChest();

};
