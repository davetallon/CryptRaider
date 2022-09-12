// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///////////////////////   Moving an actor at constant speed /////////////////
	if(ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + MoveOffset;
		float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;
		FVector newLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(newLocation);
	} 
	////////////////////////////////////////////////////////////////////////////








///////////////////////////// POINTERS TIPS & INFO ///////////////////////////////////////////////////
	float myFloat = 5;
	//A star after the filetype tells the compiler that it is a pointer (The address in meomory)
	float* yourFloat = &myFloat;
	/*
	This will not work, because all that exists inside yourFloat is an address.
	UE_LOG(LogTemp, Display, TEXT("Your float value: %f"), yourFloat);
	A star before the value is the de-referencing operator. It will give us the actual value.
	*/
	UE_LOG(LogTemp, Display, TEXT("Your float value 2: %f"), *yourFloat);



	AActor* Owner = GetOwner();
	UE_LOG(LogTemp, Display, TEXT("The memory address is: %u"), Owner); 
	/*
	FString name = (*Owner).GetActorNameOrLabel();
	The arrow operator IS BEST to de-reference the address.
	*/
	FString ownerName = Owner->GetActorNameOrLabel();
	UE_LOG(LogTemp, Display, TEXT("Move owner name is: %s"), *ownerName);



	FVector ownerLocation = Owner->GetActorLocation();
	FString ownerLocationString = ownerLocation.ToCompactString();
	UE_LOG(LogTemp, Display, TEXT("Mover name is: %s and its location is: %s"),*ownerName, *ownerLocationString);
/////////////////////////////////////////////////////////////////////////////////////////////////////////

}

