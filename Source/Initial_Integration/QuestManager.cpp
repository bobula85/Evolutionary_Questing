// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include "Engine.h"

#include "Initial_IntegrationCharacter.h"

#include "GenericPlatform/GenericPlatformMath.h"

void UQuestManager::Init()
{
	// Initialise far

	UQuest* far_kill		= NewObject<UQuest>();
	UQuest* far_gather		= NewObject<UQuest>();
	UQuest* far_fetch		= NewObject<UQuest>();
	UQuest* far_explore		= NewObject<UQuest>();

	far_kill->Init(DIST_FAR, TP_KILL, L"Kill Far", this);
	far_gather->Init(DIST_FAR, TP_GATHER, L"Gather Far", this);
	far_fetch->Init(DIST_FAR, TP_FETCH, L"Fetch Far", this);
	far_explore->Init(DIST_FAR, TP_EXPLORE, L"Explore Far", this);

	// Initialise mid

	UQuest* mid_kill	= NewObject<UQuest>();// new UQuest(1, 2, TP_KILL);
	UQuest* mid_gather	= NewObject<UQuest>();// new UQuest(7, 3, TP_GATHER);
	UQuest* mid_fetch	= NewObject<UQuest>();// new UQuest(7, 3, TP_GATHER);
	UQuest* mid_explore	= NewObject<UQuest>();// new UQuest(2, 5, TP_FETCH);

	mid_kill->Init(DIST_MID, TP_KILL, L"Kill Mid", this);
	mid_gather->Init(DIST_MID, TP_GATHER, L"Gater Mid", this);
	mid_fetch->Init(DIST_MID, TP_FETCH, L"Fetch Mid", this);
	mid_explore->Init(DIST_MID, TP_EXPLORE, L"Explore Mid", this);

	// Initialise close

	UQuest* close_kill		= NewObject<UQuest>();//new UQuest(3, 3, TP_KILL);
	UQuest* close_gather	= NewObject<UQuest>();//new UQuest(3, 5, TP_GATHER);
	UQuest* close_fetch		= NewObject<UQuest>();//new UQuest(5, 4, TP_FETCH);
	UQuest* close_explore	= NewObject<UQuest>();//new UQuest(5, 4, TP_FETCH);

	close_kill->Init(DIST_CLOSE, TP_KILL, L"Kill Close", this);
	close_gather->Init(DIST_CLOSE, TP_GATHER, L"Gather Close", this);
	close_fetch->Init(DIST_CLOSE, TP_FETCH, L"Fetch Close", this);
	close_explore->Init(DIST_CLOSE, TP_EXPLORE, L"Explore Close", this);

	vpPopulation.Add(far_kill);
	vpPopulation.Add(far_gather);
	vpPopulation.Add(far_fetch);
	vpPopulation.Add(far_explore);

	vpPopulation.Add(mid_kill);
	vpPopulation.Add(mid_gather);
	vpPopulation.Add(mid_fetch);
	vpPopulation.Add(mid_explore);

	vpPopulation.Add(close_kill);
	vpPopulation.Add(close_gather);
	vpPopulation.Add(close_fetch);
	vpPopulation.Add(close_explore);

	//if (GEngine)
	//{
	//	for(int i = 0; i < vpPopulation.Num(); i++)
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, vpPopulation[i]->questName);
	//}
}

FString UQuestManager::getTypeName(int typ)
{
	// Set quest name vaue based on type
	switch (typ)
	{
	case TP_KILL:
		return FString(TEXT("Kill "));
		break;
	case TP_GATHER:
		return FString(TEXT("Gater "));
		break;
	case TP_FETCH:
		return FString(TEXT("Fetch "));
		break;
	case TP_EXPLORE:
		return FString(TEXT("Explore "));
		break;
	}

	return FString(TEXT("none"));
}

FVector2D UQuestManager::RandQuestPos(int distBounds)
{
	int minRadius = 0;
	int maxRadius = 0;

	switch (distBounds)
	{
	case DIST_CLOSE:
	{
		minRadius = 0;
		maxRadius = 1000;

		break;
	}
	case DIST_MID:
	{
		minRadius = 1000;
		maxRadius = 2000;

		break;
	}
	case DIST_FAR:
	{
		minRadius = 2000;
		maxRadius = 4000;

		break;
	}
	}

	// Generate random angle
	int randAngle = FMath::RandRange(0, 360);
	// Generate random distance from point
	int randOffset = FMath::RandRange(minRadius, maxRadius);

	// Get x and y coordiates based on angle and offest dist
	int newX = randOffset * cos(randAngle); // FMath::RandRange(-2000, 2000);
	int newY = randOffset * sin(randAngle); // FMath::RandRange(-2000, 2000);

	return FVector2D(newX, newY);
}





////////////////////////////////////////////////////////////////////////////		Quest	/////////////////////////////////////////////////////////////

