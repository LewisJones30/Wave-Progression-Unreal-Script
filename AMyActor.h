// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMyActor.generated.h"
USTRUCT(BlueprintType)
struct FWaveInformation
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	int32 NumberOfEnemy1ToSpawn;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	int32 NumberOfEnemy2ToSpawn;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	int32 NumberOfEnemy3ToSpawn;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	int32 NumberOfEnemy4ToSpawn;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	int32 NumberOfEnemy5ToSpawn;
	//Set how much time you want between each enemy spawn. For example, 0.5 will spawn 2 enemies per second, or 1 per half second.
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	float TimeBetweenEnemySpawns;
};

UCLASS()
class CPPSCRIPTING_API AAMyActor : public AActor
{
	GENERATED_BODY()
public:	
	//Ensure that this is the same as the number of values in wave control to avoid crashing!

	// Sets default values for this actor's properties
	AAMyActor();
	//Note: You do not have to populate all five of these. It is optional.
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	TSubclassOf<AActor> Enemy1;
	//Note: You do not have to populate all five of these. It is optional.
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	TSubclassOf<AActor> Enemy2;
	//Note: You do not have to populate all five of these. It is optional.
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	TSubclassOf<AActor> Enemy3;
	//Note: You do not have to populate all five of these. It is optional.
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	TSubclassOf<AActor> Enemy4;
	//Note: You do not have to populate all five of these. It is optional.
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	TSubclassOf<AActor> Enemy5;

	//Add a blank actor where you want an enemy to spawn. Use as many or as little as you want.
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	TArray<AActor*>Spawners;

	/*Add each wave manually here.
	You can specify how many of each enemy you want in each wave.
	If you have less than five enemies, ensure that you are matching the counts correctly!*/
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	TArray<FWaveInformation>WaveControl;

	//This is a count of how many waves you have.
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Tower Defence Game");
	int32 MaximumWave = WaveControl.Num();

	TArray<FWaveInformation>* WaveControlP = &WaveControl;
	float TimePerEnemySpawn; //This is a timer that counts down until spawning an enemy.
	float DuplicateTimePerEnemySpawn = TimePerEnemySpawn; //This is used to reset the timer.

	
	int32 CurrentWave = 1;
	//Used to total up how many enemies have been killed in total this wave. Reset when the next wave is triggered. Call this when an enemy is killed.
	int32 EnemiesKilledTotal; 
	//Used to total up how many enemies have been spawned in total this wave. Reset when next wave is triggered.
	int32 EnemiesSpawnedTotal; 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EnemySpawn();
	virtual void NextWave();
	virtual void AllWavesCompleted(); //To be coded by the user.
	FVector ChooseSpawnLocation();
	int64 GetTotalEnemyCountThisWave(); 
	void PostInitProperties();
	void Spawn(int EnemyNumberToSpawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Call this as part of your enemy death script.
	virtual void EnemyKilled(); 
	//Call this if you want a percentage of the enemies defeated.
    float GetProgressionPercentage(); 
	//Call this if you want to get the current wave, E.G for UI.
	int GetCurrentWave();
};
