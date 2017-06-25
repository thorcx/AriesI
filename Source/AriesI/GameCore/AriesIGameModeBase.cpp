// Fill out your copyright notice in the Description page of Project Settings.

#include "AriesI.h"
#include "AriesIGameModeBase.h"
#include "Blueprint/UserWidget.h"



AAriesIGameModeBase::AAriesIGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> playerClass(TEXT("Blueprint'/Game/AriesI/Characters/BP_ShinyWarrior'"));
	if (playerClass.Class)
	{
		DefaultPawnClass = playerClass.Class;
	}
}

void AAriesIGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameUIWIdget = CreateWidget<UUserWidget>(GetWorld(), GameUIWidgetClass);
	if (GameUIWIdget)
	{
		GameUIWIdget->AddToViewport();
	}

	
}
