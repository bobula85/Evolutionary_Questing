// Fill out your copyright notice in the Description page of Project Settings.

#include "EvolutionManager.h"

#include "Misc/FileHelper.h"

#include "Engine.h"

#include "QuestManager.h"
#include "Initial_IntegrationCharacter.h"
#include "PlayStyleManager.h"



//Compile options for debug and logging

#define ONSCREEN_DEBUG_ENABLED = 0
#define LOGGING_ENABLED = 1



// Sets default values
void UEvolutionManager::Init(AInitial_IntegrationCharacter* p, UQuestManager* mgr)
{
	// Initialise object pointers
	m_pPlayer				= p;
	m_pQuestMgr				= mgr;

	// Initialise maximum amount of mating parents value
	m_iMaxPairs				= 50;

	// Initialise maximum population size value
	m_iMaxPopulation		= 25;

	// Initialise the number of evolutions 
	// that have taken place
	m_iEvolutionNumber		= 1;

	// The rate at which lost genetic material is reintroduced when lost
	m_iReintroRate			= 10;

	m_PreviousFreqInfoSel	= {};
	m_CurrentFreqInfoSel	= {};

	m_PreviousFreqInfoFin	= {};
	m_CurrentFreqInfoFin	= {};
}

// Initiate the various stage of the evolutionary process
void UEvolutionManager::EvolveQuests()
{
	// Update previous population stats
	m_PreviousFreqInfoSel = {};
	m_PreviousFreqInfoFin = {};

	m_PreviousFreqInfoSel = m_CurrentFreqInfoSel;
	m_PreviousFreqInfoFin = m_CurrentFreqInfoFin;
	
	// Use the player statistics to calculate the optimum fitness values
	m_pPlayer->style->CalculateFitness();

	// Evaluate all current population solutions based on player statistics
	for (int i = 0; i < m_pQuestMgr->vpPopulation.Num(); i++)
		Evaluate(m_pQuestMgr->vpPopulation[i]);

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

#ifdef LOGGING_ENABLED

	// Savle the created solutions information to
	// a .csv file
	OutputResult();

#endif

	// Increment the number of evolutions that has taken place
	m_iEvolutionNumber++;
}

