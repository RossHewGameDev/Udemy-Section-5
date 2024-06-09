// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h" 

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (bInFireRange())
    {
         RotateTurret(Tank->GetActorLocation());
    }
    else
    {
        // Idle
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true); // Check every FireRate seconds
}

void ATower::CheckFireCondition()
{
    if (bInFireRange())
    {
        Fire();
    }
}

bool ATower::bInFireRange()
{
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    if (Tank)
    {
        if (Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}