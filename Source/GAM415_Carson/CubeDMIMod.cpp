// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "GAM415_CarsonCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// The box component
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");

	// The static mesh for the box
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	// Setup the hierarcy
	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);

}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();

	// Call when something overlaps the component
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin);

	// Check if the base material is valid, then run code
	if (baseMaterial) {
		// Setup the DMI Material
		dmiMaterial = UMaterialInstanceDynamic::Create(baseMaterial, this);
	}

	// Make sure the cube mesh is not null, then run code
	if (cubeMesh) {
		// Apply the material to the cube mesh
		cubeMesh->SetMaterial(0, dmiMaterial);
	}
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Cast the other actor to the player character class
	AGAM415_CarsonCharacter* overlappedActor = Cast<AGAM415_CarsonCharacter>(OtherActor);

	// If the overlapped actor was cast to the player properly, then run code
	if (overlappedActor) {
		// Setup 3 float variables to assign the R, G and B values
		float randNumR = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float randNumG = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float randNumB = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

		// The random Darkness value
		float randNumD = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

		// Setup the colora s a Vector4
		FVector4 randomColor = FVector4(randNumR, randNumG, randNumB, 1.0f);

		// Check if the dynamic matiral instance has been assigned
		if (dmiMaterial) {
			// Assign the randomColor to the Color paramater of the material
			dmiMaterial->SetVectorParameterValue("Color", randomColor);

			// Set the darkness parameter value in the DMI
			dmiMaterial->SetScalarParameterValue("Darkness", randNumD);
		}
	}
}

