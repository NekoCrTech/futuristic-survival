// developed by Neko


#include "GameObjects/SurvProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/SurvPlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayTags/SurvTags.h"
#include "Tools/SurvBlueprintLibrary.h"


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

	FGameplayEventData Payload;
	Payload.Instigator = GetOwner();
	Payload.Target = PlayerCharacter;

	USurvBlueprintLibrary::SendDamageEventToPlayer(PlayerCharacter, DamageEffect,Payload, SurvTags::SetByCaller::Projectile, Damage);
	
	Destroy();
}

