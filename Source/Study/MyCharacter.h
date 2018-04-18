// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Core.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "UFSM.h"
#include "MyCharacter.generated.h"

UCLASS()
class STUDY_API AMyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCharacter();

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* IdleAnimation;
	UPROPERTY(EditAnywhere)
		UPaperFlipbook* RunAnimation;

	UFUNCTION()
		void OnHorizontal(float val);
	UFUNCTION()
		void OnVertical(float val);

private:
	UPROPERTY(VisibleDefaultsOnly)
		UCharacterMovementComponent* p_movementComponent;
	UPROPERTY(VisibleDefaultsOnly)
		UCameraComponent* p_camera;
	UPROPERTY(VisibleDefaultsOnly)
		UPaperFlipbookComponent* p_characterAnimator;
	UPROPERTY()
		UStateMachineComponent* p_stateMachine;

private:
	float horizontalAxis, verticalAxis;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FName Idle = FName("Idle");
	FName Run = FName("Run");

public:
	UFUNCTION()
		void BindBeginIdle();
	UFUNCTION()
		void BindUpdateIdle();

	UFUNCTION()
		void BindBeginRun();
	UFUNCTION()
		void BindUpdateRun();
};
