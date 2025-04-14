// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

UENUM(BlueprintType)
enum class EffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EffectRemovePolicy
{
	RemoveOnEndOverlap,
	DoNotRemove,
};


UCLASS()
class GASTEST_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GamePlayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* OverlappedActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OverlappedActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> InstantGamePlayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EffectApplicationPolicy InstantGamePlayEffectApplicationPolicy = EffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> DurationGamePlayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EffectApplicationPolicy DurationGamePlayEffectApplicationPolicy = EffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> InfinityGamePlayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EffectApplicationPolicy InfinityGamePlayEffectApplicationPolicy = EffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EffectRemovePolicy InfinityGamePlayEffectRemovePolicy = EffectRemovePolicy::DoNotRemove;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent* > ActiveGEHandleToASCMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float ActorLevel = 1;
};
