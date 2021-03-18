// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "QuestBoard.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INITIAL_INTEGRATION_API AQuestBoard : public AInteractable
{
	GENERATED_BODY()

public:

	AQuestBoard();

protected:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* boardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName boardID;
};
