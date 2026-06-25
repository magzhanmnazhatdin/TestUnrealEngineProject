// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	}
	
}

void ABasePlayerCharacter::RewardPlayer(float ExpReward, float HpReward)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HpReward, 0.0f, MaxHealth);

	CurrentExp += ExpReward;

	while (CurrentExp >= ExpToLevelUp)
	{
		CurrentExp -= ExpToLevelUp;
		LevelUp();
	}
}

void ABasePlayerCharacter::LevelUp()
{
	CurrentLevel++;

	CurrentHealth = MaxHealth;

	ExpToLevelUp *= 1.2f;

	UE_LOG(LogTemp, Warning, TEXT("Level UP! Current level: %d"), CurrentLevel);
}

