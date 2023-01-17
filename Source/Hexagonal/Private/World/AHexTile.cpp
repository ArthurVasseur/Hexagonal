// Fill out your copyright notice in the Description page of Project Settings.


#include "World/AHexTile.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AAHexTile::AAHexTile()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAHexTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAHexTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

