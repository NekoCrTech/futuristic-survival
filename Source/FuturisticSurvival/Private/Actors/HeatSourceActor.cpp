// developed by Neko


#include "Actors/HeatSourceActor.h"

#include "Character/SurvCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

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
}

void AHeatSourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsActivated)
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
		float AppliedHeat = MaxHeatValue * HeatMultiplier;
		GEngine->AddOnScreenDebugMessage(1,1,FColor::Orange,FString::Printf(TEXT("Applied Heat: %f"), AppliedHeat));
		//TODO: Call to Statline to add Heat offset
	}
	
}

void AHeatSourceActor::OnHeatZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ASurvCharacter>(OtherActor) != nullptr && Cast<UCapsuleComponent>(OtherComp) )
	{
		ActorsInRange.AddUnique(OtherActor);
	}
}

void AHeatSourceActor::OnHeatZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ActorsInRange.Remove(OtherActor);
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
		return;
	}
	Emitter->Activate(true);
	GEngine->AddOnScreenDebugMessage(1,1,FColor::Cyan,FString::Printf(TEXT("Interacting with %s"),*GetName()));
}

bool AHeatSourceActor::IsInteractable_Implementation() const
{
	return bIsInteractableHeatSource;
}


