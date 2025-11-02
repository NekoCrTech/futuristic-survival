// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "SurvAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttributesInitialized);

UCLASS()
class FUTURISTICSURVIVAL_API USurvAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintAssignable)
	FAttributesInitialized OnAttributeInitialized;

	UPROPERTY(ReplicatedUsing = OnRep_AttributesInitialized)
	bool bAttributesInitialized = false;

	UFUNCTION()
	void OnRep_AttributesInitialized();
	
	/** ---------------- Health ---------------- */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Attributes|Vital")
	FGameplayAttributeData Health;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Attributes|Vital")
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, MaxHealth)

	/** ---------------- Stamina ---------------- */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category="Attributes|Vital")
	FGameplayAttributeData Stamina;
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, Stamina)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category="Attributes|Vital")
	FGameplayAttributeData MaxStamina;
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, MaxStamina)

	/** ---------------- Energy ---------------- */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Energy, Category="Attributes|Vital")
	FGameplayAttributeData Energy;
	UFUNCTION()
	void OnRep_Energy(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, Energy)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxEnergy, Category="Attributes|Vital")
	FGameplayAttributeData MaxEnergy;
	UFUNCTION()
	void OnRep_MaxEnergy(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, MaxEnergy)

	/** ---------------- Thirst ---------------- */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Thirst, Category="Attributes|Vital")
	FGameplayAttributeData Thirst;
	UFUNCTION()
	void OnRep_Thirst(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, Thirst)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxThirst, Category="Attributes|Vital")
	FGameplayAttributeData MaxThirst;
	UFUNCTION()
	void OnRep_MaxThirst(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, MaxThirst)

	/** ---------------- Hunger ---------------- */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Hunger, Category="Attributes|Vital")
	FGameplayAttributeData Hunger;
	UFUNCTION()
	void OnRep_Hunger(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, Hunger)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHunger, Category="Attributes|Vital")
	FGameplayAttributeData MaxHunger;
	UFUNCTION()
	void OnRep_MaxHunger(const FGameplayAttributeData& OldValue);
	ATTRIBUTE_ACCESSORS(USurvAttributeSet, MaxHunger)
	
};
