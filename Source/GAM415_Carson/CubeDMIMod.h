// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubeDMIMod.generated.h"

UCLASS()
class GAM415_CARSON_API ACubeDMIMod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeDMIMod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The Box collider
	UPROPERTY(EditAnywhere)
		UBoxComponent* boxComp;

	// The Statis mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* cubeMesh;

	// The reference to the dynamic material
	UPROPERTY(EditAnywhere)
		UMaterialInterface* baseMaterial;

	// The internal dynamic material
	UPROPERTY()
		UMaterialInstanceDynamic* dmiMaterial;

	// The overlap function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
