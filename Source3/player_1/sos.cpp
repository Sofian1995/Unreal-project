
#include "sos.h"

// Sets default values
Asos::Asos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Asos::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void Asos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
} 

void Asos::MovePlatform(float DeltaTime)

{
   if (ShouldPlatformReturn())
   {
	  FVector MoveDirection = PlatformVelocity.GetSafeNormal();
	  StartLocation = StartLocation + MoveDirection * MoveDistance;
	  SetActorLocation(StartLocation);
	  PlatformVelocity = -PlatformVelocity;
   } 
   else  
   {
   FVector CurrentLocation = GetActorLocation();
   CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
   SetActorLocation(CurrentLocation);
   }
}

void Asos::RotatePlatform(float DeltaTime)
{
 
  AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool Asos::ShouldPlatformReturn() const

{
return GetDistanceMove() > MoveDistance;

}

float Asos::GetDistanceMove() const

{
 return  FVector::Dist(StartLocation, GetActorLocation());

}