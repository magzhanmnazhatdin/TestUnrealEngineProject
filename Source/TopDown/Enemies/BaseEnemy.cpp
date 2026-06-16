// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerActor = UGameplayStatics::GetPlayerPawn(this, 0);

	if (GetCharacterMovement()) 
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerActor)
	{
		FVector Direction = PlayerActor->GetActorLocation() - GetActorLocation();

		Direction.Z = 0.0f;

		Direction.Normalize();

		AddMovementInput(Direction, 1.0f);
	}

}