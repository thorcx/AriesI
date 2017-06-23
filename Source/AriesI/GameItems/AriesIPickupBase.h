// Free to all

#pragma once

#include "GameFramework/Actor.h"
#include "AriesIPickupBase.generated.h"

UCLASS()
class ARIESI_API AAriesIPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAriesIPickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//* 是否激活 */
	UFUNCTION(BlueprintPure, Category=Pickups)
	bool IsActive();

	//* 设置激活状态 */
	UFUNCTION(BlueprintCallable, Category = Pickups)
	void SetActive(bool isActive);

	UFUNCTION(BlueprintNativeEvent)
	void OnGetCollected();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Pickups, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* PickupMesh;

	bool bIsActive;

public:
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }
	
};
