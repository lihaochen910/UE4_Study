// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* collision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = collision;
	collision->SetSphereRadius(28.0f);
	collision->RelativeLocation = FVector(0, 0, 0);
	
	p_movementComponent = CreateDefaultSubobject<UCharacterMovementComponent>("Movement");
	p_movementComponent->SetUpdatedComponent(RootComponent);
	/*p_movementComponent->MaxSpeed = 500.0f;
	p_movementComponent->Acceleration = p_movementComponent->MaxSpeed * 5;
	p_movementComponent->Deceleration = p_movementComponent->MaxSpeed * 5;*/

	p_camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	p_camera->AttachTo(RootComponent);
	p_camera->SetWorldRotation(FVector(0,-90,0).Rotation());
	p_camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	p_camera->OrthoWidth = 1500;

	p_characterAnimator = CreateDefaultSubobject<UPaperFlipbookComponent>("SpriteAnimator");
	p_characterAnimator->AttachTo(RootComponent);

	p_stateMachine = CreateDefaultSubobject<UStateMachineComponent>("StateMachine");
	if (p_stateMachine->IsValidLowLevel())
	{
		p_stateMachine->AddState(0, Idle);
		p_stateMachine->AddState(1, Run);
		p_stateMachine->AddState(2, FName("Push"));

		p_stateMachine->GetStateRef(Idle).OnBeginState.AddDynamic(this, &AMyCharacter::BindBeginIdle);
		p_stateMachine->GetStateRef(Idle).OnUpdateState.AddDynamic(this, &AMyCharacter::BindUpdateIdle);

		p_stateMachine->GetStateRef(Run).OnBeginState.AddDynamic(this, &AMyCharacter::BindBeginRun);
		p_stateMachine->GetStateRef(Run).OnUpdateState.AddDynamic(this, &AMyCharacter::BindUpdateRun);

		p_stateMachine->SetActive(true, true);
		p_stateMachine->bAutoActivate = true;
		p_stateMachine->Debug = true;
	}
}

void AMyCharacter::OnHorizontal(float val)
{
	horizontalAxis = val;

	/*if (val != 0.0f)
	{
		p_characterAnimator->SetFlipbook(RunAnimation);

		if (val > 0) {
			p_characterAnimator->SetRelativeScale3D(FVector::OneVector);
		}
		else {
			p_characterAnimator->SetRelativeScale3D(FVector(-1,1,1));
		}
	}
	else {
		p_characterAnimator->SetFlipbook(IdleAnimation);
	}

	AddMovementInput(FVector(val, 0, 0));*/
}

void AMyCharacter::OnVertical(float val)
{
	verticalAxis = val;
	//AddMovementInput(FVector(0, 0, val));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &AMyCharacter::OnHorizontal);
	InputComponent->BindAxis("Vertical", this, &AMyCharacter::OnVertical);

}

// ********************************************************************
// Idle
// ********************************************************************
void AMyCharacter::BindBeginIdle()
{
	p_characterAnimator->SetFlipbook(IdleAnimation);
}
void AMyCharacter::BindUpdateIdle()
{
	if (horizontalAxis != 0)
		p_stateMachine->SetState(Run);
}

// ********************************************************************
// Run
// ********************************************************************

void AMyCharacter::BindBeginRun()
{
	p_characterAnimator->SetFlipbook(RunAnimation);
}

void AMyCharacter::BindUpdateRun()
{
	if (horizontalAxis == 0)
		p_stateMachine->SetState(Idle);

	if (horizontalAxis > 0) {
		p_characterAnimator->SetRelativeScale3D(FVector::OneVector);
	}
	else {
		p_characterAnimator->SetRelativeScale3D(FVector(-1, 1, 1));
	}

	AddMovementInput(FVector(horizontalAxis, 0, 0));
}

