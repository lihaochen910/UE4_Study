// Fill out your copyright notice in the Description page of Project Settings.

#include "FallingActor.h"


// Sets default values
AFallingActor::AFallingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));

	CubeMesh->SetSimulatePhysics(true);

	CubeMesh->OnComponentHit.AddDynamic(this, &AFallingActor::OnHit);
}

void AFallingActor::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, OtherActor->GetName());

	CubeMesh->AddImpulse(FVector(0, 0, strength), FName(TEXT("None")), true);

	//CubeMesh->AddRadialImpulse(GetActorLocation(), r, strength, ERadialImpulseFalloff::RIF_Linear, true);
}

//void AFallingActor::ReceiveHit(UPrimitiveComponent * MyComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
//{
//
//}

// Called when the game starts or when spawned
void AFallingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFallingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

