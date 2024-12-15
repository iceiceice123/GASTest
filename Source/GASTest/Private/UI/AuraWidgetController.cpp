// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllorParams(const FMWidgetControllerParams WCParams)
{
	PlayerControllor = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}