void UQuest::Init(TEnumAsByte<QuestDistance> d, TEnumAsByte<QuestType> typ, FString qName, UQuestManager* p)
{
	m_pParent = p; 

	FVector2D rand = m_pParent->RandQuestPos(d);
	// Set quest x position
	m_iXPos = rand.X;
	// Set quest y position
	m_iYPos = rand.Y;

	// Set quest y position
	m_iZPos = 130;

	m_vQuestLocation = FVector(m_iXPos, m_iYPos, m_iZPos);

	m_bEventCreated = false;

	// Set quest type position
	m_eType = typ;
	// Initialise state to available
	m_eStatus = ST_AVAILABLE;

	m_sQuestName = qName;

	// Initialise the quest type name
	setTypeName();
	setDescription();
	
	m_bInCompleteAdded = false; 
}

bool UQuest::Compare(UQuest* comQuest)
{
	// Compare two quests, return true if the same, false if different
	if (comQuest->m_iXPos == m_iXPos && comQuest->m_iYPos == m_iYPos && comQuest->m_iZPos == m_iZPos && comQuest->m_eType == m_eType)
		return true;
	else
		return false;
}

void UQuest::setTypeName()
{
	// Set quest name vaue based on type
	switch (m_eType)
	{
	case TP_KILL:
		m_sTypeName = L"Kill Quest";
		break;
	case TP_GATHER:
		m_sTypeName = L"Gather Quest";
		break;
	case TP_FETCH:
		m_sTypeName = L"Fetch Quest";
		break;
	case TP_EXPLORE:
		m_sTypeName = L"Explore Quest";
		break;
	}
}

void UQuest::setType(QuestType Typ)
{
	m_eType = Typ;

	setTypeName();
}

void UQuest::setLocation(FVector loc)
{
	m_vQuestLocation = loc;

	m_iXPos = m_vQuestLocation.X;
	m_iYPos = m_vQuestLocation.Y;
	m_iZPos = 130;

}

void UQuest::setDistName()
{
	// Set distance banding name text by band
	switch (m_eDistBand)
	{
	case DIST_CLOSE:
		m_sDistName = L" (Close)";
		break;
	case DIST_MID:
		m_sDistName = L" (Mid)";
		break;
	case DIST_FAR:
		m_sDistName = L" (Far)";
		break;
	}
}

void UQuest::setDescription()
{
	int randOpener = FMath::RandRange(0, 3);

	switch (randOpener)
	{
	case 0:
		m_sDescription = TEXT("I have a mighty quest for a mighty worrier! Your travels will take you ");
		break;
	case 1:
		m_sDescription = TEXT("Hello Adventurer! Might you aid me in a task? It's ");
		break;
	case 2:
		m_sDescription = TEXT("Hey you? Do me a favor will you? It's ");
		break;
	case 3:
		m_sDescription = TEXT("If only there were someone who could help me.... Ah you there? I have a job for you! It's ");
		break;
	}

	// Set distance banding name text by band
	switch (m_eDistBand)
	{
	case DIST_CLOSE:
		m_sDescription += TEXT("only a short distance so pack light. ");
		break;
	case DIST_MID:
		m_sDescription += TEXT("not too far. ");
		break;
	case DIST_FAR:
		m_sDescription += TEXT("a great distance so be prepeared. ");
		break;
	}

	// Set quest name vaue based on type
	switch (m_eType)
	{
	case TP_KILL:
		m_sDescription += TEXT("When you arrive at your destination dispatch the swine that you find there! He served me cold tea this one time... there's no excuse for it!");
		break;
	case TP_GATHER:
		m_sDescription += TEXT("Christmas is fast approaching and i need some good twigs for my reef! could you gather me some?");
		break;
	case TP_FETCH:
		m_sDescription += TEXT("Whilst out sinking some bevies with my bestie last night i misplaced my hoard or treasure... could you find it?");
		break;
	case TP_EXPLORE:
		m_sDescription += TEXT("I have been studying the contents of the rubbish looking stone houses that keep randomly appearing but recently one collapsed on my leg! Could you go explore that one for me?");
		break;
	}
}

void UQuest::setQuestName()
{
	setDistName();

	FString newName;

	newName += m_sTypeName;
	newName += m_sDistName;
	m_sQuestName = newName;
}

void UQuest::setState(TEnumAsByte<QuestStatus> state)
{
	// Set quest state
	m_eStatus = state;
}

void UQuest::SetDistanceFromPlayer(FVector playerPos)
{
	FVector questPos(m_iXPos, m_iYPos, m_iZPos);

	m_fDistance = playerPos.Dist(playerPos, questPos);

	//FString temp = FString::SanitizeFloat(distance);
	
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, playerPos.ToString());

	// Set the distance banding based on distance from player
	if (m_fDistance > 0 && m_fDistance <= 1000)
	{
		m_eDistBand = DIST_CLOSE;
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, L" close ");
	}
	else if (m_fDistance > 1000 && m_fDistance <= 2000)
	{
		m_eDistBand = DIST_MID;
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, L" mid ");
	}
	else if (m_fDistance > 2000)
	{
		m_eDistBand = DIST_FAR;
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, L" far ");
	}
	
	setQuestName();
	setDescription();
}