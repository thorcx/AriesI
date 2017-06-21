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

	//* �����Ƿ�������� */
	UFUNCTION(BlueprintCallable, Category = "Player Attributes")
	void OnSetPlayerController(bool status);

	//* ���˺�ʱ���ã�������Ѫ�� */
	UFUNCTION(BlueprintCallable, Category = "Player Attributes")
	void OnChangeHealthByAmount(float usedAmount);

	//* ����������Ĵ����߼� */
	UFUNCTION(BlueprintCallable, Category="Player Actions")
	void OnPostAttack();

protected:
	//* ��ҵ�ǰѪ�� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attributes")
	float TotalHealth;

	//* ��ҹ�����Χ */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attributes")
	float AttackRange;


	//* ����ת������ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	
	//* ����ת������ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
	
	//* �����ٶ� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	float JumpVelocity;

	//* �Ƿ����� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	bool IsStillAlive;

	//* �Ƿ񹥻� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	bool IsAttacking;
	
	//* ������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	int32 WeaponIndex;

	//* �Ƿ�������ҿ���״̬ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Attributes")
	bool IsControlable;

	//* ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game DataTables")
	UAriesIGameTables* TablesInstance;
	

	//* �����ҡ�� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess="true"))
	class USpringArmComponent *CameraBoom;

	//* ����� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//��������Ļ�ϻ�Ч�����������������Sprite�������ǰ�棬ȡ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* EffectSprite;

public:
	FORCEINLINE class USpringArmComponent*	GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent*		GetFollowCamera() const { return FollowCamera; }


};
