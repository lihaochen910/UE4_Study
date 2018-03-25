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
	
	p_movementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	p_movementComponent->SetUpdatedComponent(RootComponent);
	p_movementComponent->MaxSpeed = 500.0f;
	p_movementComponent->Acceleration = p_movementComponent->MaxSpeed * 5;
	p_movementComponent->Deceleration = p_movementComponent->MaxSpeed * 5;

	p_camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	p_camera->AttachTo(RootComponent);
	p_camera->SetWorldRotation(FVector(0,-90,0).Rotation());
	p_camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	p_camera->OrthoWidth = 1500;

	p_characterVisual = CreateDefaultSubobject<UPaperSpriteComponent>("SpriteComponent");
	p_characterVisual->AttachTo(RootComponent);
	p_characterVisual->SetRelativeLocation(FVector(0,0,-7));

	p_characterAnimatorVisual = CreateDefaultSubobject<UPaperFlipbookComponent>("SpriteAnimator");
	p_characterAnimatorVisual->AttachTo(RootComponent);
}

void AMyCharacter::OnHorizontal(float val)
{
	if (val != 0.0f)
	{
		p_characterAnimatorVisual->SetFlipbook(RunAnimation);

		if (val > 0) {
			p_characterAnimatorVisual->SetRelativeScale3D(FVector::OneVector);
		}
		else {
			p_characterAnimatorVisual->SetRelativeScale3D(FVector(-1,1,1));
		}
	}
	else {
		p_characterAnimatorVisual->SetFlipbook(IdleAnimation);
	}

	AddMovementInput(FVector(val, 0, 0));
}

void AMyCharacter::OnVertical(float val)
{
	AddMovementInput(FVector(0, 0, val));
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

