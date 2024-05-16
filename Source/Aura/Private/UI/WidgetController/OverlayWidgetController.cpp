// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"

#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();  Base is empty


	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHealth());

	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAS()->GetMaxHealth());

	
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//Super::BindCallbacksToDependencies(); super fun is empty
	
	GetAuraPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	GetAuraPS()->OnLevelChangedDelegate.AddLambda(
	[this](int32 NewLevel)
	{
		OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
	}
	);
	

	

	//这个委托不是Dynamic，所以绑定事件要用.AddUObject
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});


	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
	);

	if(GetAuraASC())
	{
		GetAuraASC()->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
		
		//需要考虑赋予Ability和绑定的先后执行问题，这是不确定的，如果没绑定委托就执行回调这是危险的
		//如果检测到ASC中赋予能力的函数已经执行，说明还未绑定委托，所以直接执行回调。否则绑定委托等待赋予能力的执行
		if(GetAuraASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}
		

		GetAuraASC()->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		for(const auto Tag : AssetTags)
		{
			//For example, say that Tag = Message.HealthPotion
			//"Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion")wil return False

			// const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
			// GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green,Msg);
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if(Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow* Row = GetDataTableByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowSignature.Broadcast(*Row);
			}
			
		}
	}
	);
	}
	
}


void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,const FGameplayTag& Slot, const FGameplayTag& PrevSlot) const
{
	
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	
	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PrevSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;
	//Broadcast empty info if PreviousSlot is a valid slot. Only if equipping an already-equipped spell
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;
	AbilityInfoDelegate.Broadcast(Info);

	
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) 
{

	const ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInfo;

	checkf(LevelUpInfo, TEXT("Unabled to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));
	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if(Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;
		
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}



