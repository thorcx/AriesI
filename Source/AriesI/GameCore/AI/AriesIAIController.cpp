// Free to all

#include "AriesI.h"
#include "AriesIAIController.h"
#include "AriesIEnemyBase.h"
#include "AriesIWarriorBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

DEFINE_LOG_CATEGORY_STATIC(LogAriesIAI, All, All);

AAriesIAIController::AAriesIAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	bWantsPlayerState = true;
}

void AAriesIAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AAriesIEnemyBase* enemy = Cast<AAriesIEnemyBase>(InPawn);

	if (enemy && enemy->EnemyBehaviorTreeAsset)
	{
		BlackboardComp->InitializeBlackboard(*enemy->EnemyBehaviorTreeAsset->BlackboardAsset);

		//* ��ȡBlackboard�ڵ�Key IDΪ���Ժ��ѯʱ��ʹ�� */
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyPositionKeyID = BlackboardComp->GetKeyID("EnemyPosition");
		BehaviorComp->StartTree(*enemy->EnemyBehaviorTreeAsset);

		UE_LOG(LogAriesIAI, Log, TEXT("=====>>Got the enemy and the BT started!"));
	}

}

void AAriesIAIController::BeginInactiveState()
{

}

void AAriesIAIController::SetEnemy(APawn* InPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
		if(InPawn)
			BlackboardComp->SetValueAsVector("EnemyPosition", InPawn->GetActorLocation());

		SetFocus(InPawn);
	}
}

AAriesIWarriorBase* AAriesIAIController::GetEnemy() const
{
	if (BlackboardComp)
	{
		return Cast<AAriesIWarriorBase>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}
	return nullptr;
}

void AAriesIAIController::SetPatrolTargetPoint(FVector location)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector("PatrolPosition", location);
		SetFocalPoint(location);
	}
}

void AAriesIAIController::ClearEnemyTargetPoint()
{
	if (BlackboardComp)
	{
		BlackboardComp->ClearValue("");
	}
}

void AAriesIAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	
		FVector enemyLoc = GetFocalPoint();

		if (!enemyLoc.IsZero() && GetPawn())
		{
			APawn *controlledPawn = GetPawn();
			if (controlledPawn)
			{

				FVector direction = enemyLoc - controlledPawn->GetActorLocation();

				FRotator rot = FRotationMatrix::MakeFromX(direction).Rotator();

				rot.Yaw = FRotator::ClampAxis(rot.Yaw);
				SetControlRotation(rot);

				if (bUpdatePawn)
				{
					controlledPawn->FaceRotation(rot, DeltaTime);
				}
			}
		}
	
}

bool AAriesIAIController::PawnCanBeSeen(APawn* Target)
{
	return true;
}

/*����������ֱ���õ�������Player,Ȼ������ΪĿ�꣬Ȼ������Ϊ����ʹ��Service������
����ֻ������һ�ַ���������Ҳ���Բ�ʹ��Service��ʹ��AI���UPawnSensingComponent
*/
void AAriesIAIController::OnSearchForEnemy()
{
	APawn *controlledPawn = GetPawn();
	if (!controlledPawn)
		return;
	const FVector location = controlledPawn->GetActorLocation();
	float bestDistSq = MAX_FLT;
	AAriesIWarriorBase* player = nullptr;

	for (TActorIterator<AAriesIWarriorBase> It(GetWorld()); It; ++It)
	{
		if (PawnCanBeSeen(*It))
		{
			AAriesIWarriorBase* target = *It;
			if (target && target->GetIsStillAlive())
			{
				const float distSq = (target->GetActorLocation() - location).SizeSquared();
				if (distSq < bestDistSq)
				{
					bestDistSq = distSq;
					player = target;
				}
			}
		}
	}
	if (player)
	{
		SetEnemy(player);
	}
}
