// developed by Neko


#include "GameObjects/SurvProjectile.h"

#include "AbilitySystemComponent.h"
#include "Character/SurvPlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASurvProjectile::ASurvProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

	bReplicates = true;
}

void ASurvProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	OnImpact();
	
	ASurvPlayerCharacter* PlayerCharacter = Cast<ASurvPlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter)) return;
	if(!PlayerCharacter->IsAlive()) return;
	UAbilitySystemComponent* AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent) || !HasAuthority()) return;

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	OnImpact();
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	Destroy();
}

