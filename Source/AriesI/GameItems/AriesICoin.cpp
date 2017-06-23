// Free to all

#include "AriesI.h"
#include "AriesICoin.h"




AAriesICoin::AAriesICoin()
{
	CoinValue = 20.0f;
}

void AAriesICoin::OnGetCollected_Implementation()
{
	Super::OnGetCollected_Implementation();
	Destroy();
}

float AAriesICoin::GetCoinValue()
{
	return CoinValue;
}
