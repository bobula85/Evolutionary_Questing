// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuestManager.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayStyleManager.generated.h"

UENUM(BlueprintType)
enum CompleteionStatElement
{
	STAT_KILL_COMPLETE = 0,
	STAT_KILL_INCOMPLETE,
	STAT_KILL_ABANDONED,
	STAT_KILL_REJECTED,

	STAT_GATHER_COMPLETE,
	STAT_GATHER_INCOMPLETE,
	STAT_GATHER_ABANDONED,
	STAT_GATHER_REJECTED,

	STAT_FETCH_COMPLETE,
	STAT_FETCH_INCOMPLETE,
	STAT_FETCH_ABANDONED,
	STAT_FETCH_REJECTED,

	STAT_EXPLORE_COMPLETE,
	STAT_EXPLORE_INCOMPLETE,
	STAT_EXPLORE_ABANDONED,
	STAT_EXPLORE_REJECTED,

	STAT_CLOSE_COMPLETE,
	STAT_CLOSE_INCOMPLETE,
	STAT_CLOSE_ABANDONED,
	STAT_CLOSE_REJECTED,

	STAT_MID_COMPLETE,
	STAT_MID_INCOMPLETE,
	STAT_MID_ABANDONED,
	STAT_MID_REJECTED,

	STAT_FAR_COMPLETE,
	STAT_FAR_INCOMPLETE,
	STAT_FAR_ABANDONED,
	STAT_FAR_REJECTED
};

struct CompletionStatPointerStruct
{
	CompleteionStatElement element;
	int* completeionStat;
};

struct FittnessPointerStruct
{
	QuestElements element;
	float* fitnessValue;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INITIAL_INTEGRATION_API UPlayStyleManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	//! A function which initialises the play style manager.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	void Init();

	//! A function which updates the players play style.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	void CalculateFitness();

	//! A function that increments a stat value based on stat element.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	bool IncrementStatValue(CompleteionStatElement element);

	//! A function that decrements a stat value based on stat element.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	bool DecrementStatValue(CompleteionStatElement element);

	//! An accessor function which returns the value of a stat based on stat element.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	int GetStatValue(CompleteionStatElement element);

	//! An accessor function which returns a pointr to a fitness value based on quest element.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	float GetFitnessValue(int element);

	//! An accessor function which returns a pointr to a fitness value based on quest element.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	void SetFitnessValue(int element, float val);

	////////////////////////////	KILL STATS	////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iKill_Com;		/*!< An integer value representing amount of kill quests completed */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iKill_InCom;		/*!< An integer value representing amount of kill quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iKill_Abn;		/*!< An integer value representing amount of kill quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iKill_Rej;		/*!< An integer value representing amount of kill quests rejected */

	////////////////////////////	GATHER STATS	////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iGather_Com;		/*!< An integer value representing amount of gather quests completed */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iGather_InCom;	/*!< An integer value representing amount of gather quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iGather_Abn;		/*!< An integer value representing amount of gather quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iGather_Rej;		/*!< An integer value representing amount of gather quests rejected */

	////////////////////////////	FETCH STATS	////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFetch_Com;		/*!< An integer value representing amount of fetch quests completed */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFetch_Abn;		/*!< An integer value representing amount of fetch quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFetch_InCom;		/*!< An integer value representing amount of fetch quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFetch_Rej;		/*!< An integer value representing amount of fetch quests rejected */

	////////////////////////////	EXPLORE STATS	////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iExplore_Com;		/*!< An integer value representing amount of fetch quests completed */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iExplore_InCom;	/*!< An integer value representing amount of fetch quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iExplore_Abn;		/*!< An integer value representing amount of fetch quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iExplore_Rej;		/*!< An integer value representing amount of explore quests rejected */

	////////////////////////////	CLOSE STATS		////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iClose_Com;		/*!< An integer value representing amount of close quests complete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iClose_InCom;		/*!< An integer value representing amount of close quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iClose_Abn;		/*!< An integer value representing amount of close quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iClose_Rej;		/*!< An integer value representing amount of close quests rejected */

	////////////////////////////	MID STATS		////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iMid_Com;			/*!< An integer value representing amount of mid quests complete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iMid_InCom;		/*!< An integer value representing amount of mid quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iMid_Abn;			/*!< An integer value representing amount of mid quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iMid_Rej;			/*!< An integer value representing amount of mid quests rejected */

	////////////////////////////	FAR STATS		////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFar_Com;			/*!< An integer value representing amount of far quests complete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFar_InCom;		/*!< An integer value representing amount of far quests incomplete */
	   	  
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFar_Abn;			/*!< An integer value representing amount of far quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFar_Rej;			/*!< An integer value representing amount of far quests rejected */

