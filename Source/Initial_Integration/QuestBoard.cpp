// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestBoard.h"

AQuestBoard::AQuestBoard()
{
	boardMesh = CreateDefaultSubobject<UStaticMeshComponent>("BoardMesh");

	boardID = FName("Set board ID!");
}