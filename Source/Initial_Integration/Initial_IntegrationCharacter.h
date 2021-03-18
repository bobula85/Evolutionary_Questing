// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Initial_IntegrationCharacter.generated.h"

class UQuest;
class UPlayStyleManager;

UCLASS(config=Game)
class AInitial_IntegrationCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AInitial_IntegrationCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//! A function which adds a quest to the players list of accepted quests.
	/*!
		\param addQuest of type quest.
		\return True if quest is added.
	*/
	UFUNCTION(BlueprintCallable, Category = "PlayerQuestManagement")
	bool AddQuest(UQuest* addQuest);

	//! A function which complets a quest from the players list of accepted quests.
	/*!
		 \param completeQuest of type quest.
		 \return True if quest is completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "PlayerQuestManagement")
	bool CompleteQuest(UQuest* completeQuest);

	//! A function which abandons a quest from the players list of accepted quests.
	/*!
		\param abandonQuest of type quest.
		\return True if quest is abandoned.
	*/
	UFUNCTION(BlueprintCallable, Category = "PlayerQuestManagement")
	bool AbandonQuest(UQuest* abandonQuest);

	//! A function which checks if the quest has already been accepted.
	/*!
		\param compQuest of type quest.
		\return True if quest already accepted.
	*/
	UFUNCTION(BlueprintCallable, Category = "PlayerQuestManagement")
	bool AlreadyAccepted(UQuest* compQuest);

	//APlayStyleManager* GetStyle() { return style; };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerQuestManagement")
	TArray<UQuest*> quests;	 /*!< A vector of type quest which holds the players accepted quests. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStyleManagement")
	UPlayStyleManager* style;	/*!< A pointer to a playstyle manager class.*/

	UQuest* activeQuest;		/*!< A pointer to the currently active quest.*/

protected:

	// Check at each tick for an interacable item
	//UFUNCTION(BlueprintCallable, Category = "PlayerManagement")
	//void CheckForInteracables();

	//UFUNCTION(BlueprintCallable, Category = "PlayerManagement")
	//void OnInteract();

	//UFUNCTION(BlueprintCallable, Category = "PlayerManagement")
	//void OnQuestList();

	//UFUNCTION(BlueprintCallable, Category = "PlayerManagement")
	//void OnHistoryGUI();

	//UFUNCTION(BlueprintCallable, Category = "PlayerManagement")
	//void OnEvolutionGUI();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void Tick(float DeltaTime) override;

};



