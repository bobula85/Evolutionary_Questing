// Fill out your copyright notice in the Description page of Project Settings.

#include "EvolutionManager.h"

#include "Misc/FileHelper.h"

#include "Engine.h"

#include "QuestManager.h"
#include "Initial_IntegrationCharacter.h"
#include "PlayStyleManager.h"

struct FSortByFitness
{
	FSortByFitness(const UQuest& quest)
		//: Quest(quest)
	{

	}

	/* The Location to use in our Sort comparision. */
	//UQuest Quest;

	bool operator()(const UQuest* A, const UQuest* B) const
	{
		int fitnessA = A->totalFitness;
		int fitnessB = B->totalFitness;

		return fitnessA > fitnessB;
	}
};

// Sets default values
void UEvolutionManager::Init(AInitial_IntegrationCharacter* p, UQuestManager* mgr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Initialise object pointers
	player = p;
	questMgr = mgr;

	// Initialise maximum amount of mating parents value
	maxPairs = 50;

	// Initialise maximum population size value
	maxPopulation = 25;

	// Initialise the number of evolutions 
	// that have taken place
	evolutionNumber = 1;

	ReintroRate = 10;

	PreviousFreqInfoSel = {};
	CurrentFreqInfoSel	 = {};

	PreviousFreqInfoFin = {};
	CurrentFreqInfoFin = {};
}

// Initiate the various stage of the evolutionary process
void UEvolutionManager::EvolveQuests()
{
	// Update previous population stats
	PreviousFreqInfoSel = {};
	PreviousFreqInfoFin = {};

	PreviousFreqInfoSel = CurrentFreqInfoSel;
	PreviousFreqInfoFin = CurrentFreqInfoFin;
	
	// Use the player statistics to calculate the optimum fitness values
	player->style->CalculateFitness();

	// Evaluate all current population solutions based on player statistics
	for (int i = 0; i < questMgr->vpPopulation.Num(); i++)
		Evaluate(questMgr->vpPopulation[i]);

	// Initiate the selection of the parent solutions
	// using roulette wheel selection
	//SelectRoulette();

	// Initiate the selection of the parent solutions
	// using roulette wheel selection
	SelectRanked();

	// Initiate the creation of the child solutions
	// using parents selected
	Combine();

	// Initiate the mutation function based on population stats of the child solutions
	Mutate();

	// Initiate the selection of the next generation of solutions
	Survive();

	// Recalculate population Stat data
	DisplayChangeSel();
	DisplayChangeFin();

	// Savle the created solutions information to
	// a .csv file
	//OutputResult();

	// Increment the number of evolutions that has taken place
	evolutionNumber++;
}

