// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAM415_CarsonProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AGAM415_CarsonProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	// Reference to the ball mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ballMesh;

	// Reference to the splat material
	UPROPERTY(EditAnywhere)
		UMaterial* splatMaterial;

	// Make the random color variable
	UPROPERTY()
		FLinearColor randomColor;

	// The projectile material for the ball
	UPROPERTY(EditAnywhere)
		UMaterialInterface* projectileMaterial;

	// The dynamic material instance
	UPROPERTY()
		UMaterialInstanceDynamic* dmiMaterial;

public:
	AGAM415_CarsonProjectile();

protected:
	virtual void BeginPlay();

public:

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

