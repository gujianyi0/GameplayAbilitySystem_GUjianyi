// Copyright Gujianyi


#include "AutraCharacterBase.h"

// Sets default values
AAutraCharacterBase::AAutraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAutraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAutraCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAutraCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