void UEvolutionManager::Evaluate(UQuest* qst)
{
	// based on the qst type value set the fitness type element of the soultion
	switch (qst->m_eType)
	{
		// Kill quest type
	case TP_KILL:
	{
		// Set type fitness
		qst->m_iTypeElementFitness = m_pPlayer->style->m_iKill_Fitness;

		// based on the qst distance banding value set the fitness of distance element and the total fitness of the soultion
		switch (qst->m_eDistBand)
		{
			// Close Quests
		case DIST_CLOSE:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iClose_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iKill_Fitness + m_pPlayer->style->m_iClose_Fitness);

			break;
		}
		// Mid Quests
		case DIST_MID:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iMid_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iKill_Fitness + m_pPlayer->style->m_iMid_Fitness);
			break;
		}
		// Far away quests
		case DIST_FAR:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iFar_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iKill_Fitness + m_pPlayer->style->m_iFar_Fitness);
			break;
		}
		}

		break;
	}
	// Gather quest type
	case TP_GATHER:
	{
		// Set type fitness
		qst->m_iTypeElementFitness = m_pPlayer->style->m_iGather_Fitness;

		// based on the qst distance banding value set the fitness of distance element and the total fitness of the soultion
		switch (qst->m_eDistBand)
		{
			// Close Quests
		case DIST_CLOSE:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iClose_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iGather_Fitness + m_pPlayer->style->m_iClose_Fitness);
			break;
		}
		// Mid Quests
		case DIST_MID:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iMid_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iGather_Fitness + m_pPlayer->style->m_iMid_Fitness);
			break;
		}
		// Far away quests
		case DIST_FAR:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iFar_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iGather_Fitness + m_pPlayer->style->m_iFar_Fitness);
			break;
		}
		}

		break;
	}
	// Protect quest type
	case TP_EXPLORE:
	{
		// Set type fitness
		qst->m_iTypeElementFitness = m_pPlayer->style->m_iExplore_Fitness;

		// based on the qst distance banding value set the fitness of distance element and the total fitness of the soultion
		switch (qst->m_eDistBand)
		{
			// Close Quests
		case DIST_CLOSE:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iClose_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iExplore_Fitness + m_pPlayer->style->m_iClose_Fitness);
			break;
		}
		// Mid Quests
		case DIST_MID:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iMid_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iExplore_Fitness + m_pPlayer->style->m_iMid_Fitness);
			break;
		}
		// Far away quests
		case DIST_FAR:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iFar_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iExplore_Fitness + m_pPlayer->style->m_iFar_Fitness);
			break;
		}
		}

		break;
	}
	// Defend quest type
	case TP_FETCH:
	{
		// Set type fitness
		qst->m_iTypeElementFitness = m_pPlayer->style->m_iFetch_Fitness;

		// based on the qst distance banding value set the fitness of distance element and the total fitness of the soultion
		switch (qst->m_eDistBand)
		{
			// Close Quests
		case DIST_CLOSE:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iClose_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iFetch_Fitness + m_pPlayer->style->m_iClose_Fitness);
			break;
		}
		// Mid Quests
		case DIST_MID:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iMid_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iFetch_Fitness + m_pPlayer->style->m_iMid_Fitness);
			break;
		}
		// Far away quests
		case DIST_FAR:
		{
			qst->m_iDistElementFitness = m_pPlayer->style->m_iFar_Fitness;

			qst->m_iTotalFitness = qst->m_iTotalFitness + (m_pPlayer->style->m_iFetch_Fitness + m_pPlayer->style->m_iFar_Fitness);
			break;
		}
		}

		break;
	}
	}

	if (qst->m_iTotalFitness <= 0)
		qst->m_iTotalFitness = 1;
}

// Applies the roulette wheel selection method to select parent solutions
void UEvolutionManager::SelectRoulette()
{
	// Empty the parents vector
	m_aParents.Empty();

	// Create a vecor to hold the sum of fitness values of selection
	TArray<int> tempVec;

	// Hold the sum of fitness total value
	int sumOfFitness = 0;

	// Loop through the population and increment the sum of fitness values accordingly
	for (int i = 0; i < m_pQuestMgr->vpPopulation.Num(); i++)
	{
		if (i == 0)
			tempVec.Add(m_pQuestMgr->vpPopulation[i]->m_iTotalFitness);
		else
			tempVec.Add(tempVec[i - 1] + m_pQuestMgr->vpPopulation[i]->m_iTotalFitness);

		sumOfFitness += (m_pQuestMgr->vpPopulation[i]->m_iTotalFitness);
	}

	// Loop through the population and select maxPairs of parent solutions 
	for (int i = 0; i < m_iMaxPairs; i++)
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
				parentPair.p1 = m_pQuestMgr->vpPopulation[j];
				break;
			}
		}

		for (int j = 0; j < tempVec.Num(); j++)
		{
			if (tempVec[j] >= r2)
			{
				parentPair.p2 = m_pQuestMgr->vpPopulation[j];
				break;
			}
		}

		if (parentPair.p1 == parentPair.p2)
			i--;
		else
			// add the parent pair to the parent vector
			m_aParents.Add(parentPair);
	}
}

