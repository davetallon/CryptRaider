// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

	//The above funnctions are called on BP_Player Blueprint

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400;



	void PrintDamage(const float& Damage);
	// using const and & here means that it is a read-only reference (const not mandatory)

	bool HasDamage(float& OutDamage);


	UPROPERTY(EditAnywhere)
	float grabRadius = 100;


};
