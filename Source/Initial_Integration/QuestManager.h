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

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INITIAL_INTEGRATION_API UQuest : public UActorComponent
{

	GENERATED_BODY()

public:

	//UQuest();

	//! Quest Constructor.
	/*!
		Cretes a quest and initialises its storage.
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void Init(TEnumAsByte<QuestDistance> d, TEnumAsByte<QuestType> typ, FString qName, UQuestManager* p);

	//! Quest Destructor.
	/*!
		Destroys quest and removes all data.
	*/
	//~UQuest();
	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool Compare(UQuest *comQuest);

	//! A function which initialises a text value of the quest type.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setTypeName();

	//! A function which initialises a text value of the quest type.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setType(QuestType Typ);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setLocation(FVector loc);

	//! A function which initialises a text value of the quest distance banding.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setDistName();

	//! A function which initialises a text value of the quest distance banding.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setQuestName();

	//! A function which initialises a text value of the quest distance banding.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setDescription();

	//! A function which sets the quest status - AVAILABLE, ACCEPTED, COMPLETE, ABANDONED.
	/*!
		\param state of type UINT8.
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void setState(TEnumAsByte<QuestStatus> state);

	//! A function which sets the distance of the quest from the player and update banding.
	/*!
		\param p of type Player.
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetDistanceFromPlayer(FVector playerPos);
	
	//! A function which Checks the distance away from the player of a point
	/*!
		\param p of type Player.
	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	int CheckDist(FVector playerPos, FVector newQuestPos);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int x;						/**< Integer value x representing the quests x position. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int y;						/**< Integer value y representing the quests y position. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int z;						/**< Integer value z representing the quests y position. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FVector questLocation; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<QuestType> type;					/**< UINT8 value used for bit representation of quest type. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<QuestStatus> status;					/**< Integer value status indicates the status of the quest (enum)*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	float distance;				/**< Integer value distance indicates the actual distance of the quest from the player*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<QuestDistance> distBand;				/**< Integer value status indicates the distance banding of the quest (enum)*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int totalFitness;			/**< integer value representing the quests total fitness*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int typeElementFitness;		/**< integer value representing the fitness of the type element*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	int distElementFitness;		/**< integer value representing the fitness of the distance element*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FString questName;			/**< string value used to store the text of a quest name for diplay in the list box. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FString typeName;			/**< string value used to store the text of a quest type for diplay in the list box. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FString distName;			/**< string value used to store the text of a quest distance banding for diplay in the list box. */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	FString description;		/**< string value used to store the text of a quest distance banding for diplay in the list box. */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	bool eventCreated;		/**< integer value representing the fitness of the distance element*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	bool inCompleteAdded;		/**< integer value representing the fitness of the distance element*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	bool chosen;		/**< integer value representing the fitness of the distance element*/

	UQuestManager* parent; 
};


struct less_than_fitness
{
	//! An inline function which sorts two quests by fitness.
	/*!

		\param q1 of type Quest*.
		\param q2 of type Quest*.
	*/
	inline bool operator() (UQuest* q1, UQuest* q2)
	{
		return (q1->totalFitness < q2->totalFitness);
	}
};



UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INITIAL_INTEGRATION_API UQuestManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	//UQuestManager();

	//! A function which initialises the begining quest list.
/*!
	\param abandonQuest of type quest.
	\return True if quest is abandoned.
*/
	UFUNCTION(BlueprintCallable, Category = "QuestManagement")
	void Init();

	FVector2D RandQuestPos(int distBounds);

	//! A function which initialises a text value of the quest type.
	/*!

	*/
	UFUNCTION(BlueprintCallable, Category = "Quest")
	FString getTypeName(int Typ);

	//! A function which tests the distance calculation.
	/*!

	*/
	//void AQuestManager::TestDistanceCalc();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestManagement")
	TArray<UQuest*> vpPopulation;	 /*!< A vector of type quest which holds all currently existing quests. */

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
