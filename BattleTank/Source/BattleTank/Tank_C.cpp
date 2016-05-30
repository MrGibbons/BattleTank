// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank_C.h"


// Sets default values
ATank_C::ATank_C()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	Tank = CreateDefaultSubobject<UChildActorComponent>(TEXT("Tank"));
	Tank->AttachTo(RootComponent);

	Turret = CreateDefaultSubobject<UChildActorComponent>(TEXT("Turret"));
	Turret->AttachTo(Tank);

	Barrel = CreateDefaultSubobject<UChildActorComponent>(TEXT("Barrel"));
	Barrel->AttachTo(Turret);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	// The camera follows at this distance behind the character	
	CameraBoom->TargetArmLength = 300.0f;
	// Rotate the arm based on the controller
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	// Camera does not rotate relative to arm
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ATank_C::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank_C::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATank_C::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Rotate_Turret", this, &ATank_C::RotateTurret);
	InputComponent->BindAxis("Elevate_Turret", this, &ATank_C::ElevateTurret);
	InputComponent->BindAxis("Move_Tank", this, &ATank_C::MoveTank);
	InputComponent->BindAxis("Rotate_Tank", this, &ATank_C::RotateTank);
}

void ATank_C::RotateTurret(float Value)
{
	if (!Turret) { return; }
	float Rotation = GetWorld()->DeltaTimeSeconds * Value * RotationSpeed;
	Turret->AddRelativeRotation(FRotator(0, Rotation, 0));

	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rotation * (2.f/5));
}

void ATank_C::ElevateTurret(float Value)
{
	if (!Barrel) { return; }
	float Rotation = GetWorld()->DeltaTimeSeconds * Value * RotationSpeed;
	Barrel->AddRelativeRotation(FRotator(Rotation, 0, 0));

	// calculate delta for this frame from the rate information
	AddControllerPitchInput(-Rotation  * (2.f / 5));
}

void ATank_C::MoveTank(float Value)
{
	if (!Tank) { return; }
	float Distance = GetWorld()->DeltaTimeSeconds * Value * MovementSpeed;
	Tank->AddRelativeLocation(Tank->GetForwardVector() * Distance);
	CameraBoom->AddRelativeLocation(Tank->GetForwardVector() * Distance);
}

void ATank_C::RotateTank(float Value)
{
	if (!Tank) { return; }
	float Rotation = GetWorld()->DeltaTimeSeconds * Value * RotationSpeed;
	Tank->AddRelativeRotation(FRotator(0, Rotation, 0));
	Turret->AddRelativeRotation(FRotator(0, -Rotation, 0));
}
