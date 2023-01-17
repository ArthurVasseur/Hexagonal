// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGenerator.generated.h"

class AAHexTile;
class UFastNoiseWrapper;
class UHexGrid;

UCLASS()
class HEXAGONAL_API AWorldGenerator final : public AActor
{
	GENERATED_BODY()

private:
	float Sqrt3 = FMath::Sqrt(3.0f) * 100;
	UFastNoiseWrapper* NoiseGenerator = nullptr;
	UHexGrid* Grid = nullptr;
protected:
	
	UPROPERTY(EditAnywhere, Category = "World Generation | General")
	int32 Width;

	UPROPERTY(EditAnywhere, Category = "World Generation | General")
	int32 Height;

	UPROPERTY(EditAnywhere, Category = "World Generation | General")
	float TileHorizontalOffset = Sqrt3;

	UPROPERTY(EditAnywhere, Category = "World Generation | General")
	float OddRowHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "World Generation | General")
	float TileVerticalOffset;

	UPROPERTY(EditAnywhere, Category = "World Generation | Tile")
	TSubclassOf<AAHexTile> HexTileClass;

	UPROPERTY(EditAnywhere, Category = "World Generation | Tile")
	TSubclassOf<AAHexTile> HexTileRiverClass;
	
	UPROPERTY(EditAnywhere, Category = "World Generation | Tile")
	TSubclassOf<AAHexTile> HexTilePlainClass;

	UPROPERTY(EditAnywhere, Category = "World Generation | Tile")
	TSubclassOf<AAHexTile> HexTileMountainClass;

	UPROPERTY(EditAnywhere, Category = "World Generation | Tile")
	TSubclassOf<AAHexTile> HexTileForestClass;

	UPROPERTY(EditAnywhere, Category = "World Generation | Biome Generation")
	float Multiplier;

	UPROPERTY(EditAnywhere, Category = "World Generation | Biome Generation")
	float NoiseScale;
public:	
	// Sets default values for this actor's properties
	AWorldGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
