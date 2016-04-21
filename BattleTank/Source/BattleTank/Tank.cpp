// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATank::SetTurretChildActor(UChildActorComponent* TurretFromBP)
{
	if (!TurretFromBP) { return; }
	Turret = TurretFromBP;
}

void ATank::SetBarrelChildActor(UChildActorComponent* BarrelFromBP)
{
	if (!BarrelFromBP) { return; }
	Barrel = BarrelFromBP;
}

void ATank::SetTankChildActor(UChildActorComponent* TankFromBP)
{
	if (!TankFromBP) { return; }
	Tank = TankFromBP;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	GetWorld()->DeltaTimeSeconds;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("Rotate_Turret", this, &ATank::RotateTurret);
	InputComponent->BindAxis("Elevate_Turret", this, &ATank::ElevateTurret);
	InputComponent->BindAxis("Move_Tank", this, &ATank::MoveTank);
	InputComponent->BindAxis("Rotate_Tank", this, &ATank::RotateTank);
}

void ATank::RotateTurret(float Speed)
{
	if (!Turret) { return; }
	float Rotation = GetWorld()->DeltaTimeSeconds * Speed * RotationSpeed;
	Turret->AddRelativeRotation(FRotator(0, Rotation, 0));
}

void ATank::ElevateTurret(float Speed)
{
	if (!Barrel) { return; }
	float Rotation = GetWorld()->DeltaTimeSeconds * Speed * RotationSpeed;
	Barrel->AddRelativeRotation(FRotator(-Rotation, 0, 0));
}

void ATank::MoveTank(float Speed)
{
	if (!Tank) { return; }
	float Distance = GetWorld()->DeltaTimeSeconds * Speed * MovementSpeed;
	Tank->AddRelativeLocation(Tank->GetForwardVector() * Distance);
}

void ATank::RotateTank(float Speed)
{
	if (!Tank) { return; }
	float Rotation = GetWorld()->DeltaTimeSeconds * Speed * RotationSpeed;
	Tank->AddRelativeRotation(FRotator(0, Rotation, 0));
}