// Not yet used. May be used in the next unit
void UEvolutionManager::SelectRanked()
{
	// Empty the parents vector
	m_aParents.Empty();

	// Array to hold the population sorted by fitness
	TArray<UQuest*> tempVecSortedPop;

	// Add all quests to the sort array
	for (int i = 0; i < m_pQuestMgr->vpPopulation.Num(); i++)
		tempVecSortedPop.Add(m_pQuestMgr->vpPopulation[i]);

	// Sort the array using a basic lambda function
	tempVecSortedPop.Sort([](const UQuest& a, const UQuest& b) { return a.m_iTotalFitness < b.m_iTotalFitness; });

	// calculates the total sum of all the ranked positions in the array (eg an array of 4 is 10 as 1+2+3+4 = 10)
	double sumOfRanks = ((double)tempVecSortedPop.Num() + 1) * ((double)tempVecSortedPop.Num() / 2);

	TArray<double> probs;

	for (int i = 0; i < tempVecSortedPop.Num(); i++)
	{
		//calculates raks probablility i = rank
		double prob = ((i+1) / sumOfRanks) * 100;
		probs.Add(prob);
	}

	// Array to hold the stacked probaility of selection values
	TArray<double> stackedProbabilities;

	// variable to hold the sum of all of the probabilities (should be 100%)
	double sumOfRankedFitness = 0;

	// Loop through the population and increment the sum of fitness values accordingly
	// so that the probabilities stack ready to be selected from eq |  prob1 |   prob2 = prob1 +prob2     |		prob3 = prob2 + prob3			| etc
	for (int i = 0; i < probs.Num(); i++)
	{
		if (i == 0)
			stackedProbabilities.Add(probs[i]);
		else
			// |  prob1 |   prob2 = prob1 +prob2     |		prob3 = prob2 + prob3			| etc
			stackedProbabilities.Add(stackedProbabilities[i - 1] + probs[i]);

		// should be 100%
		sumOfRankedFitness += probs[i];
	}

	// Loop though maxPairs to select all parent pairs
	for (int i = 0; i < m_iMaxPairs; i++)
	{
		// Generate a random number for each parent selection between 1 and sum of fitness (should be 100)
		int r1 = FMath::RandRange(1, sumOfRankedFitness);
		int r2 = FMath::RandRange(1, sumOfRankedFitness);

		FPair parentPair;

		for (int j = 0; j < stackedProbabilities.Num(); j++)
		{	
			// If the random number generated falls within the probaility value of
			// a population solution then add it to the pair object as one of the parents.
			if (stackedProbabilities[j] >= (double)r1)
			{
				parentPair.p1 = m_pQuestMgr->vpPopulation[j];
				break;
			}
		}

		// If the random number generated falls within the probaility value of
		// a population solution then add it to the pair object as one of the parents.
		for (int j = 0; j < stackedProbabilities.Num(); j++)
		{
			if (stackedProbabilities[j] >= (double)r2)
			{
				parentPair.p2 = m_pQuestMgr->vpPopulation[j];
				break;
			}
		}

		// if parents are the same solution then repeat the selection process
		if (parentPair.p1 == parentPair.p2)
			i--;
		else
			// add the parent pair to the parent vector
			m_aParents.Add(parentPair);
	}

}

void UEvolutionManager::Combine()
{
	m_aChildren.Empty();

	for (int i = 0; i < m_aParents.Num(); i++)
	{
		// Create the two new children
		UQuest* child1 = NewObject<UQuest>();
		UQuest* child2 = NewObject<UQuest>();
		
		m_aParents[i].c1 = child1;
		m_aParents[i].c2 = child2;

		// Initialise children quests using elements of the parents
		child1->Init(m_aParents[i].p1->m_eDistBand, m_aParents[i].p2->m_eType, L"Quest? 1", m_pQuestMgr);
		child2->Init(m_aParents[i].p2->m_eDistBand, m_aParents[i].p1->m_eType, L"Quest? 2", m_pQuestMgr);


		// Update child solutions distance, name and description information
		child1->SetDistanceFromPlayer(m_pPlayer->GetActorLocation());
		child2->SetDistanceFromPlayer(m_pPlayer->GetActorLocation());
		child1->setDistName();
		child2->setDistName();

		child1->setQuestName();
		child2->setQuestName();

		child1->setDescription();
		child2->setDescription();

		// Add children to the children vector
		m_aChildren.Add(child1);
		m_aChildren.Add(child2);
	}
}

