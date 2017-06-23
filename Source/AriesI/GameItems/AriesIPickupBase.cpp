// Free to all

#include "AriesI.h"
#include "AriesIPickupBase.h"


// Sets default values
AAriesIPickupBase::AAriesIPickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bIsActive = true;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void AAriesIPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAriesIPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAriesIPickupBase::IsActive()
{
	return bIsActive;
}

void AAriesIPickupBase::SetActive(bool isActive)
{
	bIsActive = isActive;
}

void AAriesIPickupBase::OnGetCollected_Implementation()
{
	// to do
}

