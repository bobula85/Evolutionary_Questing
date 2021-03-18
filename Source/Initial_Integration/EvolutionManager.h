// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EvolutionManager.generated.h"

class AInitial_IntegrationCharacter;
class UQuestManager;
class UQuest;

// holds pointers to a pair of parents

USTRUCT(BlueprintType)
struct Ffrequency_Count
{
	GENERATED_BODY()

///////////////////////////		Selection Population Stats		/////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int KillCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float KillFreq = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float KillChange = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int FetchCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float FetchFreq = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float FetchChange = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int GatherCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float GatherFreq = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float GatherChange = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int ExploreCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float ExploreFreq = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float ExploreChange = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int CloseCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float CloseFreq = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float CloseChange = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int MidCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float MidFreq = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float MidChange = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int FarCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float FarFreq = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float FarChange = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	bool lowTypeFreq = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	bool lowDistFreq = false; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	TArray<int> LowTypeFreqs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	TArray<int> LowDistFreqs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	TArray<float> TypeFreqs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	TArray<float> DistFreqs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int highestType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int highestDist;
};

USTRUCT(BlueprintType)
struct FPair
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	UQuest* p1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	UQuest* p2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	UQuest* c1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	UQuest* c2;
};

USTRUCT(BlueprintType)
struct FPair_SaveItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int x;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int y;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int DistBanding;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int Type;
};

USTRUCT(BlueprintType)
struct FPair_SaveItems
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	FPair_SaveItem p1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	FPair_SaveItem p2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	FPair_SaveItem c1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	FPair_SaveItem c2;
};

USTRUCT(BlueprintType)
struct FPair_SaveGeneration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	TArray<FPair_SaveItems> GenerationPairs;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int GenerationNumber;
};

USTRUCT(BlueprintType)
struct FGenerationData
{
	GENERATED_BODY()
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int Generation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int Stage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int PercentageKill;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int PercentageFetch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int PercentageGather;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int PercentageExplore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int PercentageClose;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int PercentageMid;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair_SaveItem")
	int PercentageFar;

};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INITIAL_INTEGRATION_API UEvolutionManager : public UActorComponent
{

	GENERATED_BODY()
	
public:	

	//UEvolutionManager();

	// Sets default values for this actor's properties
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Init(AInitial_IntegrationCharacter* p, UQuestManager* mgr);
	//! A function that initiates the evolutionary process.
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void EvolveQuests();

	//! A function which evaluates the the populations solutions.
	/*!
		Takes the a pointer to the quest that requires evaluation.
		\param qst a Quest pointer for quest object.
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Evaluate(UQuest* qst);

	//! A function which selects parents usinf the roulette selection method.
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void SelectRoulette();

	//! A function which selects parents using the ranked selection method.
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void SelectRanked();

	//! A function which creates new solutions from the parents selected in SelectionRoulette() and SelectRanked().
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Combine();

	//! A function which calculates the frequecy of each quest element type.
	/*!
	*/
	void CalculateFrequencySel(Ffrequency_Count* count);

	//! A function which calculates the frequecy of each quest element type.
	/*!
	*/
	void CalculateFrequencyFin(Ffrequency_Count* count);

	//! A function which creates new solutions from the parents selected in SelectionRoulette() and SelectRanked().
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Mutate();

	//! A function which selects soultions created in Combine() to be added to the population.
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Survive();

	void DisplayChangeSel();

	void DisplayChangeFin();

	//! A function outputs evolutionary data to a .csv file.
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void OutputResult();

	//! A function calculates the percentages of population elements.
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void CalculateData(int gen, int stage, TArray<UQuest*> &questArray);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	TArray<UQuest*> children;		/*!< A vector of type Quest* which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	TArray<FPair> parents;			/*!< A vector of type quest which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	AInitial_IntegrationCharacter* player;		/*!< A pointer of type Player* which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	UQuestManager* questMgr;				/*!< A pointer of QuestManager* which holds all quest information. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int maxPairs;				/*!< An integer which declares the maximum amount of mating pairs that can be selected for breeding. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int maxChildren;			/*!< An integer which declares the maximum amount of children that can be created per evolution. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int maxPopulation;			/*!< An integer which declares the maximum size of the population. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int ReintroRate;			/*!< An integer used to trigger mutation of quest elements. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int evolutionNumber; 				/*!< An integer which declares the total number of evolutions that have taken place so far. */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	TArray<FPair_SaveItem> EvoPairItems;			/*!< A vector of type quest which holds the players accepted quests. */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	TArray<FPair_SaveGeneration> EvoGenerations;			/*!< A vector of type quest which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	TArray<FGenerationData> EvoGenerationData;			/*!< A vector of type quest which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	Ffrequency_Count CurrentFreqInfoSel;					/*!< A structure that holds the current populations frequency information. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	Ffrequency_Count PreviousFreqInfoSel;					/*!< A structure that holds the previous populations frequency information. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	Ffrequency_Count CurrentFreqInfoFin;					/*!< A structure that holds the current populations frequency information. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	Ffrequency_Count PreviousFreqInfoFin;					/*!< A structure that holds the previous populations frequency information. */

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
