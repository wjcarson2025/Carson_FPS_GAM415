// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415_CarsonProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AGAM415_CarsonProjectile::AGAM415_CarsonProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGAM415_CarsonProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Create the ball static mesh component
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");

	// Set as root component
	RootComponent = CollisionComp;

	// Link the ballMesh to the root component collider
	ballMesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AGAM415_CarsonProjectile::BeginPlay()
{
	// Setup 3 float variables to assign the R, G and B values
	float randNumR = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
	float randNumG = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
	float randNumB = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

	// Setup the random color
	randomColor = FLinearColor(randNumR, randNumG, randNumB, 1.0f);

	// Setup the dynamic material instance
	dmiMaterial = UMaterialInstanceDynamic::Create(projectileMaterial, this);

	// Apply the DMI to the ball
	ballMesh->SetMaterial(0, dmiMaterial);

	// Set the random color to the ball
	dmiMaterial->SetVectorParameterValue("Color", randomColor);

}

void AGAM415_CarsonProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	// If the ball hit another actor
	if (OtherActor != nullptr) {
		
		// Frame number for the quadrant of the splat texture
		float frameNumber = UKismetMathLibrary::RandomFloatInRange(0.0f, 3.0f);

		// Create the decal
		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), splatMaterial, FVector(UKismetMathLibrary::RandomFloatInRange(20.0f, 40.0f)), Hit.Location, Hit.Normal.Rotation(), 0.0f);

		// Reference the splat material
		auto MatInstance = Decal->CreateDynamicMaterialInstance();

		// Assign the color and frame number to the splat material
		MatInstance->SetVectorParameterValue("Color", randomColor);
		MatInstance->SetScalarParameterValue("Frame", frameNumber);

	}
}