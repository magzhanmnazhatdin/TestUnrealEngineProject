// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