	////////////////////////////	FITNESS VALUES		////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	float m_iKill_Fitness;		/*!< An integer value representing the final kill fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	float m_iGather_Fitness;		/*!< An integer value representing the final gather fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	float m_iFetch_Fitness;		/*!< An integer value representing the final fetch fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	float m_iExplore_Fitness;		/*!< An integer value representing the final fetch fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	float m_iClose_Fitness;		/*!< An integer value representing the final close fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	float m_iMid_Fitness;			/*!< An integer value representing the final mid fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	float m_iFar_Fitness;			/*!< An integer value representing the final far fitness */
	
	// could be exposed to the unreal editor for easy modification
	double m_dCompMultiplier;		/*!< A multiplier of type double used in the completed quests part of the fitness calculation */
	double m_dInCompMultiplier;		/*!< A multiplier of type double used in the incomplete quests part of the fitness calculation */
	double m_dAbnMultiplier;		/*!< A multiplier of type double used in the abandoned quests part of the fitness calculation */
	double m_dRejMultiplier;		/*!< A multiplier of type double used in the rejected quests part of the fitness calculation */

	TArray<FittnessPointerStruct> m_aFitnessPointers = { FittnessPointerStruct{ELEMENT_KILL,	&m_iKill_Fitness},
														 FittnessPointerStruct{ELEMENT_GATHER,	&m_iGather_Fitness},
														 FittnessPointerStruct{ELEMENT_FETCH,	&m_iFetch_Fitness},
														 FittnessPointerStruct{ELEMENT_EXPLORE,	&m_iExplore_Fitness},
														 FittnessPointerStruct{ELEMENT_CLOSE,	&m_iClose_Fitness},
														 FittnessPointerStruct{ELEMENT_MID,		&m_iMid_Fitness},
														 FittnessPointerStruct{ELEMENT_FAR,		&m_iFar_Fitness}	};

	TArray<CompletionStatPointerStruct> m_aStatPointers = {  CompletionStatPointerStruct{STAT_KILL_COMPLETE ,		&m_iKill_Com},
															 CompletionStatPointerStruct{STAT_KILL_INCOMPLETE,		&m_iKill_InCom},
															 CompletionStatPointerStruct{STAT_KILL_ABANDONED,		&m_iKill_Abn},
															 CompletionStatPointerStruct{STAT_KILL_REJECTED,		&m_iKill_Rej},
															 							
															 CompletionStatPointerStruct{STAT_GATHER_COMPLETE,		&m_iGather_Com},
															 CompletionStatPointerStruct{STAT_GATHER_INCOMPLETE,	&m_iGather_InCom},
															 CompletionStatPointerStruct{STAT_GATHER_ABANDONED,		&m_iGather_Abn},
															 CompletionStatPointerStruct{STAT_GATHER_REJECTED,		&m_iGather_Rej},
															 
															 CompletionStatPointerStruct{STAT_FETCH_COMPLETE,		&m_iFetch_Com},
															 CompletionStatPointerStruct{STAT_FETCH_INCOMPLETE,		&m_iFetch_InCom},
															 CompletionStatPointerStruct{STAT_FETCH_ABANDONED,		&m_iFetch_Abn},
															 CompletionStatPointerStruct{STAT_FETCH_REJECTED,		&m_iFetch_Rej},
															 
															 CompletionStatPointerStruct{STAT_EXPLORE_COMPLETE,		&m_iExplore_Com},
															 CompletionStatPointerStruct{STAT_EXPLORE_INCOMPLETE,	&m_iExplore_InCom},
															 CompletionStatPointerStruct{STAT_EXPLORE_ABANDONED,	&m_iExplore_Abn},
															 CompletionStatPointerStruct{STAT_EXPLORE_REJECTED,		&m_iExplore_Rej},
															 
															 CompletionStatPointerStruct{STAT_CLOSE_COMPLETE,		&m_iClose_Com},
															 CompletionStatPointerStruct{STAT_CLOSE_INCOMPLETE,		&m_iClose_InCom},
															 CompletionStatPointerStruct{STAT_CLOSE_ABANDONED,		&m_iClose_Abn},
															 CompletionStatPointerStruct{STAT_CLOSE_REJECTED,		&m_iClose_Rej},
															 
															 CompletionStatPointerStruct{STAT_MID_COMPLETE,			&m_iMid_Com},
															 CompletionStatPointerStruct{STAT_MID_INCOMPLETE,		&m_iMid_InCom},
															 CompletionStatPointerStruct{STAT_MID_ABANDONED,		&m_iMid_Abn},
															 CompletionStatPointerStruct{STAT_MID_REJECTED,			&m_iMid_Rej},
															 
															 CompletionStatPointerStruct{STAT_FAR_COMPLETE,			&m_iFar_Com},
															 CompletionStatPointerStruct{STAT_FAR_INCOMPLETE,		&m_iFar_InCom},
															 CompletionStatPointerStruct{STAT_FAR_ABANDONED,		&m_iFar_Abn},
															 CompletionStatPointerStruct{STAT_FAR_REJECTED,			&m_iFar_Rej} };

};