// Free to all

#pragma once

#include "GameFramework/Character.h"
#include "AriesIEnemyBase.generated.h"

UCLASS()
class ARIESI_API AAriesIEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAriesIEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, Category=AIData)
	class UBehaviorTree	*EnemyBehaviorTreeAsset;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy AI")
	class UPawnSensingComponent* PawnSensor;

	UFUNCTION(BlueprintCallable, Category="Enemy AI")
	void OnPerformAttack();

	UFUNCTION(BlueprintCallable, Category="Enemy AI")
	void OnPreAttack();

	UFUNCTION(BlueprintCallable, Category="Enemy AI")
	void OnPostAttack();

	//* ���������ķ����߼� */
	UFUNCTION()
	void OnHearNoise(APawn* OtherActor, const FVector &Location, float Volume);

	//* �Ӿ������ķ����߼� */
	UFUNCTION()
	void OnSeePawn(APawn *OtherPawn);

	UFUNCTION()
	void OnHandTriggerOverlap(class UPrimitiveComponent* OverlappedComp,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Triggers, meta=(AllowPrivateAccess="true"))
	class USphereComponent* BodySphereTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Triggers, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* LeftHandTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Triggers, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* RightHandTrigger;

	//* Ѫ�� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Behavior")
	float TotalHealth;

	//* �������� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Behavior")
	float AttackRange;

	//* ������ */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Behavior")
	float AttackDamage;

	//* �Ƿ��� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Behavior")
	bool IsAlive;

	//* �Ƿ�ʼ���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Behavior")
	bool IsAttacking;

	//* �Ӿ��������˼�������ʱ�䣬����ʱ�����Blackboard��Ŀ�� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Behavior")
	float SeenEnemyMemoryTime;

public:
	FORCEINLINE class USphereComponent* GetBodySphereTrigger() const { return BodySphereTrigger; }


};
