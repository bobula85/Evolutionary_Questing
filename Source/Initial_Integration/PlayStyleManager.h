// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayStyleManager.generated.h"


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
	int m_iKill_Fitness;		/*!< An integer value representing the final kill fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iGather_Fitness;		/*!< An integer value representing the final gather fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFetch_Fitness;		/*!< An integer value representing the final fetch fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iExplore_Fitness;		/*!< An integer value representing the final fetch fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iClose_Fitness;		/*!< An integer value representing the final close fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iMid_Fitness;			/*!< An integer value representing the final mid fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int m_iFar_Fitness;			/*!< An integer value representing the final far fitness */

	// could be exposed to the unreal editor for easy modification

	double m_dCompMultiplier;		/*!< A multiplier of type double used in the completed quests part of the fitness calculation */
	double m_dInCompMultiplier;		/*!< A multiplier of type double used in the incomplete quests part of the fitness calculation */
	double m_dAbnMultiplier;		/*!< A multiplier of type double used in the abandoned quests part of the fitness calculation */
	double m_dRejMultiplier;		/*!< A multiplier of type double used in the rejected quests part of the fitness calculation */

};
