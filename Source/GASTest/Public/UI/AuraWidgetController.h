// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilitySystemComponent.h"
#include "AuraWidgetController.generated.h"


/**
 * 
 */
UCLASS()
class GASTEST_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetControllor")
    TObjectPtr<APlayerController> PlayerControllor;	
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetControllor")
	TObjectPtr<APlayerState> PlayerState;	
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetControllor")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;	
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetControllor")
	TObjectPtr<UAttributeSet> AttributeSets;
};
