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


/*
void AQuestManager::TestDistanceCalc()
{
	Player* p1 = new Player(1, 1);
	Player* p2 = new Player(10, 10);
	Player* p3 = new Player(6, 4);
	Player* p4 = new Player(-1, -1);
	Player* p5 = new Player(15, 15);


	Quest* q1 = new Quest(0, 0, TP_KILL);
	Quest* q2 = new Quest(6, 2, TP_KILL);
	Quest* q3 = new Quest(4, 8, TP_KILL);
	Quest* q4 = new Quest(-1, -1, TP_KILL);
	Quest* q5 = new Quest(20, 10, TP_KILL);

	TArray<int> results;

	q1->SetDistanceFromPlayer(p1);
	q2->SetDistanceFromPlayer(p2);
	q3->SetDistanceFromPlayer(p3);
	q4->SetDistanceFromPlayer(p4);
	q5->SetDistanceFromPlayer(p5);

	results.push_back(q1->distance);
	results.push_back(q2->distance);
	results.push_back(q3->distance);
	results.push_back(q4->distance);
	results.push_back(q5->distance);

}
*/
///////////////////////////////		Quest	//////////////////////////////

void UQuest::Init(TEnumAsByte<QuestDistance> d, TEnumAsByte<QuestType> typ, FString qName, UQuestManager* p)
{
	parent = p; 

	FVector2D rand = parent->RandQuestPos(d);
	// Set quest x position
	x = rand.X;
	// Set quest y position
	y = rand.Y;

	// Set quest y position
	z = 130;

	questLocation = FVector(x, y, z);

	eventCreated = false;

	// Set quest type position
	type = typ;
	// Initialise state to available
	status = ST_AVAILABLE;

	questName = qName;

	// Initialise the quest type name
	setTypeName();
	setDescription();
	
	inCompleteAdded = false; 
}

bool UQuest::Compare(UQuest* comQuest)
{
	// Compare two quests, return true if the same, false if different
	if (comQuest->x == x && comQuest->y == y && comQuest->z == z && comQuest->type == type)
		return true;
	else
		return false;
}

void UQuest::setTypeName()
{
	// Set quest name vaue based on type
	switch (type)
	{
	case TP_KILL:
		typeName = L"Kill Quest";
		break;
	case TP_GATHER:
		typeName = L"Gather Quest";
		break;
	case TP_FETCH:
		typeName = L"Fetch Quest";
		break;
	case TP_EXPLORE:
		typeName = L"Explore Quest";
		break;
	}
}

void UQuest::setType(QuestType Typ)
{
	type = Typ;

	setTypeName();
}

void UQuest::setLocation(FVector loc)
{
	questLocation = loc;

	x = questLocation.X;
	y = questLocation.Y;
	z = 130;

}

void UQuest::setDistName()
{
	// Set distance banding name text by band
	switch (distBand)
	{
	case DIST_CLOSE:
		distName = L" (Close)";
		break;
	case DIST_MID:
		distName = L" (Mid)";
		break;
	case DIST_FAR:
		distName = L" (Far)";
		break;
	}
}

void UQuest::setDescription()
{
	int randOpener = FMath::RandRange(0, 3);

	switch (randOpener)
	{
	case 0:
		description = TEXT("I have a mighty quest for a mighty worrier! Your travels will take you ");
		break;
	case 1:
		description = TEXT("Hello Adventurer! Might you aid me in a task? It's ");
		break;
	case 2:
		description = TEXT("Hey you? Do me a favor will you? It's ");
		break;
	case 3:
		description = TEXT("If only there were someone who could help me.... Ah you there? I have a job for you! It's ");
		break;
	}

	// Set distance banding name text by band
	switch (distBand)
	{
	case DIST_CLOSE:
		description += TEXT("only a short distance so pack light. ");
		break;
	case DIST_MID:
		description += TEXT("not too far. ");
		break;
	case DIST_FAR:
		description += TEXT("a great distance so be prepeared. ");
		break;
	}

	// Set quest name vaue based on type
	switch (type)
	{
	case TP_KILL:
		description += TEXT("When you arrive at your destination dispatch the swine that you find there! He served me cold tea this one time... there's no excuse for it!");
		break;
	case TP_GATHER:
		description += TEXT("Christmas is fast approaching and i need some good twigs for my reef! could you gather me some?");
		break;
	case TP_FETCH:
		description += TEXT("Whilst out sinking some bevies with my bestie last night i misplaced my hoard or treasure... could you find it?");
		break;
	case TP_EXPLORE:
		description += TEXT("I have been studying the contents of the rubbish looking stone houses that keep randomly appearing but recently one collapsed on my leg! Could you go explore that one for me?");
		break;
	}
}

void UQuest::setQuestName()
{
	setDistName();

	FString newName;

	newName += typeName;
	newName += distName;
	questName = newName;
}

void UQuest::setState(TEnumAsByte<QuestStatus> state)
{
	// Set quest state
	status = state;
}

int UQuest::CheckDist(FVector playerPos, FVector newQuestPos /*int cx, int cy, int cz, int x, int y, int z */)
{
	int x1 = pow((newQuestPos.X - playerPos.X), 2);
	int y1 = pow((newQuestPos.Y - playerPos.Y), 2);
	int z1 = pow((newQuestPos.Z - playerPos.Z), 2);

	//int val = (x1 + y1 + z1);

	// distance between the centre  
	// and given point 
	return (x1 + y1 + z1);
}

void UQuest::SetDistanceFromPlayer(FVector playerPos)
{
	FVector questPos(x, y, z);

	distance = playerPos.Dist(playerPos, questPos); // Abs(Abs(p->pos_x - 1) - Abs(x - 1)) + (Abs(p->pos_y - 1) - Abs(y - 1));

	//FString temp = FString::SanitizeFloat(distance);
	
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, playerPos.ToString());

	// Set the distance banding based on distance from player
	if (distance > 0 && distance <= 1000)
	{
		distBand = DIST_CLOSE;
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, L" close ");
	}
	else if (distance > 1000 && distance <= 2000)
	{
		distBand = DIST_MID;
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, L" mid ");
	}
	else if (distance > 2000)
	{
		distBand = DIST_FAR;
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, L" far ");
	}
	
	setQuestName();
	setDescription();
}