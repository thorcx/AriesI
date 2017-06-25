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
	//* �趨BP��UMG���ͣ�ע������Ҫ����ͼ�ļ̳�gamemode��ָ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=UI)
	TSubclassOf<class UUserWidget> GameUIWidgetClass;

	//* UMG��ʵ��*/
	UPROPERTY(BlueprintReadWrite, Category = UI)
	class UUserWidget*	GameUIWIdget;
};
