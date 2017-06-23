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
	
	//* 设置AI目标 */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	void SetEnemy(APawn* InPawn);
	
	//* AI获取玩家目标 */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	class AAriesIWarriorBase* GetEnemy() const;


	//* 设置巡逻下一个目标点 */
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SetPatrolTargetPoint(FVector location);

	//* 清除BlackboardEnemyPosition */
	//暂时没用，蓝图的Task里完成这个功能了
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void ClearEnemyTargetPoint();

	//* 更新转向 */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	void UpdateControlRotation(float DeltaTime, bool bUpdatePawn);

	//* AI是否能看见目标 */
	UFUNCTION(BlueprintCallable, Category=Behavior)
	bool PawnCanBeSeen(APawn* Target);

	//* 搜寻敌人 */
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
