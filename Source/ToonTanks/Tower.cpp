// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h" 

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Find distance to player
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        if (Distance <= FireRange)
        {
            RotateTurret(Tank->GetActorLocation());
        }
        else
        {
            // Idle
        }
    }



}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // Get the turret reference
}