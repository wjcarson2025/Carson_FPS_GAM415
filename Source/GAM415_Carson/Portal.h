// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Portal.generated.h"

class GAM415_CarsonCharacter;

UCLASS()
class GAM415_CARSON_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The portal mesh //
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	// The scene capture camera component //
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* sceneCapture;

	// The render target texture for the material //
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* renderTarget;

	// The box collision component //
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	// The other portal this will be linked to //
	UPROPERTY(EditAnywhere)
	APortal* OtherPortal;

	// The material to assign the render target texture to //
	UPROPERTY(EditAnywhere)
	UMaterialInterface* material;

	// Function for the overlap event //
	UFUNCTION()
	void OnOveralpBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to sett the boolean value to false after the player has teleported//
	UFUNCTION()
	void SetBool(AGAM415_CarsonCharacter* playerChar);

	// Update the portals //
	UFUNCTION()
	void UpdatePortals();

};
