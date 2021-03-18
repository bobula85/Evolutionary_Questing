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
	// Sets default values for this actor's properties
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	void Init();

protected:
	// Called when the game starts or when spawned
	//UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//! A function which updates the players play style.
/*!
	\param
*/
	UFUNCTION(BlueprintCallable, Category = "PlayStyle")
	void CalculateFitness();

	////////////////////////////	KILL STATS	////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Kill_Com;		/*!< An integer value representing amount of kill quests completed */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Kill_InCom;		/*!< An integer value representing amount of kill quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Kill_Abn;		/*!< An integer value representing amount of kill quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Kill_Rej;		/*!< An integer value representing amount of kill quests rejected */

	////////////////////////////	GATHER STATS	////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Gather_Com;		/*!< An integer value representing amount of gather quests completed */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Gather_InCom;	/*!< An integer value representing amount of gather quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Gather_Abn;		/*!< An integer value representing amount of gather quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Gather_Rej;		/*!< An integer value representing amount of gather quests rejected */

	////////////////////////////	FETCH STATS	////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Fetch_Com;		/*!< An integer value representing amount of fetch quests completed */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Fetch_Abn;		/*!< An integer value representing amount of fetch quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Fetch_InCom;	/*!< An integer value representing amount of fetch quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Fetch_Rej;		/*!< An integer value representing amount of fetch quests rejected */

	////////////////////////////	EXPLORE STATS	////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Explore_Com;		/*!< An integer value representing amount of fetch quests completed */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Explore_InCom;	/*!< An integer value representing amount of fetch quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Explore_Abn;		/*!< An integer value representing amount of fetch quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Explore_Rej;		/*!< An integer value representing amount of explore quests rejected */

	////////////////////////////	CLOSE STATS		////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Close_Com;		/*!< An integer value representing amount of close quests complete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Close_InCom;	/*!< An integer value representing amount of close quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Close_Abn;		/*!< An integer value representing amount of close quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Close_Rej;		/*!< An integer value representing amount of close quests rejected */

	////////////////////////////	MID STATS		////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Mid_Com;		/*!< An integer value representing amount of mid quests complete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Mid_InCom;		/*!< An integer value representing amount of mid quests incomplete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Mid_Abn;		/*!< An integer value representing amount of mid quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Mid_Rej;		/*!< An integer value representing amount of mid quests rejected */

	////////////////////////////	FAR STATS		////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Far_Com;		/*!< An integer value representing amount of far quests complete */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Far_InCom;		/*!< An integer value representing amount of far quests incomplete */
	   	  
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Far_Abn;		/*!< An integer value representing amount of far quests abandoned */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Far_Rej;		/*!< An integer value representing amount of far quests rejected */

	////////////////////////////	FITNESS VALUES		////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Kill_Fitness;		/*!< An integer value representing the final kill fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Gather_Fitness;		/*!< An integer value representing the final gather fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Fetch_Fitness;		/*!< An integer value representing the final fetch fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Explore_Fitness;		/*!< An integer value representing the final fetch fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Close_Fitness;		/*!< An integer value representing the final close fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Mid_Fitness;		/*!< An integer value representing the final mid fitness */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayStyle")
	int Far_Fitness;		/*!< An integer value representing the final far fitness */

	double compMultiplier; 
	double inCompMultiplier;
	double abnMultiplier;
	double rejMultiplier;

};
