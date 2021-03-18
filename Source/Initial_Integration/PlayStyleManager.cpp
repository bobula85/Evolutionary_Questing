// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayStyleManager.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
void UPlayStyleManager::Init()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	compMultiplier = 1.2;
	inCompMultiplier = 1.0;
	abnMultiplier = 0.8;
	rejMultiplier = 1.3;

	int baseValue = 1; 

	// Initiale all player preference statistics to 1
	Kill_Com = baseValue;
	Gather_Com = baseValue;
	Fetch_Com = baseValue;
	Explore_Com = baseValue;

	Kill_InCom = baseValue;
	Gather_InCom = baseValue;
	Fetch_InCom = baseValue;
	Explore_InCom = baseValue;

	Kill_Abn = baseValue;
	Gather_Abn = baseValue;
	Fetch_Abn = baseValue;
	Explore_Abn = baseValue;

	Kill_Rej = baseValue;
	Gather_Rej = baseValue;
	Fetch_Rej = baseValue;
	Explore_Rej = baseValue;

	Close_Com = baseValue;
	Mid_Com = baseValue;
	Far_Com = baseValue;

	Close_InCom = baseValue;
	Mid_InCom = baseValue;
	Far_InCom = baseValue;

	Close_Abn = baseValue;
	Mid_Abn = baseValue;
	Far_Abn = baseValue;

	Close_Rej = baseValue;
	Mid_Rej = baseValue;
	Far_Rej = baseValue;


	Kill_Fitness = 1;
	Gather_Fitness = 1;
	Fetch_Fitness = 1;
	Explore_Fitness = 1;
	
	Close_Fitness = 1;
	Mid_Fitness = 1;
	Far_Fitness = 1;
}

// Called when the game starts or when spawned
//void UPlayStyleManager::BeginPlay()
//{
//	Super::BeginPlay();
	
//}

// Called every frame
//void UPlayStyleManager::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

void UPlayStyleManager::CalculateFitness()
{
	// Calculate fitness using player preference statisics eg fitness = (((Completed*2) + Incomplete) - Abandoned - (Rejected*2))
	Kill_Fitness = (((Kill_Com * compMultiplier) + Kill_InCom * inCompMultiplier) - ((Kill_Abn * abnMultiplier) + (Kill_Rej*rejMultiplier)));
	if (Kill_Fitness <= 0)
		Kill_Fitness = 1;

	Gather_Fitness = (((Gather_Com * compMultiplier) + Gather_InCom * inCompMultiplier) - ((Gather_Abn * abnMultiplier) + (Gather_Rej * rejMultiplier)));
	if (Gather_Fitness <= 0)
		Gather_Fitness = 1;

	Fetch_Fitness = (((Fetch_Com * compMultiplier) + Fetch_InCom * inCompMultiplier) - ((Fetch_Abn * abnMultiplier) + (Fetch_Rej * rejMultiplier)));
	if (Fetch_Fitness <= 0)
		Fetch_Fitness = 1;

	Explore_Fitness = (((Explore_Com * compMultiplier) + Explore_InCom * inCompMultiplier) - ((Explore_Abn * abnMultiplier) + (Explore_Rej * rejMultiplier)));
	if (Explore_Fitness <= 0)
		Explore_Fitness = 1;
	
	Close_Fitness = (((Close_Com * compMultiplier) + Close_InCom * inCompMultiplier) - ((Close_Abn * abnMultiplier) + (Close_Rej * rejMultiplier)));
	if (Close_Fitness <= 0)
		Close_Fitness = 1;

	Mid_Fitness = (((Mid_Com * compMultiplier) + Mid_InCom * inCompMultiplier) - ((Mid_Abn * abnMultiplier) + (Mid_Rej * rejMultiplier)));
	if (Mid_Fitness <= 0)
		Mid_Fitness = 1;

	Far_Fitness = (((Far_Com * compMultiplier) + Far_InCom * inCompMultiplier) - ((Far_Abn * abnMultiplier) + (Far_Rej * rejMultiplier)));
	if (Far_Fitness <= 0)
		Far_Fitness = 1;


}