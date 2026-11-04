// Copyright Epic Games, Inc. All Rights Reserved.

#include "Carson_FPS_GAM415Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACarson_FPS_GAM415Projectile::ACarson_FPS_GAM415Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACarson_FPS_GAM415Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// The mesh for the ball projectile
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");

	// Set as root component
	RootComponent = CollisionComp;

	// Attach the ball mesh to the root component
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


void ACarson_FPS_GAM415Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	// If it's hit something in the scene other than air and the baseMat is set
	if (OtherActor != nullptr && baseMat) 
	{
		/* Remove this code because it's not done in the BeginPlay function
		// Random floats between 0 and 1 for the color and frame number
		float ranNumR = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumG = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumB = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

		// The random color created from the random float values
		FVector4 randColor = FVector4(ranNumR, ranNumG, ranNumB, 1.0f);
		*/

		// Number for the quadrant of the splat texture to use
		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.0f, 3.0f);
		
		// Setup the Decal to be spawned at the hit location
		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.0f, 40.0f)), Hit.Location, Hit.Normal.Rotation(), 0.0f);

		// Setup the material instance
		auto MatInstance = Decal->CreateDynamicMaterialInstance();

		// Assign the color and frame number for the splat decal
		MatInstance->SetVectorParameterValue("Color", randColor);
		MatInstance->SetScalarParameterValue("Frame", frameNum);
	}
}

void ACarson_FPS_GAM415Projectile::BeginPlay()
{
	// Run the parent's BeginPlay
	Super::BeginPlay();

	// If the projectile material has been assigned, run the code
	if (projMat) 
	{
		// Setup a random color with random float values beteen 0 and 1 for R, G and B
		randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), 1.0f);

		// Setup the Dynamic Material Interface
		dmiMat = UMaterialInstanceDynamic::Create(projMat, this);

		// Set the material to the ball mesh
		ballMesh->SetMaterial(0, dmiMat);

		// Set the color to the Dynamic Material
		dmiMat->SetVectorParameterValue("ProjColor", randColor);
	}

}