void UEvolutionManager::Evaluate(UQuest* qst)
{
	// based on the qst type value set the fitness type element of the soultion
	switch (qst->type)
	{
		// Kill quest type
	case TP_KILL:
	{
		// Set type fitness
		qst->typeElementFitness =
			player->style->Kill_Fitness;

		// based on the qst distance banding value set the fitness of distance element and the total fitness of the soultion
		switch (qst->distBand)
		{
			// Close Quests
		case DIST_CLOSE:
		{
			qst->distElementFitness =
				player->style->Close_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Kill_Fitness + player->style->Close_Fitness);

			break;
		}
		// Mid Quests
		case DIST_MID:
		{
			qst->distElementFitness =
				player->style->Mid_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Kill_Fitness + player->style->Mid_Fitness);
			break;
		}
		// Far away quests
		case DIST_FAR:
		{
			qst->distElementFitness =
				player->style->Far_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Kill_Fitness + player->style->Far_Fitness);
			break;
		}
		}

		break;
	}
	// Gather quest type
	case TP_GATHER:
	{
		// Set type fitness
		qst->typeElementFitness =
			player->style->Gather_Fitness;

		// based on the qst distance banding value set the fitness of distance element and the total fitness of the soultion
		switch (qst->distBand)
		{
			// Close Quests
		case DIST_CLOSE:
		{
			qst->distElementFitness =
				player->style->Close_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Gather_Fitness + player->style->Close_Fitness);
			break;
		}
		// Mid Quests
		case DIST_MID:
		{
			qst->distElementFitness =
				player->style->Mid_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Gather_Fitness + player->style->Mid_Fitness);
			break;
		}
		// Far away quests
		case DIST_FAR:
		{
			qst->distElementFitness =
				player->style->Far_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Gather_Fitness + player->style->Far_Fitness);
			break;
		}
		}

		break;
	}
	// Protect quest type
	case TP_EXPLORE:
	{
		// Set type fitness
		qst->typeElementFitness =
			player->style->Explore_Fitness;

		// based on the qst distance banding value set the fitness of distance element and the total fitness of the soultion
		switch (qst->distBand)
		{
			// Close Quests
		case DIST_CLOSE:
		{
			qst->distElementFitness =
				player->style->Close_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Explore_Fitness + player->style->Close_Fitness);
			break;
		}
		// Mid Quests
		case DIST_MID:
		{
			qst->distElementFitness =
				player->style->Mid_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Explore_Fitness + player->style->Mid_Fitness);
			break;
		}
		// Far away quests
		case DIST_FAR:
		{
			qst->distElementFitness =
				player->style->Far_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Explore_Fitness + player->style->Far_Fitness);
			break;
		}
		}

		break;
	}
	// Defend quest type
	case TP_FETCH:
	{
		// Set type fitness
		qst->typeElementFitness =
			player->style->Fetch_Fitness;

		// based on the qst distance banding value set the fitness of distance element and the total fitness of the soultion
		switch (qst->distBand)
		{
			// Close Quests
		case DIST_CLOSE:
		{
			qst->distElementFitness =
				player->style->Close_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Fetch_Fitness + player->style->Close_Fitness);
			break;
		}
		// Mid Quests
		case DIST_MID:
		{
			qst->distElementFitness =
				player->style->Mid_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Fetch_Fitness + player->style->Mid_Fitness);
			break;
		}
		// Far away quests
		case DIST_FAR:
		{
			qst->distElementFitness =
				player->style->Far_Fitness;

			qst->totalFitness = qst->totalFitness + (player->style->Fetch_Fitness + player->style->Far_Fitness);
			break;
		}
		}

		break;
	}
	}

	if (qst->totalFitness <= 0)
		qst->totalFitness = 1;
}

// Applies the roulette wheel selection method to select parent solutions
void UEvolutionManager::SelectRoulette()
{
	// Empty the parents vector
	parents.Empty();

	// Create a vecor to hold the sum of fitness values of selection
	TArray<int> tempVec;

	// Hold the sum of fitness total value
	int sumOfFitness = 0;

	// Loop through the population and increment the sum of fitness values accordingly
	for (int i = 0; i < questMgr->vpPopulation.Num(); i++)
	{
		if (i == 0)
			tempVec.Add(questMgr->vpPopulation[i]->totalFitness);
		else
			tempVec.Add(tempVec[i - 1] + questMgr->vpPopulation[i]->totalFitness);

		sumOfFitness += (questMgr->vpPopulation[i]->totalFitness);
	}

	// Seed the random number generator
	//srand(time(NULL));

	// Loop through the population and select maxPairs of parent solutions 
	for (int i = 0; i < maxPairs; i++)
	{
		// Generate random number between 1 and total fitness for both parents
		int r1 = FMath::RandRange(1, sumOfFitness);
		int r2 = FMath::RandRange(1, sumOfFitness);

		// Create pair struct to hold both parents as one object
		FPair parentPair;

		// If the random number generated falls within the probaility value of
		// a population solution then add it to the pair object as one of the parents.
		for (int j = 0; j < tempVec.Num(); j++)
		{
			if (tempVec[j] >= r1)
			{
				parentPair.p1 = questMgr->vpPopulation[j];
				break;
			}
		}

		for (int j = 0; j < tempVec.Num(); j++)
		{
			if (tempVec[j] >= r2)
			{
				parentPair.p2 = questMgr->vpPopulation[j];
				break;
			}
		}

		if (parentPair.p1 == parentPair.p2)
			i--;
		else
			// add the parent pair to the parent vector
			parents.Add(parentPair);
	}
}

