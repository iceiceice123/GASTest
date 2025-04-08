// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if(TargetASC == nullptr) return;

	check(GamePlayEffectClass);
	FGameplayEffectContextHandle ContextHandle =  TargetASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetASC->MakeOutgoingSpec(GamePlayEffectClass, 1.f, ContextHandle);
	const FActiveGameplayEffectHandle ActiveGEHandle =  TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

	const bool isInfinite = GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (isInfinite && InfinityGamePlayEffectRemovePolicy == EffectRemovePolicy::RemoveOnEndOverlap) 
	{
		ActiveGEHandleToASCMap.Add(ActiveGEHandle, TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* OverlappedActor)
{
	if (InstantGamePlayEffectApplicationPolicy == EffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(OverlappedActor, InstantGamePlayEffectClass);
	}

	if (DurationGamePlayEffectApplicationPolicy == EffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(OverlappedActor, DurationGamePlayEffectClass);
	}

	if (InfinityGamePlayEffectApplicationPolicy == EffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(OverlappedActor, InfinityGamePlayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* OverlappedActor)
{
	if (InstantGamePlayEffectApplicationPolicy == EffectApplicationPolicy::ApplyOnEndOverlap) 
	{
		ApplyEffectToTarget(OverlappedActor, InstantGamePlayEffectClass);
	}

	if (DurationGamePlayEffectApplicationPolicy == EffectApplicationPolicy::ApplyOnEndOverlap) 
	{
		ApplyEffectToTarget(OverlappedActor, DurationGamePlayEffectClass);
	}

	if (InfinityGamePlayEffectApplicationPolicy == EffectApplicationPolicy::ApplyOnEndOverlap) 
	{
		ApplyEffectToTarget(OverlappedActor, InfinityGamePlayEffectClass);
	}

	if (InfinityGamePlayEffectRemovePolicy == EffectRemovePolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OverlappedActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		
		// 先收集需要移除的Handle
		for (auto HandlePair : ActiveGEHandleToASCMap) 
		{
			if (TargetASC == HandlePair.Value) 
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		
		// 在遍历结束后再移除元素
		for (auto& Handle : HandlesToRemove) 
		{
			ActiveGEHandleToASCMap.FindAndRemoveChecked(Handle);
		}
	}
}
