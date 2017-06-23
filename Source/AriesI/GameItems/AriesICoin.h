// Free to all

#pragma once

#include "GameItems/AriesIPickupBase.h"
#include "AriesICoin.generated.h"

/**
 * 
 */
UCLASS()
class ARIESI_API AAriesICoin : public AAriesIPickupBase
{
	GENERATED_BODY()
	
public:
	AAriesICoin();

	void OnGetCollected_Implementation() override;

	float GetCoinValue();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Coins, meta=(BlueprintProtected="true"))
	float CoinValue;
	
};
