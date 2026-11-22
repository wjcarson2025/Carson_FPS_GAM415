// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralFromStatic.generated.h"

UCLASS()
class GAM415_CARSON_API AProceduralFromStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralFromStatic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// THe array of verts for the plane
	UPROPERTY()
	TArray<FVector> Vertices;

	// The number of triangles in the plane?
	UPROPERTY()
	TArray<int> Triangles;

	// Normals for the mesh
	UPROPERTY()
		TArray<FVector> Normals;

		TArray<FVector2D> UV0;

	UPROPERTY()
		TArray<FLinearColor> VertexColors;

		TArray<FColor> UpVertexColors;

		TArray<FProcMeshTangent> Tangents;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* baseMesh;

private:
	UProceduralMeshComponent* proceduralMesh;
	void GetMeshData();
	void CreateMesh();

};
