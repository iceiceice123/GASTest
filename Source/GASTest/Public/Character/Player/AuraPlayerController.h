// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class GASTEST_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	// TObjectPtr<IEnemyInterface> LastActor;
	// TObjectPtr<IEnemyInterface> ThisActor;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};