// Not yet used. May be used in the next unit
void UEvolutionManager::SelectRanked()
{
	// Empty the parents vector
	parents.Empty();

	TArray<UQuest*> tempVecQuests;

	TArray<double> tempVec;

	for (int i = 0; i < questMgr->vpPopulation.Num(); i++)
		tempVecQuests.Add(questMgr->vpPopulation[i]);

	tempVecQuests.Sort([](const UQuest& a, const UQuest& b) { return a.totalFitness < b.totalFitness; });

	double sumOfRanks = ((double)tempVecQuests.Num() + 1) * ((double)tempVecQuests.Num() / 2);

	TArray<double> probs;

	for (int i = 0; i < tempVecQuests.Num(); i++)
	{
		double rank = i + 1;
		double pr = (rank / sumOfRanks);
		double prob = (rank / sumOfRanks) * 100;
		probs.Add(prob);
	}

	double sumOfRankedFitness = 0;

	// Loop through the population and increment the sum of fitness values accordingly
	for (int i = 0; i < probs.Num(); i++)
	{
		if (i == 0)
			tempVec.Add(probs[i]);
		else
			tempVec.Add(tempVec[i - 1] + probs[i]);

		sumOfRankedFitness += probs[i];
	}

	for (int i = 0; i < maxPairs; i++)
	{
		int r1 = FMath::RandRange(1, sumOfRankedFitness);
		int r2 = FMath::RandRange(1, sumOfRankedFitness);

		FPair parentPair;

		for (int j = 0; j < tempVec.Num(); j++)
		{
			if (tempVec[j] >= (double)r1)
			{
				parentPair.p1 = questMgr->vpPopulation[j];
				break;
			}
		}

		for (int j = 0; j < tempVec.Num(); j++)
		{
			if (tempVec[j] >= (double)r2)
			{
				parentPair.p2 = questMgr->vpPopulation[j];
				break;
			}
		}

		if (parentPair.p1 == parentPair.p2)
			i--;
		else
			// add the parent pair to the parent vector
			parents.Add(parentPair);
	}

}

void UEvolutionManager::Combine()
{
	children.Empty();

	for (int i = 0; i < parents.Num(); i++)
	{
		UQuest* child1 = NewObject<UQuest>();
		UQuest* child2 = NewObject<UQuest>();
		
		parents[i].c1 = child1;
		parents[i].c2 = child2;

		child1->Init(parents[i].p1->distBand, parents[i].p1->type, L"Quest? 1", questMgr);
		child2->Init(parents[i].p2->distBand, parents[i].p2->type, L"Quest? 2", questMgr);


		// Update child solutions distance information
		child1->SetDistanceFromPlayer(player->GetActorLocation());
		child2->SetDistanceFromPlayer(player->GetActorLocation());
		child1->setDistName();
		child2->setDistName();

		child1->setQuestName();
		child2->setQuestName();

		child1->setDescription();
		child2->setDescription();

		// Add children to the children vector
		children.Add(child1);
		children.Add(child2);
	}
}

