// Free to all

#pragma once

#include "GameFramework/SaveGame.h"
#include "AriesISaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ARIESI_API UAriesISaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	
	UAriesISaveGame();

	UPROPERTY(VisibleAnywhere, Category=SavedValues)
	FString SlotName;

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	uint32 PlayerIndex;

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	uint32 CollectedCoins;

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	FString PlayerName;


	UPROPERTY(VisibleAnywhere, Category=SaveValues)
	float PlayerHealth;
	
	
};
