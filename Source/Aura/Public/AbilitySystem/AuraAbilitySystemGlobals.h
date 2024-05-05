// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 *	本项目应用了自己的GameplayEffectContext(FGameplayEffectModCallbackData)
 *	指明修改为自己的GameplayEffectContext类要Overrider下面的函数
 *	而应用此Globals类要在 Config/Game.ini 中设置
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
