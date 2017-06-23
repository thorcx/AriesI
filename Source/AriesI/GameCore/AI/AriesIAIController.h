// Free to all

#pragma once

#include "AIController.h"
#include "AriesIAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARIESI_API AAriesIAIController : public AAIController
{
	GENERATED_BODY()
	
	AAriesIAIController();
	
public:
	//~ Begin AAIController 
	virtual void Possess(APawn* InPawn) override;
	//~ End AAIController 
	
	//~ Begin AController
	virtual void BeginInactiveState() override;
	//~ End AController
	
	//* ����AIĿ�� */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	void SetEnemy(APawn* InPawn);
	
	//* AI��ȡ���Ŀ�� */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	class AAriesIWarriorBase* GetEnemy() const;


	//* ����Ѳ����һ��Ŀ��� */
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SetPatrolTargetPoint(FVector location);

	//* ���BlackboardEnemyPosition */
	//��ʱû�ã���ͼ��Task��������������
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void ClearEnemyTargetPoint();

	//* ����ת�� */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	void UpdateControlRotation(float DeltaTime, bool bUpdatePawn);

	//* AI�Ƿ��ܿ���Ŀ�� */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	bool PawnCanBeSeen(APawn* Target);

	//* ��Ѱ���� */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	void OnSearchForEnemy();


protected:
	int32 EnemyKeyID;
	int32 EnemyPositionKeyID;

	UPROPERTY(transient)
	UBlackboardComponent*	BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent*	BehaviorComp;
	
};
