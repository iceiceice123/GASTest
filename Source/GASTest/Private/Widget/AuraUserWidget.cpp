// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InController)
{
	WidgetController = InController;
	WidgetControllerSet();
}