// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//(PhysicsHandle component was added to BP_Player) - This is to capture it in code.
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	//This is to prevent a UE crash in the case of grabbing something without a physics handle component.
	if(PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Got physics handle: %s"), *PhysicsHandle->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No physics handle was found."));
	}
}

///////////////////// Pointers Vs. References NOTES ////////////////////
/* 
Both store memory address'.
Only pointers can be re-assigned, references cannot.
Pointers CAN be null (nullptr) References cannot.
Declaring: ActorPtr* actorName = &Actorname    /   Actor& ActorRef = Actor
Accessing contents: *ActorPtr   /   ActorRef
Accessing address:  ActorPtr   /   &ActorRef    (& = address of)..(using a pointer variable will be default get pointer address).
Changing address: ActorPtr = &Actor    /   Not allowed
Changing value:  *ActorPtr = Actor    /  ActorRef = Actor
*/     ///// Loook at Udemy video-note in 'Refernce V Pointers' vid.





// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator Rotation = GetComponentRotation();
	FString RotationString = Rotation.ToCompactString();
	// UE_LOG(LogTemp, Display, TEXT("Grabber rotation is: %s"), *RotationString)

	float Time = GetWorld()->TimeSeconds;
	// UE_LOG(LogTemp, Display, TEXT("The time is: %f"), Time);
	
	






	////////////////////// REFERENCE INFO/EXAMPLE /////////////////////
	/*

	float Damage = 5;
	float& DamageRef = Damage;  //float& is a reference to a float, it does not allocate new memory
	DamageRef = 10;
	// UE_LOG(LogTemp, Display, TEXT("Damage: %f and DamageRef is: %f"), Damage, DamageRef); //using DamageRef just like a regular variable
	//notice from above uelog: the value has updated the source.
	//LESSON: REFERENCES is generally preferable as it is safer and doesnt need fancy syntax.

	*/
	

	float Damage;
	if(HasDamage(Damage))
	{
		PrintDamage(Damage);
	}
	
	///////////////////////////////////////////////////////////////////
}
	
bool UGrabber::HasDamage(float& OutDamage)
	{
		OutDamage = 5;
		return true;
	}


void UGrabber::Grab()
{
	//////////////////// DEBUG LINE ///////////////////////
	FVector start = GetComponentLocation();
	FVector end = start + (GetForwardVector() * MaxGrabDistance);
	DrawDebugLine(GetWorld(), start, end, FColor::Red);
	////////////////////////////////////////////////////////
	///////////////////// DEBUG SPHERE /////////////////////
	//See below inside if
	///////////////////////////////////////////////////////


	/////////////// SWEEP LINE //////////////////
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(grabRadius);

	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
	HitResult, 
	start, 
	end, 
	FQuat::Identity, 
	ECC_GameTraceChannel2, 
	Sphere
	);

	//'FQuat::Identity' was simply provided in videos. Apparently it is "mathematical speak" for No Rotation.
	// The channel was found in folder: config.defaultengine.ini and search for Grabber 


	if (HasHit)
	{
		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("You have hit: %s"), *HitActor->GetActorNameOrLabel());
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Blue, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Yellow, false, 5);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Actor hit."));
	}
	///////////////////////////////////////////////
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released!"));
}



void UGrabber::PrintDamage(const float& Damage)
{
	// UE_LOG(LogTemp, Display, TEXT("Damage is: %f"), Damage);
}
