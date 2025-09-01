// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CurrentX = 0;
	CurrentY = 0;
	TotalDistance = 0.0f;
	TotalEvents = 0;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	Move();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AMyActor::Step()
{
	return FMath::RandRange(0, 1);
}

bool AMyActor::TriggerEvent()
{
	return (FMath::RandRange(0, 1) == 1);
}

void AMyActor::Move()
{
	UE_LOG(LogTemp, Log, TEXT("Step 0 : (%d, %d)"), CurrentX, CurrentY);

	for (int32 i = 1; i <= 10; i++)
	{
		int32 PrevX = CurrentX;
		int32 PrevY = CurrentY;

		int32 StepX = Step();
		int32 StepY = Step();

		CurrentX += StepX;
		CurrentY += StepY;

		float DX = static_cast<float>(CurrentX - PrevX);
		float DY = static_cast<float>(CurrentY - PrevY);

		float Distance = FMath::Sqrt(FMath::Square(DX) + FMath::Square(DY));
		TotalDistance += Distance;

		bool bEvent = TriggerEvent();
		if (bEvent)
		{
			TotalEvents++;

			FVector NewWorldLocation = FVector(CurrentX * 100.0f, CurrentY * 100.0f, GetActorLocation().Z);
			SetActorLocation(NewWorldLocation);
		}

		UE_LOG(LogTemp, Log, TEXT("Step %d : (%d, %d), Distance = %.2f, Event = %s"),
			i, CurrentX, CurrentY, Distance, bEvent ? TEXT("Occurred") : TEXT("None"));
	}

	UE_LOG(LogTemp, Log, TEXT("Total Distance = %.2f"), TotalDistance);
	UE_LOG(LogTemp, Log, TEXT("Total Events = %d"), TotalEvents);
}