void UEvolutionManager::CalculateFrequencySel(Ffrequency_Count* count)
{
	// Loop which caounts the the amount of each quest type element in the current population
	for (int i = 0; i < m_aChildren.Num(); i++)
	{
		switch (m_aChildren[i]->m_eType)
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

		switch (m_aChildren[i]->m_eDistBand)
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

	// Calculate the amount each type element appears in the population as a percentage
	count->KillFreq		= ((float)count->KillCount	/ (float)m_aChildren.Num()) * 100;
	count->GatherFreq	= ((float)count->GatherCount/ (float)m_aChildren.Num()) * 100;
	count->FetchFreq	= ((float)count->FetchCount	/ (float)m_aChildren.Num()) * 100;
	count->ExploreFreq	= ((float)count->ExploreCount/ (float)m_aChildren.Num()) * 100;

	// Add the type frequencies to an array for later use
	count->TypeFreqs.Add(count->KillFreq);
	count->TypeFreqs.Add(count->GatherFreq);
	count->TypeFreqs.Add(count->FetchFreq);
	count->TypeFreqs.Add(count->ExploreFreq);

	// Check for any quests type frequencies of zero. This indicates aloss of genetic material from the population
	if (count->KillFreq == 0.0 || count->GatherFreq == 0.0 || count->FetchFreq == 0.0 || count->ExploreFreq == 0.0)
	{
		// Add any lost type enum values to a list for the mutation function to use later
		if (count->KillFreq == 0.0)
			count->LowTypeFreqs.Add((int)TP_KILL);
		if (count->GatherFreq == 0.0)
			count->LowTypeFreqs.Add((int)TP_GATHER);
		if (count->FetchFreq == 0.0)
			count->LowTypeFreqs.Add((int)TP_FETCH);
		if (count->ExploreFreq == 0.0)
			count->LowTypeFreqs.Add((int)TP_EXPLORE);

		// Set low frequency to true so that mutation is triggered
		count->lowTypeFreq = true;
	}

	// Calculate the amount each distance element appears in the population as a percentage
	count->CloseFreq	= ((float)count->CloseCount	/ (float)m_aChildren.Num())*100;
	count->MidFreq		= ((float)count->MidCount	/ (float)m_aChildren.Num())*100;
	count->FarFreq		= ((float)count->FarCount	/ (float)m_aChildren.Num())*100;
	
	// Add the type frequencies to an array for later use
	count->DistFreqs.Add(count->CloseFreq);
	count->DistFreqs.Add(count->MidFreq);
	count->DistFreqs.Add(count->FarFreq);

	// Check for any quests distance frequencies of zero. This indicates aloss of genetic material from the population
	if (count->CloseFreq == 0.0 || count->MidFreq == 0.0 || count->FarFreq == 0.0)
	{
		// Add any lost distance enum values to a list for the mutation function to use later
		if (count->CloseFreq == 0.0)
			count->LowDistFreqs.Add((int)DIST_CLOSE);
		if (count->MidFreq == 0.0)
			count->LowDistFreqs.Add((int)DIST_MID);
		if (count->FarFreq == 0.0)
			count->LowDistFreqs.Add((int)DIST_FAR);

		// Set low frequency to true so that mutation is triggered
		count->lowDistFreq = true;
	}
}

void UEvolutionManager::Mutate()
{
	// Create a container to hold the population frequency information
	m_CurrentFreqInfoSel = {};

	// Get frequency information 
	CalculateFrequencySel(&m_CurrentFreqInfoSel);

	// if an element type is missing add it back in as below
	if (m_CurrentFreqInfoSel.lowTypeFreq || m_CurrentFreqInfoSel.lowDistFreq)
	{
		// misssing type element
		if (m_CurrentFreqInfoSel.lowTypeFreq)
		{
			// for each type element that is missing 
			for (int i = 0; i < m_CurrentFreqInfoSel.LowTypeFreqs.Num(); i++)
			{
				// add in 5 random ones
				for (int j = 0; j < m_iReintroRate; j++)
				{
					//generate a random index to change
					int randIndex = FMath::RandRange(0, (m_aChildren.Num() - 1));

					// set it's type to the missing type
					m_aChildren[randIndex]->setType((QuestType)m_CurrentFreqInfoSel.LowTypeFreqs[i]);

					m_aChildren[randIndex]->setQuestName();
					m_aChildren[randIndex]->setDescription();
				}
			}
		}
		// missing distance 
		if (m_CurrentFreqInfoSel.lowDistFreq)
		{	
			// for each distance banding that is missing
			for (int i = 0; i < m_CurrentFreqInfoSel.LowDistFreqs.Num(); i++)
			{
				int count = 0;
				
				int minRadius = 0;
				int maxRadius = 0; 

				//set the random number generater bounding based on missing dist type
				switch(m_CurrentFreqInfoSel.LowDistFreqs[i])
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

				while (count < m_iReintroRate)
				{
					// Generate random index 
					int randIndex = FMath::RandRange(0, (m_aChildren.Num()-1));

					// Generate random angle
					int randAngle = FMath::RandRange(0, 360);
					// Generate random distance from point
					int randOffset = FMath::RandRange(minRadius, maxRadius);

					// Get x and y coordiates based on angle and offest dist
					int newX = randOffset * cos(randAngle); // FMath::RandRange(-2000, 2000);
					int newY = randOffset * sin(randAngle); // FMath::RandRange(-2000, 2000);

					// set x and y cords
					m_aChildren[randIndex]->setLocation(FVector(newX, newY, 130));
					

					// Update quest location data
					m_aChildren[randIndex]->SetDistanceFromPlayer(m_pPlayer->GetActorLocation());

					m_aChildren[randIndex]->setDistName();
					m_aChildren[randIndex]->setQuestName();
					m_aChildren[randIndex]->setDescription();

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
	for (int i = 0; i < m_aChildren.Num(); i++)
		Evaluate(m_aChildren[i]);

	// Loop through the current population and include quests accepted but 
	// not completed in the next generation by default
	for (int i = 0; i < m_pQuestMgr->vpPopulation.Num(); i++)
	{
		if (m_pQuestMgr->vpPopulation[i]->m_eStatus == ST_ACCEPTED)
			tempNewPop.Add(m_pQuestMgr->vpPopulation[i]);
	}

	// Array to hold the population sorted by fitness
	TArray<UQuest*> tempSortPop;

	// Add all children to the sort array
	for (int i = 0; i < m_aChildren.Num(); i++)
		tempSortPop.Add(m_aChildren[i]);

	// Sort the array using a basic lambda function
	tempSortPop.Sort([](const UQuest& a, const UQuest& b) { return a.m_iTotalFitness < b.m_iTotalFitness; });

	// calculates the total sum of all the ranked positions in the array (eg an array of 4 is 10 as 1+2+3+4 = 10)
	double sumOfRanks = ((double)tempSortPop.Num() + 1) * ((double)tempSortPop.Num() / 2);

	TArray<double> probs;

	for (int i = 0; i < tempSortPop.Num(); i++)
	{
		//calculates ranks probablility i = rank
		double prob = ((i + 1) / sumOfRanks) * 100;
		probs.Add(prob);
	}

	TArray<double> stackedProbabilities;
	double sumOfRankedFitness = 0;

	// Loop through the population and increment the sum of fitness values accordingly
	for (int i = 0; i < probs.Num(); i++)
	{
		if (i == 0)
			stackedProbabilities.Add(probs[i]);
		else
			stackedProbabilities.Add(stackedProbabilities[i - 1] + probs[i]);

		sumOfRankedFitness += probs[i];
	}

	// Loop though the remaining space in the next generation and select at random
	// the children that will be added based on their fitness proportionate probailities
	while(tempNewPop.Num() < m_iMaxPopulation)
	{
		int r1 = FMath::RandRange(1, sumOfRankedFitness);

		int tempNewPopSize = tempNewPop.Num();

		for (int j = 0; j < stackedProbabilities.Num(); j++)
		{
			if (stackedProbabilities[j] >= (double)r1)
			{
				int addedCheck = tempNewPop.Num();

				if (tempNewPop.AddUnique(tempSortPop[j]) == addedCheck)
					tempSortPop[j]->m_bChosen = true;

				break;
			}
		}
	}

	// Empty the quest managers population list
	m_pQuestMgr->vpPopulation.Empty();

	// Add the new generation to the quest manager
	for (int i = 0; i < tempNewPop.Num(); i++)
		m_pQuestMgr->vpPopulation.Add(tempNewPop[i]);
}

void UEvolutionManager::CalculateFrequencyFin(Ffrequency_Count* count)
{
	// Loop which caounts the the amount of each quest type element in the current population
	for (int i = 0; i < m_pQuestMgr->vpPopulation.Num(); i++)
	{
		switch (m_pQuestMgr->vpPopulation[i]->m_eType)
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

		switch (m_pQuestMgr->vpPopulation[i]->m_eDistBand)
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

	// Calculate the amount each type element appears in the population as a percentage
	count->KillFreq = ((float)count->KillCount / (float)m_pQuestMgr->vpPopulation.Num()) * 100;
	count->GatherFreq = ((float)count->GatherCount / (float)m_pQuestMgr->vpPopulation.Num()) * 100;
	count->FetchFreq = ((float)count->FetchCount / (float)m_pQuestMgr->vpPopulation.Num()) * 100;
	count->ExploreFreq = ((float)count->ExploreCount / (float)m_pQuestMgr->vpPopulation.Num()) * 100;

	// Add the type frequencies to an array for later use
	count->TypeFreqs.Add(count->KillFreq);
	count->TypeFreqs.Add(count->GatherFreq);
	count->TypeFreqs.Add(count->FetchFreq);
	count->TypeFreqs.Add(count->ExploreFreq);

	// Calculate the amount each type element appears in the population as a percentage
	count->CloseFreq = ((float)count->CloseCount / (float)m_pQuestMgr->vpPopulation.Num()) * 100;
	count->MidFreq = ((float)count->MidCount / (float)m_pQuestMgr->vpPopulation.Num()) * 100;
	count->FarFreq = ((float)count->FarCount / (float)m_pQuestMgr->vpPopulation.Num()) * 100;

	// Add the type frequencies to an array for later use
	count->DistFreqs.Add(count->CloseFreq);
	count->DistFreqs.Add(count->MidFreq);
	count->DistFreqs.Add(count->FarFreq);
}

void UEvolutionManager::DisplayChangeSel()
{
	if (m_PreviousFreqInfoSel.TypeFreqs.Num() == 0)
		return;

	TArray<float> percentIncrease;

	for (int i = 0; i < m_CurrentFreqInfoSel.TypeFreqs.Num(); i++)
	{
		// Compare current and previous frequency data to get the increase amount
		float increase = m_CurrentFreqInfoSel.TypeFreqs[i] - m_PreviousFreqInfoSel.TypeFreqs[i];

		// Calculate the increase as a percentage
		float percentInc = (increase / m_CurrentFreqInfoSel.TypeFreqs[i]) * 100;

		// Add the percentage increase to an array for later use
		percentIncrease.Add(percentInc);
	}

	// Set the current type frequency values
	m_CurrentFreqInfoSel.KillChange		= percentIncrease[0];
	m_CurrentFreqInfoSel.GatherChange	= percentIncrease[1];
	m_CurrentFreqInfoSel.FetchChange	= percentIncrease[2];
	m_CurrentFreqInfoSel.ExploreChange	= percentIncrease[3];


	for (int i = 0; i < m_CurrentFreqInfoSel.DistFreqs.Num(); i++)
	{
		// Compare current and previous frequency data to get the increase amount
		float increase = m_CurrentFreqInfoSel.DistFreqs[i] - m_PreviousFreqInfoSel.DistFreqs[i];

		// Calculate the increase as a percentage
		float percentInc = (increase / m_CurrentFreqInfoSel.DistFreqs[i]) * 100;

		// Add the percentage increase to an array for later use
		percentIncrease.Add(percentInc);
	}

	// Set the current distance frequency values
	m_CurrentFreqInfoSel.CloseChange	= percentIncrease[4];
	m_CurrentFreqInfoSel.MidChange		= percentIncrease[5];
	m_CurrentFreqInfoSel.FarChange		= percentIncrease[6];

#ifdef DEBUG_ENABLED

	// Onscreen debug output
	if (GEngine)
	{
		FString Gen = FString(TEXT("GENERATION NUMBER: "));
		Gen += FString::FromInt(m_iEvolutionNumber);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Green, Gen, false);

		for (int i = 0; i < percentIncrease.Num(); i++)
		{
			if (percentIncrease[i] > 0)
			{
				FString temp = m_pQuestMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString::SanitizeFloat(percentIncrease[i]);
				temp += FString(TEXT("% Increased"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Green, temp, false);
			}
			if (percentIncrease[i] < 0)
			{
				FString temp = m_pQuestMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString::SanitizeFloat(percentIncrease[i]);
				temp += FString(TEXT("% Decrease"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Red, temp, false);
			}
			if (percentIncrease[i] == 0)
			{
				FString temp = m_pQuestMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString(TEXT("No Change"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Yellow, temp, false);
			}
		}
	}
#endif

}

void UEvolutionManager::DisplayChangeFin()
{
	m_CurrentFreqInfoFin = {};

	// Get frequency information 
	CalculateFrequencyFin(&m_CurrentFreqInfoFin);

	if (m_PreviousFreqInfoFin.TypeFreqs.Num() == 0)
		return;

	TArray<float> percentIncreaseFin;

	for (int i = 0; i < m_CurrentFreqInfoFin.TypeFreqs.Num(); i++)
	{
		// Compare surrent and previous frequency data to get the increase amount
		float increase = m_CurrentFreqInfoFin.TypeFreqs[i] - m_PreviousFreqInfoFin.TypeFreqs[i];

		// Calculate the increase as a percentage
		float percentInc = (increase / m_CurrentFreqInfoFin.TypeFreqs[i]) * 100;

		// Add the percentage increase to an array for later use
		percentIncreaseFin.Add(percentInc);
	}

	// Set the current type frequency values for 
	m_CurrentFreqInfoFin.KillChange			= percentIncreaseFin[0];
	m_CurrentFreqInfoFin.GatherChange		= percentIncreaseFin[1];
	m_CurrentFreqInfoFin.FetchChange		= percentIncreaseFin[2];
	m_CurrentFreqInfoFin.ExploreChange		= percentIncreaseFin[3];

	for (int i = 0; i < m_CurrentFreqInfoFin.DistFreqs.Num(); i++)
	{
		// Compare current and previous frequency data to get the increase amount
		float increase = m_CurrentFreqInfoFin.DistFreqs[i] - m_PreviousFreqInfoFin.DistFreqs[i];

		// Calculate the increase as a percentage
		float percentInc = (increase / m_CurrentFreqInfoFin.DistFreqs[i]) * 100;

		// Add the percentage increase to an array for later use
		percentIncreaseFin.Add(percentInc);
	}

	// Set the current distance frequency values
	m_CurrentFreqInfoFin.CloseChange		= percentIncreaseFin[4];
	m_CurrentFreqInfoFin.MidChange			= percentIncreaseFin[5];
	m_CurrentFreqInfoFin.FarChange			= percentIncreaseFin[6];

#ifdef DEBUG_ENABLED

	// Onscreen debug output
	if (GEngine)
	{
		FString Gen = FString(TEXT("GENERATION NUMBER: "));
		Gen += FString::FromInt(m_iEvolutionNumber);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Green, Gen, false);

		for (int i = 0; i < percentIncreaseFin.Num(); i++)
		{
			if (percentIncreaseFin[i] > 0)
			{
				FString temp = m_pQuestMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString::SanitizeFloat(percentIncreaseFin[i]);
				temp += FString(TEXT("% Increased"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Green, temp, false);
			}
			if (percentIncreaseFin[i] < 0)
			{
				FString temp = m_pQuestMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString::SanitizeFloat(percentIncreaseFin[i]);
				temp += FString(TEXT("% Decrease"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Red, temp, false);
			}
			if (percentIncreaseFin[i] == 0)
			{
				FString temp = m_pQuestMgr->getTypeName(i);
				temp += FString(TEXT(": "));
				temp += FString(TEXT("No Change"));

				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.f, FColor::Yellow, temp, false);
			}
		}
	}

#endif
}

void UEvolutionManager::OutputResult()
{
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSourceDir()) + TEXT("/DataOutput/MessageLog.csv");
	FString FileContent = TEXT("\n");

	FileContent += TEXT("GENERATION NUMBER,  ");
	FileContent += FString::FromInt(m_iEvolutionNumber);
	FileContent += TEXT(",\n");
	FileContent += TEXT("\n");

	FileContent += TEXT("SELECTION STAGE \n");
	FileContent += TEXT("\n");

	FileContent += TEXT("KILL,");
	FileContent += FString::FromInt(m_CurrentFreqInfoSel.KillFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iKill_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FETCH,");
	FileContent += FString::FromInt(m_CurrentFreqInfoSel.FetchFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iFetch_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("GATHER,");
	FileContent += FString::FromInt(m_CurrentFreqInfoSel.GatherFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iGather_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("EXPLORE,");
	FileContent += FString::FromInt(m_CurrentFreqInfoSel.ExploreFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iExplore_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("CLOSE,");
	FileContent += FString::FromInt(m_CurrentFreqInfoSel.CloseFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iClose_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("MID,");
	FileContent += FString::FromInt(m_CurrentFreqInfoSel.MidFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iMid_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FAR,");
	FileContent += FString::FromInt(m_CurrentFreqInfoSel.FarFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iFar_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FINAL STAGE \n");
	FileContent += TEXT("\n");

	FileContent += TEXT("KILL,");
	FileContent += FString::FromInt(m_CurrentFreqInfoFin.KillFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iKill_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FETCH,");
	FileContent += FString::FromInt(m_CurrentFreqInfoFin.FetchFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iFetch_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("GATHER,");
	FileContent += FString::FromInt(m_CurrentFreqInfoFin.GatherFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iGather_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("EXPLORE,");
	FileContent += FString::FromInt(m_CurrentFreqInfoFin.ExploreFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iExplore_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("CLOSE,");
	FileContent += FString::FromInt(m_CurrentFreqInfoFin.CloseFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iClose_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("MID,");
	FileContent += FString::FromInt(m_CurrentFreqInfoFin.MidFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iMid_Fitness);
	FileContent += TEXT("\n");

	FileContent += TEXT("FAR,");
	FileContent += FString::FromInt(m_CurrentFreqInfoFin.FarFreq);
	FileContent += TEXT(",%,");
	FileContent += TEXT("FITNESS,");
	FileContent += FString::FromInt(m_pPlayer->style->m_iFar_Fitness);
	FileContent += TEXT("\n");

	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

