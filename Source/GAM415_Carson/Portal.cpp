// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "GAM415_CarsonCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup the base components //
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Portal Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture Camera");

	// Setup the parent child attachments //
	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);

	// Disable the collisions for the portal mesh //
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	// Setup the overlap event //
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOveralpBegin);
	
	// Hide the portal mesh from the scene capture //
	mesh->SetHiddenInSceneCapture(true);

	// If the material is assigned, set the material to the portal mesh //
	if (material) {
		mesh->SetMaterial(0, material);
	}
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update the portals every tick //
	UpdatePortals();

}

void APortal::OnOveralpBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Cast the player overlapping the portal to the player class in this project //
	AGAM415_CarsonCharacter playerChar = Cast<AGAM415_CarsonCharacter>(OtherActor);

	// If the player char cast was valid //
	if (playerChar)
	{
		// If the other portal has been assign and is valid //
		if (OtherPortal)
		{
			// If the player is not currently teleporting //
			if (!playerChar->isTeleporting)
			{
				// Set the player to teleporting
				playerChar->isTeleporting = true;

				// Get the location of the other portal
				FVector loc = OtherPortal->GetActorLocation();

				// Teleport the plaer to that location
				playerChar->SetActorLocation(loc);

				// Setup a timer to call the SetBool function after the timer runs out of time
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}
		}
	}
}

void APortal::SetBool(AGAM415_CarsonCharacter* playerChar)
{
	// If the playerChar is valid, set the teleporting variable to false //
	if (playerChar) {
		playerChar->isTeleporting = false;
	}
}

void APortal::UpdatePortals()
{
	if (OtherPortal)
	{
		// Get the actor location minus the location of the other portal
		FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
		
		// Get the player's camera location
		FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();

		// Get the player's camera rotation
		FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();

		// Combine the locations
		FVector CombinedLocation = camLocation + Location;

		// Set the location and rotation of the scene capture camera to show what the user would look at if they were there
		sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
	}
	
}

