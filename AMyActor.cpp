// Fill out your copyright notice in the Description page of Project Settings.


#include "AMyActor.h"
#include "Actor.h"
#include <Math/UnrealMathUtility.h>
template< class T >
T* SpawnActor
(
    AActor* Owner = NULL,
    APawn* Instigator = NULL,
    bool bNoCollisionFail = false
)
{
    return (T*)(GetWorld()->SpawnActor(T::StaticClass(), NAME_None, NULL, NULL, NULL, bNoCollisionFail, false, Owner, Instigator));
}

// Sets default values
AAMyActor::AAMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAMyActor::BeginPlay()
{
    TimePerEnemySpawn = WaveControl[0].TimeBetweenEnemySpawns;
    DuplicateTimePerEnemySpawn = TimePerEnemySpawn;
	Super::BeginPlay();
	
}

// Called every frame
void AAMyActor::Tick(float DeltaTime)
{
    TimePerEnemySpawn = TimePerEnemySpawn - DeltaTime;
    if (TimePerEnemySpawn <= 0)
    {
        TimePerEnemySpawn = 5;
        EnemySpawn();
    }

	Super::Tick(DeltaTime);


}

void AAMyActor::EnemySpawn()
{
    bool SpawnReady = false; //Only set active if the count in the specific wave allows it.

    int64 AllEnemyCount = WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn + WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn + WaveControl[CurrentWave - 1].NumberOfEnemy3ToSpawn + WaveControl[CurrentWave - 1].NumberOfEnemy4ToSpawn + WaveControl[CurrentWave - 1].NumberOfEnemy5ToSpawn;
    if (EnemiesSpawnedTotal == AllEnemyCount)
    {
        SpawnReady = true;
        return;
    }
    while (SpawnReady == false)
    {
        int EnemyToSpawn = rand() % 5 + 1; //Between 1 and 5.
        switch (EnemyToSpawn)
        {
        case 1:
        {
            if (WaveControl[CurrentWave - 1].NumberOfEnemy1ToSpawn > 0)
            {
                Spawn(1);
                SpawnReady = true;
                break;
            }
            else
            {
                break;
            }
        }
        case 2:
        {
            if (WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn > 0)
            {
                Spawn(2);
                SpawnReady = true;
                break;
            }
            else
            {
                break;
            }
        }
        case 3:
        if (WaveControl[CurrentWave - 1].NumberOfEnemy3ToSpawn > 0)
        {
            Spawn(3);
            SpawnReady = true;
            break;
        }
        else
        {
            break;
        }
        case 4:
        if (WaveControl[CurrentWave - 1].NumberOfEnemy4ToSpawn > 0)
        {
            Spawn(4);
            SpawnReady = true;
            break;
        }
        else
        {
            break;
        }
        case 5:
        {
            if (WaveControl[CurrentWave - 1].NumberOfEnemy5ToSpawn > 0)
            {
                Spawn(5);
                SpawnReady = true;
                break;
            }
            else
            {
                break;
            }
        }
        }
    }




}
//This script is run to reduce duplicate code. Error checking included.
//If you are having problems spawning enemies, please check the output log!
void AAMyActor::Spawn(int EnemyNumberToSpawn)
{
    float value = rand() % 3;
    FVector Location(ChooseSpawnLocation());
    FRotator Rotation(0.0f, 0.0f, 0.0f);
    FActorSpawnParameters SpawnInfo;
    switch (EnemyNumberToSpawn)
    {
    case 1:
    {
        if (Enemy1->IsValidLowLevel())
        {
            AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(Enemy1, Location, Rotation, SpawnInfo);
            EnemiesSpawnedTotal = EnemiesSpawnedTotal + 1;
            WaveControl[CurrentWave - 1].NumberOfEnemy1ToSpawn = WaveControl[CurrentWave - 1].NumberOfEnemy1ToSpawn - 1;
            return;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemy1 is not valid, but you are attempting to spawn this enemy. Please check if Enemy1's slot is correct!\nNo enemies have been spawned to prevent crashing."));
            return;
        }
    }
    case 2:
    {
        if (Enemy2->IsValidLowLevel())
        {
            AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(Enemy2, Location, Rotation, SpawnInfo);
            EnemiesSpawnedTotal = EnemiesSpawnedTotal + 1;
            WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn = WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn - 1;
            return;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemy2 is not valid, but you are attempting to spawn this enemy. Please check if Enemy2's slot is correct!\nNo enemies have been spawned to prevent crashing."));
            return;
        }
    }
    case 3:
    {
        if (Enemy3->IsValidLowLevel())
        {
            AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(Enemy2, Location, Rotation, SpawnInfo);
            EnemiesSpawnedTotal = EnemiesSpawnedTotal + 1;
            WaveControl[CurrentWave - 1].NumberOfEnemy3ToSpawn = WaveControl[CurrentWave - 1].NumberOfEnemy3ToSpawn - 1;
            return;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemy3 is not valid, but you are attempting to spawn this enemy. Please check if Enemy3's slot is correct!\nNo enemies have been spawned to prevent crashing."));
            return;
        }
    }
    case 4:
    if (Enemy4->IsValidLowLevel())
    {
        AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(Enemy4, Location, Rotation, SpawnInfo);
        EnemiesSpawnedTotal = EnemiesSpawnedTotal + 1;
        WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn = WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn - 1;
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Enemy4 is not valid, but you are attempting to spawn this enemy. Please check if Enemy4's slot is correct!\nNo enemies have been spawned to prevent crashing."));
        return;
    }
    case 5:
    {
        if (Enemy2->IsValidLowLevel())
        {
            AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(Enemy2, Location, Rotation, SpawnInfo);
            EnemiesSpawnedTotal = EnemiesSpawnedTotal + 1;
            WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn = WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn - 1;
            return;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemy5 is not valid, but you are attempting to spawn this enemy. Please check if Enemy5's slot is correct!\nNo enemies have been spawned to prevent crashing."));
            return;
        }
    }
    default:
    {
        UE_LOG(LogTemp, Warning, TEXT("Default triggered in Spawn() method. Should not ever occur!"));
    }
    }
}


