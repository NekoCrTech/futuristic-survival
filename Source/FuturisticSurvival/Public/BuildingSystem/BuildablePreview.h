// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/AttachmentPointData.h"
#include "BuildablePreview.generated.h"

class USphereComponent;
class UBuildableBaseDataAsset;

UCLASS()
class FUTURISTICSURVIVAL_API ABuildablePreview : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PreviewMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildablePreview", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* GoodMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildablePreview", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* BadMaterial;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess= "true"),Category = "State")
	bool bCanBeBuilt = true;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "BuildablePreview", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> AttachedActors;

	void UpdateMaterial();

protected:
	
	virtual void BeginPlay() override;

public:	
	ABuildablePreview();
	virtual void Tick(float DeltaTime) override;

	void SetPreview(const UBuildableBaseDataAsset* Data);
	void DestroyAttachments();
};


// TODO: Check on tick if is buildable or not. If current 