// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward Declarations
class UTankBarrel;

class UTankTurret;

class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};


//Hold barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToset, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetRoundsLeft() const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	void MoveBarrelTowards(FVector AimDirection);

	UTankTurret* Turret = nullptr;

	//local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;

	UPROPERTY(EditAnyWhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditAnyWhere, Category = Firing)
	float LaunchSpeed = 10000; // Sensible starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 RoundsLeft = 3;

	bool IsBarrelMoving();

	FVector AimDirection;
};
