// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralPlane.generated.h"

class UProceduralMeshComponent;

UCLASS()
class GAM415_CARSON_API AProceduralPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// THe array of verts for the plane
	UPROPERTY(EditAnywhere)
		TArray<FVector> Vertices;

	// The number of triangles in the plane?
	UPROPERTY(EditAnywhere)
		TArray<int> Triangles;

	// Material for the geometry
	UPROPERTY(EditAnywhere)
		UMaterialInterface* PlaneMaterial;

	// UVs for the plane
	UPROPERTY(EditAnywhere)
		TArray<FVector2D> UV0;

	// Function to create the mesh
	UFUNCTION()
		void CreateMesh();

private:

	// The procedural mesh
	UProceduralMeshComponent* proceduralMesh;

};
