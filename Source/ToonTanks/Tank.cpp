// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFrameWork/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    InitializeInputMappings();
    TankPlayerController = Cast<APlayerController>(GetController());

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, 
        false,
        HitResult
        );
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25, 12, FColor::Red, false, 0.0f);

        RotateTurret(HitResult.ImpactPoint);
    }

}

void ATank::InitializeInputMappings()
{
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(TankMappingContext, 0);
        }
    }
}

void ATank::Movement(const FInputActionValue& Value)
{
    const FVector CurrentValue = Value.Get<FVector>();
    if (CurrentValue.Length() > 0.0f)    
    {
        FVector DeltaLocation = CurrentValue;
        DeltaLocation = CurrentValue * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
        AddActorLocalOffset(DeltaLocation, true);
    }
}

void ATank::Rotation(const FInputActionValue& Value)
{
    const FVector CurrentValue = Value.Get<FVector>();

    if (CurrentValue.Length() > 0.0f)
    {
        FRotator DeltaRotation = FRotator(0.0f, CurrentValue.X, 0.0f);
        DeltaRotation = DeltaRotation * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
        AddActorLocalRotation(DeltaRotation, true);
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Movement);
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::Rotation);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::Fire);
    }

}