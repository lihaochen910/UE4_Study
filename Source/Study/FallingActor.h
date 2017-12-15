// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Core.h"
#include "GameFramework/Actor.h"
#include "FallingActor.generated.h"

UCLASS()
class STUDY_API AFallingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingActor();

	UPROPERTY(EditAnywhere)
		float r = 10;
	UPROPERTY(EditAnywhere)
		float strength = 10;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CubeMesh;

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);

	/*UFUNCTION()
		void ReceiveHit(UPrimitiveComponent * MyComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);
*/
protected:
	// Called when the game starts or when spawned 
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
