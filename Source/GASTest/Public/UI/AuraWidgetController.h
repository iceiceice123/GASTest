// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FMWidgetControllerParams
{
	GENERATED_BODY()

	FMWidgetControllerParams() {}
	FMWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC),AttributeSet(AS){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS()
class GASTEST_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllorParams(const FMWidgetControllerParams WCParams);
	virtual void BroadcastInitialValues();
	virtual void BindCallBackToDependenies();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetControllor")
    TObjectPtr<APlayerController> PlayerControllor;	
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetControllor")
	TObjectPtr<APlayerState> PlayerState;	
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetControllor")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;	
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetControllor")
	TObjectPtr<UAttributeSet> AttributeSet;
};
