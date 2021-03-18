// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class INITIAL_INTEGRATION_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Player interact fucntion created as blueprint. controller passed for access to interacable object.
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(APlayerController* controller);

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Action;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FString GetUseText() const { return FString::Printf(TEXT("%s : Press E to %s "), *Name, *Action); }
};