void UEvolutionManager::CalculateFrequencySel(Ffrequency_Count* count)
{

	for (int i = 0; i < children.Num(); i++)
	{
		switch (children[i]->type)
		{
		case TP_KILL:
			count->KillCount++;
			break;
		case TP_GATHER:
			count->GatherCount++;
			break;
		case TP_FETCH:
			count->FetchCount++;
			break;
		case TP_EXPLORE:
			count->ExploreCount++;
			break;
		}

		switch (children[i]->distBand)
		{
		case DIST_CLOSE:
			count->CloseCount++;
			break;
		case DIST_MID:
			count->MidCount++;
			break;
		case DIST_FAR:
			count->FarCount++;
			break;
		}
	}

	count->KillFreq		= ((float)count->KillCount	/ (float)children.Num()) * 100;
	count->GatherFreq	= ((float)count->GatherCount/ (float)children.Num()) * 100;
	count->FetchFreq	= ((float)count->FetchCount	/ (float)children.Num()) * 100;
	count->ExploreFreq	= ((float)count->ExploreCount/ (float)children.Num()) * 100;

	count->TypeFreqs.Add(count->KillFreq);
	count->TypeFreqs.Add(count->GatherFreq);
	count->TypeFreqs.Add(count->FetchFreq);
	count->TypeFreqs.Add(count->ExploreFreq);

	if (count->KillFreq == 0.0 || count->GatherFreq == 0.0 || count->FetchFreq == 0.0 || count->ExploreFreq == 0.0)
	{
		if (count->KillFreq == 0.0)
			count->LowTypeFreqs.Add((int)TP_KILL);
		if (count->GatherFreq == 0.0)
			count->LowTypeFreqs.Add((int)TP_GATHER);
		if (count->FetchFreq == 0.0)
			count->LowTypeFreqs.Add((int)TP_FETCH);
		if (count->ExploreFreq == 0.0)
			count->LowTypeFreqs.Add((int)TP_EXPLORE);


		count->highestType = count->TypeFreqs.Max();
		count->lowTypeFreq = true;
	}

	count->CloseFreq	= ((float)count->CloseCount	/ (float)children.Num())*100;
	count->MidFreq		= ((float)count->MidCount	/ (float)children.Num())*100;
	count->FarFreq		= ((float)count->FarCount	/ (float)children.Num())*100;
	
	count->DistFreqs.Add(count->CloseFreq);
	count->DistFreqs.Add(count->MidFreq);
	count->DistFreqs.Add(count->FarFreq);

	if (count->CloseFreq == 0.0 || count->MidFreq == 0.0 || count->FarFreq == 0.0)
	{
		if (count->CloseFreq == 0.0)
			count->LowDistFreqs.Add((int)DIST_CLOSE);
		if (count->MidFreq == 0.0)
			count->LowDistFreqs.Add((int)DIST_MID);
		if (count->FarFreq == 0.0)
			count->LowDistFreqs.Add((int)DIST_FAR);

		count->highestDist = count->DistFreqs.Max();

		count->lowDistFreq = true;
	}
}

void UEvolutionManager::Mutate()
{
	//Ffrequency_Count tempCount;
	CurrentFreqInfoSel = {};

	// Get frequency information 
	CalculateFrequencySel(&CurrentFreqInfoSel);

	// if an element type is missing add it back in as below
	if (CurrentFreqInfoSel.lowTypeFreq || CurrentFreqInfoSel.lowDistFreq)
	{
		// misssing type element
		if (CurrentFreqInfoSel.lowTypeFreq)
		{
			// for each type element that is missing 
			for (int i = 0; i < CurrentFreqInfoSel.LowTypeFreqs.Num(); i++)
			{
				// add in 5 random ones
				for (int j = 0; j < ReintroRate; j++)
				{
					//geneerate a random index to change
					int randIndex = FMath::RandRange(0, (children.Num() - 1));

					// set it's type to the missing type
					children[randIndex]->setType((QuestType)CurrentFreqInfoSel.LowTypeFreqs[i]);

					children[randIndex]->setQuestName();
					children[randIndex]->setDescription();
				}
			}
		}
		// missing distance 
		if (CurrentFreqInfoSel.lowDistFreq)
		{	
			// for each distance banding that is missing
			for (int i = 0; i < CurrentFreqInfoSel.LowDistFreqs.Num(); i++)
			{
				int count = 0;
				
				int minRadius = 0;
				int maxRadius = 0; 

				//set the random number generater bounding based on missing dist type
				switch(CurrentFreqInfoSel.LowDistFreqs[i])
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

				while (count < ReintroRate)
				{
					// Generate random index 
					int randIndex = FMath::RandRange(0, (children.Num()-1));

					// Generate random angle
					int randAngle = FMath::RandRange(0, 360);
					// Generate random distance from point
					int randOffset = FMath::RandRange(minRadius, maxRadius);

					// Get x and y coordiates based on angle and offest dist
					int newX = randOffset * cos(randAngle); // FMath::RandRange(-2000, 2000);
					int newY = randOffset * sin(randAngle); // FMath::RandRange(-2000, 2000);

					// set x and y cords
					children[randIndex]->setLocation(FVector(newX, newY, 130));
					

					// Update quest location data
					children[randIndex]->SetDistanceFromPlayer(player->GetActorLocation());

					children[randIndex]->setDistName();
					children[randIndex]->setQuestName();
					children[randIndex]->setDescription();

					count++;
				}
			}
		}
	}

}

