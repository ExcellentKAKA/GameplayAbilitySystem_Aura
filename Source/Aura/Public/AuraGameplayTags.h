// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags   单例类的使用方法
 * 在此类中添加所有的Tag,并使得其他类可通过此单例类来访问所有Tag
 */
struct FAuraGameplayTags
{
	
public:
	static const FAuraGameplayTags& Get(){ return GameplayTags;}

	static void InitializeNativeGameplayTags();
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;
	
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;    //奥数,神秘
	FGameplayTag Damage_Physical;

	FGameplayTag Abilities_Attack;


	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	FGameplayTag Effects_HitReact;
private:
	static FAuraGameplayTags GameplayTags;
};
