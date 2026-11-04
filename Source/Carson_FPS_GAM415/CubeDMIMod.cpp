// Fill out your copyright notice in the Description page of Project Settings.



#include "CubeDMIMod.h"
#include "Carson_FPS_GAM415Character.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the box component for overlapping
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");

	// Create the static mesh
	cubeMesh = CreateDefaultSubobject <UStaticMeshComponent>("Cube Mesh");

	// Setup the hirarcy
	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);

}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();

	// Call the begin overlap at start
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin);

	// If the base material is valid
	if (baseMat) {
		// Setup the dmiMat material
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}

	// If the cube mesh is valid
	if (cubeMesh) {
		// Set the material on the cube
		cubeMesh->SetMaterial(0, dmiMat);
	}

}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Set the overlappedComp to the character if its the character
	ACarson_FPS_GAM415Character* overlappedComp = Cast<ACarson_FPS_GAM415Character>(OtherActor);

	// If the overlappedComp is valid, create X, Y and Z random floats between 0 and 1
	if (overlappedComp) {
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

		// Setup a Vector5 for an RGBA color on the material
		FVector4 randColor = FVector4(ranNumX, ranNumY, ranNumZ, 1.0f);
		if (dmiMat) {
			// Set the random color onto the material
			dmiMat->SetVectorParameterValue("Color", randColor);
			// Set the darkness value to the random X value
			dmiMat->SetScalarParameterValue("Darkness", ranNumX);
		}
	}

}