void UEvolutionManager::Survive()
{
	// Temperary vector used to hold what will be the next generation of solutions
	TArray<UQuest*> tempNewPop;

	// Evaluate the child solution so that all fittnesses are updated
	for (int i = 0; i < children.Num(); i++)
		Evaluate(children[i]);

	// Loop through the current population and include quests accepted but 
	// not completed in the next generation by default
	for (int i = 0; i < questMgr->vpPopulation.Num(); i++)
	{
		if (questMgr->vpPopulation[i]->status == ST_ACCEPTED)
			tempNewPop.Add(questMgr->vpPopulation[i]);
	}

	TArray<UQuest*> tempSortPop;

	TArray<double> tempVec;

	//for (int i = 0; i < questMgr->vpPopulation.Num(); i++)
	//	tempSortPop.Add(questMgr->vpPopulation[i]);

	for (int i = 0; i < children.Num(); i++)
		tempSortPop.Add(children[i]);

	tempSortPop.Sort([](const UQuest& a, const UQuest& b) { return a.totalFitness < b.totalFitness; });

	double sumOfRanks = ((double)tempSortPop.Num() + 1) * ((double)tempSortPop.Num() / 2);

	TArray<double> probs;

	for (int i = 0; i < tempSortPop.Num(); i++)
	{
		double rank = i + 1;
		double pr = (rank / sumOfRanks);
		double prob = (rank / sumOfRanks) * 100;
		probs.Add(prob);
	}

	double sumOfRankedFitness = 0;

	// Loop through the population and increment the sum of fitness values accordingly
	for (int i = 0; i < probs.Num(); i++)
	{
		if (i == 0)
			tempVec.Add(probs[i]);
		else
			tempVec.Add(tempVec[i - 1] + probs[i]);

		sumOfRankedFitness += probs[i];
	}

	// Loop though the remaining space in the next generation and select at random
	// the children that will be added based on their fitness proportionate probailities
	while(tempNewPop.Num() < maxPopulation)
	{
		int r1 = FMath::RandRange(1, sumOfRankedFitness);

		int tempNewPopSize = tempNewPop.Num();

		for (int j = 0; j < tempVec.Num(); j++)
		{
			if (tempVec[j] >= (double)r1)
			{
				int addedCheck = tempNewPop.Num();

				if (tempNewPop.AddUnique(tempSortPop[j]) == addedCheck)
					tempSortPop[j]->chosen = true;

				break;
			}
		}
	}

	// Empty the quest managers population list
	questMgr->vpPopulation.Empty();

	// Add the new generation to the quest manager
	for (int i = 0; i < tempNewPop.Num(); i++)
		questMgr->vpPopulation.Add(tempNewPop[i]);
}

void UEvolutionManager::CalculateFrequencyFin(Ffrequency_Count* count)
{

	for (int i = 0; i < questMgr->vpPopulation.Num(); i++)
	{
		switch (questMgr->vpPopulation[i]->type)
		{
		case TP_KILL:
			count->KillCount++;
			break;
		case TP_GATHER:
			count->GatherCount++;
			break;
		case TP_FETCH:
			count->FetchCount++;
			break;
		case TP_EXPLORE:
			count->ExploreCount++;
			break;
		}

		switch (questMgr->vpPopulation[i]->distBand)
		{
		case DIST_CLOSE:
			count->CloseCount++;
			break;
		case DIST_MID:
			count->MidCount++;
			break;
		case DIST_FAR:
			count->FarCount++;
			break;
		}
	}

	count->KillFreq = ((float)count->KillCount / (float)questMgr->vpPopulation.Num()) * 100;
	count->GatherFreq = ((float)count->GatherCount / (float)questMgr->vpPopulation.Num()) * 100;
	count->FetchFreq = ((float)count->FetchCount / (float)questMgr->vpPopulation.Num()) * 100;
	count->ExploreFreq = ((float)count->ExploreCount / (float)questMgr->vpPopulation.Num()) * 100;

	count->TypeFreqs.Add(count->KillFreq);
	count->TypeFreqs.Add(count->GatherFreq);
	count->TypeFreqs.Add(count->FetchFreq);
	count->TypeFreqs.Add(count->ExploreFreq);

	count->CloseFreq = ((float)count->CloseCount / (float)questMgr->vpPopulation.Num()) * 100;
	count->MidFreq = ((float)count->MidCount / (float)questMgr->vpPopulation.Num()) * 100;
	count->FarFreq = ((float)count->FarCount / (float)questMgr->vpPopulation.Num()) * 100;

	count->DistFreqs.Add(count->CloseFreq);
	count->DistFreqs.Add(count->MidFreq);
	count->DistFreqs.Add(count->FarFreq);
}

