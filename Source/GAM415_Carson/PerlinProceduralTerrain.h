// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProceduralTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class GAM415_CARSON_API APerlinProceduralTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProceduralTerrain();

	// Size of the terrain
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
		int XSize = 0;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
		int YSize = 0;

	// Height multiplier for the noise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
		float ZMultiplier = 1.0f;

	// Scale for the noise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
		float NoiseScale = 1.0f;

	// Scale of the terrain
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.000001))
		float Scale = 1.0f;

	// UV Scale for the UV Map
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.000001))
		float UVScale = 1.0f;

	// How big of a "hole" to make in the terrain
	UPROPERTY(EditAnywhere)
		float radius;

	// How deep of a "hole" to make in the terrain
	UPROPERTY(EditAnywhere)
		FVector depth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Call this to alter the mesh
	UFUNCTION()
		void AlterMesh(FVector impactPoint);

private:
	UProceduralMeshComponent* proceduralMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors;
	TArray<FColor> UpVertexColors;

	int sectionID = 0;

	void CreateVertices();
	void CreateTriangles();

};
