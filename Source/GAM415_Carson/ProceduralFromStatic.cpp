// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralFromStatic.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProceduralFromStatic::AProceduralFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize the meshes
	proceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");

	// Setup the hierarchy
	RootComponent = proceduralMesh;
	baseMesh->SetupAttachment(proceduralMesh);

}

// Called when the game starts or when spawned
void AProceduralFromStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProceduralFromStatic::PostActorCreated()
{
	Super::PostActorCreated();
	GetMeshData();
}

void AProceduralFromStatic::PostLoad()
{
	Super::PostLoad();
	GetMeshData();

}

// Called every frame
void AProceduralFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralFromStatic::GetMeshData()
{
	// Get the mesh from the referenced mesh
	UStaticMesh* mesh = baseMesh->GetStaticMesh();

	// Check to see if there is a mesh, then run code
	if (mesh) {
		// Get the static mesh data from the loaded mesh
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents);
		proceduralMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents);

		// Create the mesh
		CreateMesh();
	}
}

void AProceduralFromStatic::CreateMesh()
{
	// check to see if we have a base mesh, then run code
	if (baseMesh) {
		// Create the mesh from the referenced mesh
		proceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	}
}