void UEvolutionManager::DisplayChangeSel()
{
	//% increase = (Increase ÷ Original Number) × 100.

	if (PreviousFreqInfoSel.TypeFreqs.Num() == 0)
		return;

	TArray<float> percentIncrease;

	for (int i = 0; i < CurrentFreqInfoSel.TypeFreqs.Num(); i++)
	{
		float increase = CurrentFreqInfoSel.TypeFreqs[i] - PreviousFreqInfoSel.TypeFreqs[i];

		float percentInc = (increase / CurrentFreqInfoSel.TypeFreqs[i]) * 100;

		//FString temp = FString::SanitizeFloat(percentInc);

		percentIncrease.Add(percentInc);
	}

	CurrentFreqInfoSel.KillChange		= percentIncrease[0];
	CurrentFreqInfoSel.GatherChange		= percentIncrease[1];
	CurrentFreqInfoSel.FetchChange		= percentIncrease[2];
	CurrentFreqInfoSel.ExploreChange	= percentIncrease[3];

	for (int i = 0; i < CurrentFreqInfoSel.DistFreqs.Num(); i++)
	{
		float increase = CurrentFreqInfoSel.DistFreqs[i] - PreviousFreqInfoSel.DistFreqs[i];

		float percentInc = (increase / CurrentFreqInfoSel.DistFreqs[i]) * 100;

		percentIncrease.Add(percentInc);
	}

	CurrentFreqInfoSel.CloseChange = percentIncrease[4];
	CurrentFreqInfoSel.MidChange = percentIncrease[5];
	CurrentFreqInfoSel.FarChange = percentIncrease[6];


	/*if (GEngine)
	{
		FString Gen = FString(TEXT("GENERATION NUMBER: "));
		Gen += FString::FromInt(evolutionNumber);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Green, Gen, false);

		for (int i = 0; i < percentIncrease.Num(); i++)
		{
			if (percentIncrease[i] > 0)
			{
				FString temp = questMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString::SanitizeFloat(percentIncrease[i]);
				temp += FString(TEXT("% Increased"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Green, temp, false);
			}
			if (percentIncrease[i] < 0)
			{
				FString temp = questMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString::SanitizeFloat(percentIncrease[i]);
				temp += FString(TEXT("% Decrease"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Red, temp, false);
			}
			if (percentIncrease[i] == 0)
			{
				FString temp = questMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString(TEXT("No Change"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Yellow, temp, false);
			}
		}
	}*/

}

