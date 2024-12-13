// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FMWidgetControllerParams& WCParam)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllorParams(WCParam);
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverLay widget class uninit, plz fill out"))
	checkf(OverlayWidgetControllerClass, TEXT("OverLay widgetcontrollor class uninit, plz fill out"))
	
	UUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	const FMWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* OverlayWidgetControllerInstance = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget -> SetWidgetController(OverlayWidgetControllerInstance);
	OverlayWidgetControllerInstance -> BroadcastInitialValues();
	
	Widget->AddToViewport();
}

