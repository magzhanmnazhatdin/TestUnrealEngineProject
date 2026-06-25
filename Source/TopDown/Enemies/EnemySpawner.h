// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TOPDOWN_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<class ABaseEnemy> EnemyClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnRadius = 1500.0f;

	void SpawnEnemy();

private:
	FTimerHandle SpawnTimerHandle;

	AActor* PlayerActor;
};