//Small script to determine where the location of spawn should be.
//This script will ensure that a random spawner is selected, regardless of the slot number.
//If you are having issues with the spawning, please check output log in Window -> Developer Tools -> Output Log.
FVector AAMyActor::ChooseSpawnLocation()
{
    if (Spawners.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawn count is zero. Please add another spawner. Spawning enemy in location (0, 0, 0) as a fallback!"));
        return FVector(0, 0, 0);
    }
    int32 SpawnerChosen = rand() % Spawners.Num();
    if (Spawners[SpawnerChosen]->IsValidLowLevel())
    {
        FVector returnValue = Spawners[SpawnerChosen]->GetActorLocation();
        return returnValue;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Error: Spawner object has not been populated correctly. Please check all spawners.\n Spawning enemy in location (0, 0, 0) as a fallback!"));
        return FVector(0, 0, 0);
    }
}


void AAMyActor::EnemyKilled()
{
    EnemiesKilledTotal = EnemiesKilledTotal + 1;
    if (EnemiesKilledTotal == GetTotalEnemyCountThisWave())
    {
        NextWave();
    }
}
void AAMyActor::NextWave()
{
    EnemiesKilledTotal = 0;
    EnemiesSpawnedTotal = 0;
    CurrentWave += 1;
    if (CurrentWave > MaximumWave)
    {
        AllWavesCompleted();
        //Any extra code can be inserted here.
        return;
    }
    TimePerEnemySpawn = WaveControl[CurrentWave - 1].TimeBetweenEnemySpawns;
}

void AAMyActor::AllWavesCompleted()
{
    //Code what you want your game to do here.
}


void AAMyActor::PostInitProperties()
{
    Super::PostInitProperties();
    MaximumWave = WaveControl.Num();
}

//Getters

int AAMyActor::GetCurrentWave()
{
    return CurrentWave;
}

float AAMyActor::GetProgressionPercentage()
{
    return 0.f;
}
int64 AAMyActor::GetTotalEnemyCountThisWave()
{
    int64 AllEnemyCount = WaveControl[CurrentWave - 1].NumberOfEnemy1ToSpawn + WaveControl[CurrentWave - 1].NumberOfEnemy2ToSpawn + WaveControl[CurrentWave - 1].NumberOfEnemy3ToSpawn + WaveControl[CurrentWave - 1].NumberOfEnemy4ToSpawn + WaveControl[CurrentWave - 1].NumberOfEnemy5ToSpawn;
    return AllEnemyCount;
}