void UEvolutionManager::DisplayChangeFin()
{
	//% increase = (Increase ÷ Original Number) × 100.

		//Ffrequency_Count tempCount;
	CurrentFreqInfoFin = {};

	// Get frequency information 
	CalculateFrequencyFin(&CurrentFreqInfoFin);

	if (PreviousFreqInfoFin.TypeFreqs.Num() == 0)
		return;

	TArray<float> percentIncreaseFin;

	for (int i = 0; i < CurrentFreqInfoFin.TypeFreqs.Num(); i++)
	{
		float increase = CurrentFreqInfoFin.TypeFreqs[i] - PreviousFreqInfoFin.TypeFreqs[i];

		float percentInc = (increase / CurrentFreqInfoFin.TypeFreqs[i]) * 100;

		//FString temp = FString::SanitizeFloat(percentInc);

		percentIncreaseFin.Add(percentInc);
	}

	CurrentFreqInfoFin.KillChange = percentIncreaseFin[0];
	CurrentFreqInfoFin.GatherChange = percentIncreaseFin[1];
	CurrentFreqInfoFin.FetchChange = percentIncreaseFin[2];
	CurrentFreqInfoFin.ExploreChange = percentIncreaseFin[3];

	for (int i = 0; i < CurrentFreqInfoFin.DistFreqs.Num(); i++)
	{
		float increase = CurrentFreqInfoFin.DistFreqs[i] - PreviousFreqInfoFin.DistFreqs[i];

		float percentInc = (increase / CurrentFreqInfoFin.DistFreqs[i]) * 100;

		percentIncreaseFin.Add(percentInc);
	}

	CurrentFreqInfoFin.CloseChange = percentIncreaseFin[4];
	CurrentFreqInfoFin.MidChange = percentIncreaseFin[5];
	CurrentFreqInfoFin.FarChange = percentIncreaseFin[6];


	/*if (GEngine)
	{
		FString Gen = FString(TEXT("GENERATION NUMBER: "));
		Gen += FString::FromInt(evolutionNumber);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Green, Gen, false);

		for (int i = 0; i < percentIncrease.Num(); i++)
		{
			if (percentIncrease[i] > 0)
			{
				FString temp = questMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString::SanitizeFloat(percentIncrease[i]);
				temp += FString(TEXT("% Increased"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Green, temp, false);
			}
			if (percentIncrease[i] < 0)
			{
				FString temp = questMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString::SanitizeFloat(percentIncrease[i]);
				temp += FString(TEXT("% Decrease"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Red, temp, false);
			}
			if (percentIncrease[i] == 0)
			{
				FString temp = questMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString(TEXT("No Change"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Yellow, temp, false);
			}
		}
	}*/

}

void UEvolutionManager::CalculateData(int gen, int stage, TArray<UQuest*> &questArray)
{
	int killTot		= 0;
	int gatherTot	= 0;
	int fetchTot	= 0;
	int exploreTot	= 0;
	int closeTot	= 0;
	int midTot		= 0;
	int farTot		= 0;

	for (int i = 0; i < questArray.Num(); i++)
	{
		switch (questArray[i]->type)
		{
		case TP_KILL:
			killTot++;
			break;
		case TP_GATHER:
			gatherTot++;
			break;
		case TP_FETCH:
			fetchTot++;
			break;
		case TP_EXPLORE:
			exploreTot++;
			break;
		}

		switch (questArray[i]->distBand)
		{
		case DIST_CLOSE:
			closeTot++;
			break;
		case DIST_MID:
			midTot++;
			break;
		case DIST_FAR:
			farTot++;
			break;
		}
	}

	FGenerationData tempData;

	tempData.Generation			= gen;
	tempData.Stage				= stage;

	tempData.PercentageKill		=	killTot	/ questArray.Num();
	tempData.PercentageGather	=	gatherTot / questArray.Num();
	tempData.PercentageFetch	=	fetchTot / questArray.Num();
	tempData.PercentageExplore	=	exploreTot / questArray.Num();
	tempData.PercentageClose	=	closeTot / questArray.Num();
	tempData.PercentageMid		=	midTot / questArray.Num();
	tempData.PercentageFar		=	farTot / questArray.Num();
		

}

