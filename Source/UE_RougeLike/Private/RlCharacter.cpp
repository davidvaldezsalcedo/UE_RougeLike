// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_RougeLike/Public/RlCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARlCharacter::ARlCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ARlCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARlCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARlCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this,&ARlCharacter::MoveForward);
	
	PlayerInputComponent->BindAxis("Turn", this,&APawn::AddControllerYawInput);
}

void ARlCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

