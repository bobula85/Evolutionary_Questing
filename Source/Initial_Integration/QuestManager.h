// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"

#include "Components/ActorComponent.h"
#include "QuestManager.generated.h"

class AInitial_IntegrationCharacter;

// Enum for quest availablity status setting
UENUM(BlueprintType)
enum QuestStatus
{
	ST_AVAILABLE = 0,
	ST_ACCEPTED,
	ST_COMPLETED,
	ST_ABANDONED,
	ST_REJECTED
};

// Enum for quest distance band setting
UENUM(BlueprintType)
enum QuestDistance
{
	DIST_CLOSE = 0,
	DIST_MID,
	DIST_FAR
};

//Enum for quest type setting
UENUM(BlueprintType)
enum QuestType
{
	TP_KILL = 0,
	TP_GATHER,
	TP_FETCH,
	TP_EXPLORE
};

UENUM(BlueprintType)
enum QuestElements
{
	ELEMENT_NULL = 0,
	ELEMENT_KILL,
	ELEMENT_GATHER,
	ELEMENT_FETCH,
	ELEMENT_EXPLORE,
	ELEMENT_CLOSE,
	ELEMENT_MID,
	ELEMENT_FAR
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INITIAL_INTEGRATION_API UQuest : public UActorComponent
{

	GENERATED_BODY()

public:

	//! Initialises the quests storage.
	/*!
		\param d		- enum used to set quest distance
		\param typ		- enum used to set quest type
		\param qName	- string used to set quests name
		\param p		- pointer the the quest manager object
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void Init(TEnumAsByte<QuestDistance> d, TEnumAsByte<QuestType> typ, FString qName, UQuestManager* p);

	//! Destroys quest and removes all data.
	/*!
		\param comQuest - pointer to quest to be compared to.
		\return True if quest data is equal.
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool Compare(UQuest *comQuest);

	//! Overloads equal to operator using compare function.
	/*!
		\param comQuest - pointer to quest to be compared to
		\return True if quest data is equal.
	*/
	bool operator==(UQuest* comQuest)
	{
		return Compare(comQuest);
	}

	//! A function which initialises a text value of the quest type.
	/*!
		
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setTypeName();

	//! A function which initialises a text value of the quest type.
	/*!
		\param Typ - enum used for setting the quests type
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setType(QuestType Typ);

	//! A function sets the location of the quest.
	/*!
		\param loc used for setting each element of the plcation
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setLocation(FVector loc);

	//! A function which initialises a text value of the quest distance banding (close, mid, far).
	/*!
		 
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setDistName();

	//!  A function which initialises a text value of the quest complete name (type + distance).
	/*!
		
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setQuestName();

	//! A function which sets the description text for the quest ( eg "got to the castle and slay the dragon")
	/*!
		
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setDescription();

	//! A function which sets the quest status - AVAILABLE, ACCEPTED, COMPLETE, ABANDONED.
	/*!
		\param state of type enum used to set the state of the quest.
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setState(TEnumAsByte<QuestStatus> state);

	//! A function which sets the distance of the quest from the player and update banding, name and description.
	/*!
		\param playerPos - position used for distance calculation.
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetDistanceFromPlayer(FVector playerPos);
	



///////////////////////////////////////////////////		Variables		//////////////////////////////////////////////////////////////////////////////




	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int m_iXPos;								/**< Integer value x representing the quests x position. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int m_iYPos;								/**< Integer value y representing the quests y position. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int m_iZPos;								/**< Integer value z representing the quests y position. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FVector m_vQuestLocation;					/**< Vector of quests location. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<QuestType> m_eType;				/**< Enum value used for representation of quest type. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<QuestStatus> m_eStatus;			/**< Enum value used for representation of quest status (completed, available, accepted)*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	float m_fDistance;							/**< Float value indicates the actual distance of the quest from the player*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<QuestDistance> m_eDistBand;		/**< Enum value used for representation of distance banding (close, mid, far).*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	float m_iTotalFitness;						/**< Integer value representing the quests total fitness*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	float m_iTypeElementFitness;					/**< Integer value representing the fitness of the type element*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	float m_iDistElementFitness;					/**< Integer value representing the fitness of the distance element*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FString m_sQuestName;						/**< String value used to store the text of a quest name for diplay in the text box. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FString m_sTypeName;						/**< String value used to store the text of a quest type for diplay in the text box. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FString m_sDistName;						/**< String value used to store the text of a quest distance name for diplay in the text box. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FString m_sDescription;						/**< String value used to store the text of a quest description for diplay in the text box. */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	bool m_bEventCreated;						/**< Bool value representing creation event*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	bool m_bInCompleteAdded;					/**< Bool value representing the addition of an incomplete quest*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	bool m_bChosen;								/**< integer value representing the fitness of the distance element*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<QuestElements> m_eTypeElement;	/**< enum value representing the type element*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<QuestElements> m_eDistElement;	/**< enum value representing the dist element*/

	UQuestManager* m_pParent;					/**< Pointer to the quest manager*/
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INITIAL_INTEGRATION_API UQuestManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	//! A function which initialises the quest manager.
	/*!
		
	*/
	UFUNCTION(BlueprintCallable, Category = "QuestManagement")
	void Init();

	//! A function generates a random position within distance bounds.
	/*!
		\param distBounds - integer value used for setting max and min bounds (distance banding).
		\return 2d vector used for x and y position
	*/
	FVector2D RandQuestPos(int distBounds);

	//! A function which initialises a text value of the quest type.
	/*!
		\param Typ - integer value used for switching type.
		\return string of type name
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	FString getTypeName(int Typ);



///////////////////////////////////////////////////		Variables		//////////////////////////////////////////////////////////////////////////////



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestManagement")
	TArray<UQuest*> vpPopulation;				/**< A vector of type quest pointer which holds all currently existing quests. */
};
