// Free to all

#include "AriesI.h"
#include "AriesIEnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AriesIAIController.h"
#include "AriesIWarriorBase.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAriesIEnemyBase::AAriesIEnemyBase()
	:TotalHealth(100.0f)
	,AttackRange(100.0f)
	,AttackDamage(10.0f)
	,IsAlive(true)
	,IsAttacking(false)
	,SeenEnemyMemoryTime(1.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAriesIAIController::StaticClass();

	bUseControllerRotationYaw = true;
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensor"));
	PawnSensor->SensingInterval = 0.25f; //Ò»Ãë4´Î
	PawnSensor->bOnlySensePlayers = true;
	PawnSensor->SetPeripheralVisionAngle(85.0f);

	BodySphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("BodyTriggerSphere"));
	BodySphereTrigger->SetSphereRadius(150.0f);
	BodySphereTrigger->SetupAttachment(GetMesh());

	FColor handsTriggerColor(0, 0, 255, 255);

	LeftHandTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandTriggerSphere"));
	LeftHandTrigger->SetSphereRadius(70.0f);
	LeftHandTrigger->SetupAttachment(GetMesh(), "hand_l");
	LeftHandTrigger->ShapeColor = handsTriggerColor;
	LeftHandTrigger->bGenerateOverlapEvents = false;

	RightHandTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandTriggerSphere"));
	RightHandTrigger->SetSphereRadius(70.0f);
	RightHandTrigger->SetupAttachment(GetMesh(), "hand_r");
	RightHandTrigger->ShapeColor = handsTriggerColor;
	RightHandTrigger->bGenerateOverlapEvents = false;

	GetCharacterMovement()->NavAgentProps.AgentRadius = 400.0f;
	GetCharacterMovement()->SetUpdateNavAgentWithOwnersCollisions(false);

}

// Called when the game starts or when spawned
void AAriesIEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAriesIEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensor->OnSeePawn.AddDynamic(this, &AAriesIEnemyBase::OnSeePawn);
	PawnSensor->OnHearNoise.AddDynamic(this, &AAriesIEnemyBase::OnHearNoise);

	LeftHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAriesIEnemyBase::OnHandTriggerOverlap);
	RightHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAriesIEnemyBase::OnHandTriggerOverlap);
}

// Called every frame
void AAriesIEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SeenEnemyMemoryTime > 0.0f)
	{
		SeenEnemyMemoryTime -= DeltaTime;
	}
	else {
		AAriesIAIController *con = Cast<AAriesIAIController>(GetController());
		if (con && con->GetEnemy())
		{
			con->SetEnemy(nullptr);
		}
	}
}

// Called to bind functionality to input
void AAriesIEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAriesIEnemyBase::OnPerformAttack()
{
	IsAttacking = true;
}

void AAriesIEnemyBase::OnPreAttack()
{
	LeftHandTrigger->bGenerateOverlapEvents = true;
	RightHandTrigger->bGenerateOverlapEvents = true;
}

void AAriesIEnemyBase::OnPostAttack()
{
	IsAttacking = false;
	LeftHandTrigger->bGenerateOverlapEvents = false;
	RightHandTrigger->bGenerateOverlapEvents = false;
}

void AAriesIEnemyBase::OnHearNoise(APawn* OtherActor, const FVector &Location, float Volume)
{
	AAriesIAIController *controller = Cast<AAriesIAIController>(GetController());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Noise detect %f"), Volume));
}

void AAriesIEnemyBase::OnSeePawn(APawn *OtherPawn)
{
	SeenEnemyMemoryTime = 1.0f;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("See"));
	AAriesIAIController *controller = Cast<AAriesIAIController>(GetController());
	if (controller)
	{
		AAriesIWarriorBase *player = Cast<AAriesIWarriorBase>(OtherPawn);
		if (player)
		{
			controller->SetEnemy(OtherPawn);
		}
	}
}

void AAriesIEnemyBase::OnHandTriggerOverlap( UPrimitiveComponent* OverlappedComp,AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAriesIWarriorBase* const player = Cast<AAriesIWarriorBase>(OtherActor);
	if (player)
	{
		LeftHandTrigger->bGenerateOverlapEvents = false;
		RightHandTrigger->bGenerateOverlapEvents = false;
		player->OnChangeHealthByAmount(5.0f);
	}
}