void UEvolutionManager::OutputResult()
{
	/*FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir()) + TEXT("/MessageLog.csv");
	FString FileContent = TEXT("\n");
	FileContent += TEXT("GENERATION NUMBER,  ");
	FileContent += FString::FromInt(evolutionNumber);
	FileContent += TEXT(",\n");
	FileContent += TEXT("\n");

	FileContent += TEXT("SELECTION STAGE \n");
	FileContent += TEXT("\n");

	FileContent += TEXT("KILL,");
	FileContent += FString::FromInt(CurrentFreqInfoSel.KillFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Kill_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FETCH,");
	FileContent += FString::FromInt(CurrentFreqInfoSel.FetchFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Fetch_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("GATHER,");
	FileContent += FString::FromInt(CurrentFreqInfoSel.GatherFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Gather_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("EXPLORE,");
	FileContent += FString::FromInt(CurrentFreqInfoSel.ExploreFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Explore_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("CLOSE,");
	FileContent += FString::FromInt(CurrentFreqInfoSel.CloseFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Close_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("MID,");
	FileContent += FString::FromInt(CurrentFreqInfoSel.MidFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Mid_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FAR,");
	FileContent += FString::FromInt(CurrentFreqInfoSel.FarFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Far_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FINAL STAGE \n");
	FileContent += TEXT("\n");

	FileContent += TEXT("KILL,");
	FileContent += FString::FromInt(CurrentFreqInfoFin.KillFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Kill_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FETCH,");
	FileContent += FString::FromInt(CurrentFreqInfoFin.FetchFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Fetch_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("GATHER,");
	FileContent += FString::FromInt(CurrentFreqInfoFin.GatherFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Gather_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("EXPLORE,");
	FileContent += FString::FromInt(CurrentFreqInfoFin.ExploreFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Explore_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("CLOSE,");
	FileContent += FString::FromInt(CurrentFreqInfoFin.CloseFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Close_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("MID,");
	FileContent += FString::FromInt(CurrentFreqInfoFin.MidFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Mid_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FAR,");
	FileContent += FString::FromInt(CurrentFreqInfoFin.FarFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(player->style->Far_Fitness);
	FileContent += TEXT("\n");

	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

		/*FPair_SaveGeneration newGeneration;
		newGeneration.GenerationNumber = evolutionNumber;
		
		for (int i = 0; i < parents.Num(); i++)
		{
			FPair_SaveItem parent1;
			parent1.x 			= parents[i].p1->x;
			parent1.y 			= parents[i].p1->y;
			parent1.DistBanding = parents[i].p1->distBand;
			parent1.Type 		= parents[i].p1->type;
			
			FPair_SaveItem parent2;
			parent2.x 			= parents[i].p2->x;
			parent2.y 			= parents[i].p2->y;
			parent2.DistBanding = parents[i].p2->distBand;
			parent2.Type 		= parents[i].p2->type;
			
			FPair_SaveItem child1;
			child1.x 			= parents[i].c1->x;
			child1.y 			= parents[i].c1->y;
			child1.DistBanding 	= parents[i].c1->distBand;
			child1.Type 		= parents[i].c1->type;
			
			FPair_SaveItem child2;
			child2.x 			= parents[i].c2->x;
			child2.y 			= parents[i].c2->y;
			child2.DistBanding 	= parents[i].c2->distBand;
			child2.Type 		= parents[i].c2->type;
			
			FPair_SaveItems tempItem;
			tempItem.p1 = parent1;
			tempItem.p2 = parent2;
			tempItem.c1 = child1;
			tempItem.c2 = child2;
			
			newGeneration.GenerationPairs.Add(tempItem);
		}
		
		EvoGenerations.Add(newGeneration);
		
		//set vals
		
		
		
		
	 Create output file name
	wchar_t test[80] = { '\0' };
	swprintf(test, sizeof(test), L"C:\\Users\\bobby\\Desktop\\Uni\\Test\\Prototype 1\\Output\\Evolution%i.csv", evolutionNumber);

	// Open a handle to the file
	HANDLE hFile = CreateFile(
		test,					// Filename
		GENERIC_WRITE,          // Desired access
		FILE_SHARE_READ,        // Share mode
		NULL,                   // Security attributes
		CREATE_NEW,             // Creates a new file, only if it doesn't already exist
		FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
		NULL);                  // Template file handle

	// return is file doesnt open
	if (hFile == INVALID_HANDLE_VALUE)
	{
		// Failed to open/create file
		return;
	}

	DWORD bytesWritten;

	// Loop through all children created and save thier quest type and location to the .csv file
	for (unsigned int i = 0; i < children.size(); i++)
	{
		wchar_t questText[80] = { '\0' };
		swprintf(questText, sizeof(questText), L"%i, , %i,\n", children[i]->type, children[i]->distBand);

		WriteFile(hFile,				// Handle to the file
			questText,					// Buffer to write
			sizeof(questText),			// Buffer size
			&bytesWritten,				// Bytes written
			nullptr);					// Overlapped
	}

	// Close the handle once we don't need it.
	CloseHandle(hFile);*/
}

