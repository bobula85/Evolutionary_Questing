// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EvolutionManager.generated.h"

class AInitial_IntegrationCharacter;
class UQuestManager;
class UQuest;

// Struct used to contain all population statistical data
USTRUCT(BlueprintType)
struct Ffrequency_Count
{
	GENERATED_BODY()

///////////////////////////		Selection Population Stats		/////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int KillCount = 0;			/**< Integer value of total number of kill quests */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float KillFreq = 0;			/**< Float value of kill quests frequency in the population */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float KillChange = 0;		/**< Float value of change to kill quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int FetchCount = 0;			/**< Integer value of total number of fetch quests */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float FetchFreq = 0;		/**< Float value of fetch quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float FetchChange = 0;		/**< Float value of change to fetch quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int GatherCount = 0;		/**< Integer value of total number of gather quests */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float GatherFreq = 0;		/**< Float value of gather quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float GatherChange = 0;		/**< Float value of change to gather quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int ExploreCount = 0;		/**< Integer value of total number of explore quests */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float ExploreFreq = 0;		/**< Float value of expolre quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float ExploreChange = 0;	/**< Float value of change to explore quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int CloseCount = 0;			/**< Integer value of total number of close quests */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float CloseFreq = 0;		/**< Float value of close quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float CloseChange = 0;		/**< Float value of change to close quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int MidCount = 0;			/**< Integer value of total number of mid quests */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float MidFreq = 0;			/**< Float value of mid quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float MidChange = 0;		/**< Float value of change to mid quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int FarCount = 0;			/**< Integer value of total number of far quests */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float FarFreq = 0;			/**< Float value of far quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	float FarChange = 0;		/**< Float value of change to far quests frequency in the population */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	bool lowTypeFreq = false;	/**< Bool value used to show low frequency of a quest type */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	bool lowDistFreq = false;	/**< Bool value used to show low frequency of a quest distance */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	TArray<int> LowTypeFreqs;	/**< Array of low type frequencies */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	TArray<int> LowDistFreqs;	/**< Array of low distance frequencies */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	TArray<float> TypeFreqs;	/**< Array of all type frequencies */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	TArray<float> DistFreqs;	/**< Array of all distance frequencies */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int highestType;			/**< Array of all distance frequencies */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoFreqCount")
	int highestDist;			/**< Array of all distance frequencies */
};

/**< Data strucute that hold a pair of parent quests and the two resulting child quests */
USTRUCT(BlueprintType)
struct FPair
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	UQuest* p1;					/**< Quest poniter to parent quest 1 */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	UQuest* p2;					/**< Quest poniter to parent quest 2 */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	UQuest* c1;					/**< Quest poniter to child quest 1 */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoPair")
	UQuest* c2;					/**< Quest poniter to child quest 2 */
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

	//! A function initialises the evolution manager.
	/*!
		\param p a character pointer which allows access to the play style manager.
		\param mgr a pointer to the quest manager.
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Init(AInitial_IntegrationCharacter* p, UQuestManager* mgr);

	//! A function which begins the evolutionary process.
	/*!
	* 
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void EvolveQuests();

	//! A function which evaluates a quests fitness values.
	/*!
		\param qst a Quest pointer for a quest object.
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Evaluate(UQuest* qst);

	//! A function which selects parents using the roulette wheele selection method.
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

	//! A function which calculates the frequecy of each quest element type before survivor selection.
	/*!
	*/
	void CalculateFrequencySel(Ffrequency_Count* count);

	//! A function which calculates the frequecy of each quest element type after the evolutionary process has finished.
	/*!
	*/
	void CalculateFrequencyFin(Ffrequency_Count* count);

	//! A function mutates a set amount of quests when some genetic material is lost (not selected for the next generation).
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Mutate();

	//! A function which selects soultions created in Combine() to be added to the population.
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void Survive();

	//! A function which updates the frequency change values and displayes them depening on debug option
	/*!
	*/
	void DisplayChangeSel();

	//! A function which updates the frequency change values and displayes them depening on debug option
	/*!
	*/
	void DisplayChangeFin();

	//! A function outputs evolutionary data to a .csv file.
	/*!
	*/
	UFUNCTION(BlueprintCallable, Category = "EvoManagment")
	void OutputResult();




///////////////////////////////////////////////////		Variables		//////////////////////////////////////////////////////////////////////////////



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	TArray<UQuest*> m_aChildren;						/*!< A vector of type Quest* which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	TArray<FPair> m_aParents;							/*!< A vector of type quest which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	AInitial_IntegrationCharacter* m_pPlayer;			/*!< A pointer of type Player* which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	UQuestManager* m_pQuestMgr;							/*!< A pointer of QuestManager* which holds all quest information. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int m_iMaxPairs;									/*!< An integer which declares the maximum amount of mating pairs that can be selected for breeding. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int m_iMaxChildren;									/*!< An integer which declares the maximum amount of children that can be created per evolution. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int m_iMaxPopulation;								/*!< An integer which declares the maximum size of the population. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int m_iReintroRate;									/*!< An integer used to trigger mutation of quest elements. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	int m_iEvolutionNumber; 							/*!< An integer which declares the total number of evolutions that have taken place so far. */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	TArray<FGenerationData> m_aEvoGenerationData;		/*!< A vector of type quest which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	Ffrequency_Count m_CurrentFreqInfoSel;				/*!< A structure that holds the current populations frequency information prior to selection. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	Ffrequency_Count m_PreviousFreqInfoSel;				/*!< A structure that holds the previous populations frequency information prior to selection. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	Ffrequency_Count m_CurrentFreqInfoFin;				/*!< A structure that holds the current populations frequency information at the end of an evolution. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EvoManagment")
	Ffrequency_Count m_PreviousFreqInfoFin;				/*!< A structure that holds the previous populations frequency information at the end of an evolution. */
};
