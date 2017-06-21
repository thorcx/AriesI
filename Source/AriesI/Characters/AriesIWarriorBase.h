// Free to all

#pragma once


#include "GameFramework/Character.h"
#include "AriesIGameTables.h"
#include "AriesIWarriorBase.generated.h"

UCLASS(config = Game)
class ARIESI_API AAriesIWarriorBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAriesIWarriorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Player Actions")
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void Jump();

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void StopJumping();

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void OnAttack();

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void OnChangeWeapon();

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void TurnAtRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void LookUpAtRate(float Rate);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintPure, Category="Player Attributes")
	bool GetIsStillAlive() const {return IsStillAlive;}

	UFUNCTION(BlueprintPure, Category = "Player Attributes")
	float GetHealthAmount() const { return TotalHealth; }

	//* 设置是否接受输入 */
	UFUNCTION(BlueprintCallable, Category = "Player Attributes")
	void OnSetPlayerController(bool status);

	//* 受伤害时调用，用来减血量 */
	UFUNCTION(BlueprintCallable, Category = "Player Attributes")
	void OnChangeHealthByAmount(float usedAmount);

	//* 攻击结束后的处理逻辑 */
	UFUNCTION(BlueprintCallable, Category="Player Actions")
	void OnPostAttack();

protected:
	//* 玩家当前血量 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attributes")
	float TotalHealth;

	//* 玩家攻击范围 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attributes")
	float AttackRange;


	//* 左右转向速率 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	
	//* 上下转向速率 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
	
	//* 跳起速度 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	float JumpVelocity;

	//* 是否生存 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	bool IsStillAlive;

	//* 是否攻击 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	bool IsAttacking;
	
	//* 武器编号 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	int32 WeaponIndex;

	//* 是否处于受玩家控制状态 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	bool IsControlable;

	//* 数据 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game DataTables")
	UAriesIGameTables* TablesInstance;
	

	//* 摄像机摇臂 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess="true"))
	class USpringArmComponent *CameraBoom;

	//* 摄像机 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//用来向屏幕上画效果，这里我们让这个Sprite贴着相机前面，取个巧
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* EffectSprite;

public:
	FORCEINLINE class USpringArmComponent*	GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent*		GetFollowCamera() const { return FollowCamera; }


};
