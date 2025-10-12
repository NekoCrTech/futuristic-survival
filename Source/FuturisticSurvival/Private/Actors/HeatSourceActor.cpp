// developed by Neko


#include "Actors/HeatSourceActor.h"

#include "Character/SurvCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StatlineComponent.h"

AHeatSourceActor::AHeatSourceActor()
{
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(Root);

	HeatZone=CreateDefaultSubobject<USphereComponent>(FName("HeatZone"));
	HeatZone->SetupAttachment(Root);
	HeatZone->OnComponentBeginOverlap.AddDynamic(this, &AHeatSourceActor::OnHeatZoneOverlapBegin);
	HeatZone->OnComponentEndOverlap.AddDynamic(this, &AHeatSourceActor::OnHeatZoneOverlapEnd);

	Emitter=CreateDefaultSubobject<UNiagaraComponent>(FName("Emitter"));
	Emitter->SetupAttachment(Root);

	PrimaryActorTick.TickInterval = 1.f;
}

void AHeatSourceActor::BeginPlay()
{
	Super::BeginPlay();
	SphereRadius = HeatZone->GetScaledSphereRadius();
	if(!IsValid(HeatFallOff))
	{
		PrimaryActorTick.SetTickFunctionEnable(false);
	}
	if (bIsActivated)
	{
		Emitter->Activate(true);
	}
	
}

void AHeatSourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsActivated || !IsValid(HeatFallOff))
	{
		return;
	}
	//TODO: Consume fuel logic
	if (ActorsInRange.Num() == 0)
	{
		return;
	}
	for (const auto Actor : ActorsInRange)
	{
		if(!IsValid(Actor))
		{
			continue;
		}
		float ActorDistance = (Actor->GetActorLocation() - this->GetActorLocation()).Length();
		ActorDistance /= SphereRadius;
		float HeatMultiplier = HeatFallOff->GetFloatValue(ActorDistance);
		GEngine->AddOnScreenDebugMessage(1,1,FColor::Orange,FString::Printf(TEXT("Applied Heat: %f"), (MaxHeatValue * HeatMultiplier)));
		Actor->GetStatline()->AdjustLocalTempOffset(MaxHeatValue * HeatMultiplier);
	}
	
}

void AHeatSourceActor::OnHeatZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//NOTE: Possible error with multiple heat sources
	ASurvCharacter* Character = Cast<ASurvCharacter>(OtherActor);
	if(IsValid(Character) && Cast<UCapsuleComponent>(OtherComp) )
	{
		ActorsInRange.AddUnique(Character);
	}
}

void AHeatSourceActor::OnHeatZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ASurvCharacter* Character = Cast<ASurvCharacter>(OtherActor);
	Character->GetStatline()->AdjustLocalTempOffset(0);
	ActorsInRange.Remove(Character);
}

FText AHeatSourceActor::GetInteractionText_Implementation()
{
	return bIsActivated ? EnableText : DisableText;
}

void AHeatSourceActor::Interact_Implementation(class ASurvCharacter* Caller)
{
	bIsActivated = !bIsActivated;
	if (!bIsActivated)
	{
		Emitter->Deactivate();
		InteractBP();
		return;
	}
	Emitter->Activate(true);
	GEngine->AddOnScreenDebugMessage(1,1,FColor::Cyan,FString::Printf(TEXT("Interacting with %s"),*GetName()));
	InteractBP();
}

bool AHeatSourceActor::IsInteractable_Implementation() const
{
	return bIsInteractableHeatSource;
}

void AHeatSourceActor::UpdateFromSave_Implementation()
{
	if (!bIsActivated)
	{
		Emitter->Activate(true);
	}
}

void AHeatSourceActor::InteractBP_Implementation()
{
}


