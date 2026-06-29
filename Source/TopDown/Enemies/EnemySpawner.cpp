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

	PlayerActor = UGameplayStatics::GetPlayerPawn(this, 0);

	if (GetWorld()) 
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, true);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	if (!EnemyClassToSpawn || !PlayerActor) return;

	FVector PlayerLocation = PlayerActor->GetActorLocation();

	float RandomAngle = FMath::FRandRange(0.0f, 2.0f * PI);

	float SpawnX = PlayerLocation.X + (SpawnRadius * FMath::Cos(RandomAngle));
	float SpawnY = PlayerLocation.Y + (SpawnRadius * FMath::Sin(RandomAngle));

	FVector SpawnLocation(SpawnX, SpawnY, PlayerLocation.Z + 500.0f);

	FHitResult HitResult;
	FVector Start = SpawnLocation;
	FVector End = SpawnLocation - FVector(0.0f, 0.0f, 1500.0f);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(PlayerActor);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
	{
		SpawnLocation.Z = HitResult.ImpactPoint.Z + 90.0f;
	}
	else
	{
		SpawnLocation.Z = PlayerLocation.Z;
	}

	FRotator SpawnRotation = (PlayerLocation - SpawnLocation).Rotation();
	SpawnRotation.Pitch = 0.0f;
	SpawnRotation.Roll = 0.0f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<ABaseEnemy>(EnemyClassToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

}

