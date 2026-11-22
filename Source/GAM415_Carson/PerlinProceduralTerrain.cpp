// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProceduralTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProceduralTerrain::APerlinProceduralTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the procedural mesh
	proceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");

	// Attach it to the root
	proceduralMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APerlinProceduralTerrain::BeginPlay()
{
	Super::BeginPlay();
	
	// Creat the verts
	CreateVertices();

	// Create the triangles
	CreateTriangles();

	// Create the mesh section
	proceduralMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);

	// Apply the material
	if (Material) {
		proceduralMesh->SetMaterial(0, Material);
	}
}

// Called every frame
void APerlinProceduralTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProceduralTerrain::AlterMesh(FVector impactPoint)
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		FVector tempVector = impactPoint - this->GetActorLocation();

		if (FVector(Vertices[i] - tempVector).Size() < radius)
		{
			Vertices[i] = Vertices[i] - depth;
			proceduralMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProceduralTerrain::CreateVertices()
{
	for (int x = 0; x <= XSize; x++) 
	{
		for (int y = 0; y <= YSize; y++)
		{
			// Create the Z float
			float Z = FMath::PerlinNoise2D(FVector2D(x * NoiseScale * 0.1, y * NoiseScale * 0.10)) * ZMultiplier;

			// Log a message to the debugger
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z));

			// Add the verts
			Vertices.Add(FVector(x * Scale, y * Scale, Z));

			// Add the UV Map
			UV0.Add(FVector2D(x * UVScale, y * UVScale));
		}
	}
}

void APerlinProceduralTerrain::CreateTriangles()
{
	int Vertex = 0;

	for (int x = 0; x <= XSize; x++)
	{
		for (int y = 0; y <= YSize; y++)
		{
			// Setup the triangles based on the vertex points like in the other file, but through code
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);

			// Incriment the Vertex
			Vertex++;
		}

		// Incriment the Vertex
		Vertex++;
	}
}

