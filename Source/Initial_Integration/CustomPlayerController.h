// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

//class AInteractable;

/**
 * 
 */
UCLASS(Blueprintable)
class INITIAL_INTEGRATION_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:


	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	//AInteractable* currentInteractable;

	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	//AInteractable* GetCurrentInteractable() { return currentInteractable; };

};
