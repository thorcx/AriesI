// Free to all

#include "AriesI.h"
#include "AriesIWarriorBase.h"
#include "PaperSpriteComponent.h"
#include "AriesIPickupBase.h"
#include "AriesICoin.h"


// Sets default values
AAriesIWarriorBase::AAriesIWarriorBase()
	:TotalHealth(100.0f)
	,AttackRange(25.0f)
	,JumpVelocity(600.0f)
	,BaseTurnRate(45.0f)
	,BaseLookUpRate(45.0f)
	,IsStillAlive(true)
	,IsAttacking(false)
	,WeaponIndex(1)
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	bUseControllerRotationYaw	= false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll	= false;

	//设置让朝向对准移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	//让摇臂跟随playercontroller的rot
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	EffectSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ClawEffect"));
	EffectSprite->SetupAttachment(CameraBoom);

	//启用玩家输入
	OnSetPlayerController(true);

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAriesIWarriorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAriesIWarriorBase::MoveForward(float Value)
{
	if ((Controller != nullptr) && IsControlable && !IsAttacking && Value != 0.0f)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, Value);
	}
}

void AAriesIWarriorBase::MoveRight(float Value)
{
	if ((Controller != nullptr) && IsControlable && !IsAttacking && Value != 0.0f)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, Value);
	}
}

void AAriesIWarriorBase::Jump()
{
	if (IsControlable && !IsAttacking)
	{
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
}

void AAriesIWarriorBase::StopJumping()
{
	if (IsControlable)
	{
		bPressedJump = false;
		JumpKeyHoldTime = 0.0f;
	}
}

void AAriesIWarriorBase::OnAttack()
{
	if (IsControlable)
	{
		IsAttacking = true;
	}
}

void AAriesIWarriorBase::OnChangeWeapon()
{
	if (IsControlable)
	{
		//循环迭代weaponIndex
	}
}

void AAriesIWarriorBase::TurnAtRate(float Rate)
{
	if (IsControlable)
	{
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AAriesIWarriorBase::LookUpAtRate(float Rate)
{
	if (IsControlable)
	{
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

// Called every frame
void AAriesIWarriorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnCollectPickup();
}

// Called to bind functionality to input
void AAriesIWarriorBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAriesIWarriorBase::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAriesIWarriorBase::StopJumping);

	PlayerInputComponent->BindAction("Attack",			IE_Pressed, this, &AAriesIWarriorBase::OnAttack);
	PlayerInputComponent->BindAction("ChangeWeapon",	IE_Pressed, this, &AAriesIWarriorBase::OnChangeWeapon);

	PlayerInputComponent->BindAxis("MoveForward",	this, &AAriesIWarriorBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",		this, &AAriesIWarriorBase::MoveRight);

	PlayerInputComponent->BindAxis("Turn",		this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",	this, &APawn::AddControllerPitchInput);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAriesIWarriorBase::OnSetPlayerController(bool status)
{
	IsControlable = status;
}

void AAriesIWarriorBase::OnChangeHealthByAmount(float usedAmount)
{
	TotalHealth -= usedAmount;
	FOutputDeviceNull ar;
	//特殊的直接呼叫蓝图函数,蓝图函数实现表现层效果
	this->CallFunctionByNameWithArguments(TEXT("ApplyGetDamageEffect"), ar, NULL, true);
}

void AAriesIWarriorBase::OnPostAttack()
{
	IsAttacking = false;
}

void AAriesIWarriorBase::OnCollectPickup()
{
	TArray<AActor*> CollectedPickups;
	this->GetCapsuleComponent()->GetOverlappingActors(CollectedPickups);
	for (int32 i = 0; i < CollectedPickups.Num(); i++)
	{
		AAriesIPickupBase *pickupBase = Cast<AAriesIPickupBase>(CollectedPickups[i]);
		if (pickupBase && !pickupBase->IsPendingKill() && pickupBase->IsActive())
		{
			pickupBase->OnGetCollected();
			AAriesICoin *coin = Cast<AAriesICoin>(pickupBase);
			if (coin)
			{
				CollectedCoinsValue += coin->GetCoinValue();
				++CollectedCoinNumber;
			}
			pickupBase->SetActive(false);
		}
	}
}

