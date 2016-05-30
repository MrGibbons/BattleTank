// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Tank_C.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BATTLETANK_API ATank_C : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATank_C();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* Turret = nullptr;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* Barrel = nullptr;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* Tank = nullptr;

	UPROPERTY(EditAnywhere)
		float RotationSpeed = 120;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 120;

	void RotateTurret(float Speed);
	void ElevateTurret(float Speed);
	void MoveTank(float Speed);
	void RotateTank(float Speed);
};
