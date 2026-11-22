// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralPlane.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AProceduralPlane::AProceduralPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Setup the procedural mesh
	proceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");

	

}

// Called when the game starts or when spawned
void AProceduralPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProceduralPlane::PostActorCreated()
{
	Super::PostActorCreated();

	CreateMesh();
}

void AProceduralPlane::PostLoad()
{
	Super::PostLoad();

	CreateMesh();
}

// Called every frame
void AProceduralPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralPlane::CreateMesh()
{
	proceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);

	// If the plane material has been set, assign it
	if (PlaneMaterial) {
		proceduralMesh->SetMaterial(0, PlaneMaterial);
	}
}

