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

	//* 声音触发的发现逻辑 */
	UFUNCTION()
	void OnHearNoise(APawn* OtherActor, const FVector &Location, float Volume);

	//* 视觉触发的发现逻辑 */
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

	//* 血量 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Behavior")
	float TotalHealth;

	//* 攻击距离 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Behavior")
	float AttackRange;

	//* 攻击力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Behavior")
	float AttackDamage;

	//* 是否存活 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Behavior")
	bool IsAlive;

	//* 是否开始攻击 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Behavior")
	bool IsAttacking;

	//* 视觉看见敌人记忆留存时间，超过时间清除Blackboard内目标 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Behavior")
	float SeenEnemyMemoryTime;

public:
	FORCEINLINE class USphereComponent* GetBodySphereTrigger() const { return BodySphereTrigger; }


};
