// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDown/Characters/BasePlayerCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	if (GetCharacterMovement()) 
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;

		GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	}

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyProfile"));
	}

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

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= ActualDamage;

	if (Health <= 0.0f)
	{
		Die();
	}

	return ActualDamage;
}

void ABaseEnemy::Die()
{
	if (PlayerActor)
	{
		ABasePlayerCharacter* Player = Cast<ABasePlayerCharacter>(PlayerActor);

		if (Player)
		{
			Player->RewardPlayer(ExpRewardValue, HpRewardValue);
		}
	}
}