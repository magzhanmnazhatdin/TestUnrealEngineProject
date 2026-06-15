// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, true);
	
}

void AEnemySpawner::SpawnEnemy()
{
	if (!EnemyClassToSpawn) return;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn) return;

	FVector PlayerLocation = PlayerPawn->GetActorLocation();

	float RandomAngle = FMath::FRandRange(0.0f, 2.0f * PI);

	FVector SpawnOffset(FMath::Cos(RandomAngle) * SpawnRadius, FMath::Sin(RandomAngle) * SpawnRadius, 0.0f);
	FVector FinalSpawnLocation = PlayerLocation + SpawnOffset;

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ABaseEnemy>(EnemyClassToSpawn, FinalSpawnLocation, FRotator::ZeroRotator, SpawnParams);
}

