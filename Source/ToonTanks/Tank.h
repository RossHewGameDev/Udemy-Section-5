// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputAction.h"
#include "Tank.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

protected:
	virtual void BeginPlay() override;

	void InitializeInputMappings();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Movement(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivate));
	UInputMappingContext* TankMappingContext; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivate));
	UInputAction* MoveAction;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Setup", meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Setup", meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* Camera;
};
