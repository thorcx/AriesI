// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "AriesIGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARIESI_API AAriesIGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAriesIGameModeBase();
	
	virtual void BeginPlay() override;

protected:
	//* 设定BP内UMG类型，注意这里要在蓝图的继承gamemode内指定好 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=UI)
	TSubclassOf<class UUserWidget> GameUIWidgetClass;

	//* UMG的实例*/
	UPROPERTY(BlueprintReadWrite, Category = UI)
	class UUserWidget*	GameUIWIdget;
};
