// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS()
class TOPDOWN_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInsigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	AActor* PlayerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Speed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	float ExpRewardValue = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	float HpRewardValue = 0.0f;

	void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
