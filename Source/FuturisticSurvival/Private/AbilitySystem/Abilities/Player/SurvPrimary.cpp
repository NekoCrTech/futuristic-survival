// developed by Neko


#include "AbilitySystem/Abilities/Player/SurvPrimary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "GameplayTags/SurvTags.h"

TArray<AActor*> USurvPrimary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0, 0, HitBoxElevationOffset);

	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation,FQuat::Identity,ECC_Visibility, Sphere, QueryParams, ResponseParams);

	TArray<AActor*> ActorsHit;
	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if(!IsValid(OverlapResult.GetActor())) continue;
		ActorsHit.AddUnique(OverlapResult.GetActor());
	}
	
	if (bDrawDebug)
	{
		DrawHitBoxOverlapDebugs(OverlapResults, HitBoxLocation);
	}
	
	return ActorsHit;
}

void USurvPrimary::SendHitReactEventToActors(TArray<AActor*> ActorsHit)
{
	for (AActor* Actor : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, SurvTags::Events::Enemy::HitReact,Payload);
	}
}

void USurvPrimary::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const
{
	DrawDebugSphere(GetWorld(),HitBoxLocation, HitBoxRadius, 16, FColor::Red,false,3.f);

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (IsValid(OverlapResult.GetActor()))
		{
			FVector DebugLocation = OverlapResult.GetActor()->GetActorLocation();
			DebugLocation.Z += 100.f;
			DrawDebugSphere(GetWorld(),DebugLocation, 30.f, 10, FColor::Green, false, 3.f);
		}
	}
}
