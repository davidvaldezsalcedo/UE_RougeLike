// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_RougeLike/Public/RlCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "RlInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARlCharacter::ARlCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<URlInteractionComponent>(TEXT("InteractionComp"));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
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

	// Rotation Visualization
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of the pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(),LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

// Called to bind functionality to input
void ARlCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this,&ARlCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this,&ARlCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis(TEXT("Turn"), this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ARlCharacter::Jump);
	
	PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ARlCharacter::PrimaryAttack);
	
	PlayerInputComponent->BindAction(TEXT("PrimaryInteract"), IE_Pressed, this, &ARlCharacter::PrimaryInteract);
}

void ARlCharacter::MoveForward(float value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;
	
	AddMovementInput(controlRot.Vector(), value);
}

void ARlCharacter::MoveRight(float value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;

	FVector rightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(rightVector, value);
}

void ARlCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimeHandle_PrimaryAttack, this, &ARlCharacter::PrimaryAttack_TimeElapsed, 0.2f);

	// GetWorldTimerManager().ClearTimer(TimeHandle_PrimaryAttack);
}

void ARlCharacter::PrimaryAttack_TimeElapsed()
{
	FVector handLocation = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	FTransform spawnTM = FTransform(GetControlRotation(), handLocation);

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, spawnTM, spawnParams);	
}

void ARlCharacter::PrimaryInteract()
{
	if(InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

