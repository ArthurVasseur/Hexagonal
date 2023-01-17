// Fill out your copyright notice in the Description page of Project Settings.


#include "World/WorldGenerator.h"

#include "World/AHexTile.h"
#include "World/UHexGrid.h"
#include "FastNoiseWrapper.h"
#include "Math/NumericLimits.h"

// Sets default values
AWorldGenerator::AWorldGenerator() 
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Grid = CreateDefaultSubobject<UHexGrid>(TEXT("HexagonalGrid"));
	AddOwnedComponent(Grid);
	NoiseGenerator = CreateDefaultSubobject<UFastNoiseWrapper>(TEXT("NoiseGenerator"));
}

// Called when the game starts or when spawned
void AWorldGenerator::BeginPlay()
{
	Super::BeginPlay();
	int32 Seed = FMath::RandRange(0, TNumericLimits<int32>::Max() - 1);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(Seed));
	NoiseGenerator->SetupFastNoise(EFastNoise_NoiseType::Cellular, Seed);
	NoiseGenerator->SetDistanceFunction(EFastNoise_CellularDistanceFunction::Manhattan);
	NoiseGenerator->SetCellularJitter(1.f);
	NoiseGenerator->SetReturnType(EFastNoise_CellularReturnType::CellValue);
	NoiseGenerator->SetFrequency(0.015f);
	NoiseGenerator->SetOctaves(3);
	Grid->SetExtent(Width, Height);
	Sqrt3 = FMath::Sqrt(3.0f) * 100.0f;
	TileHorizontalOffset += Sqrt3;
	OddRowHorizontalOffset = Sqrt3 / 2.0f;
	TileVerticalOffset += 150.0f;
	for (int32 y = 0; y < Height; ++y)
	{
		for (int32 x = 0; x < Width; ++x)
		{
			const bool bOddRow = y % 2 == 1;
			const float XOffset = bOddRow ? (x * TileHorizontalOffset) + OddRowHorizontalOffset : x * TileHorizontalOffset;
			const float YOffset = y * TileVerticalOffset;
			
			TSubclassOf<AAHexTile> TileToSpawn = HexTileClass;
			const float Noise = NoiseGenerator->GetNoise2D(x * NoiseScale + 0.5f , y * NoiseScale + 0.5f);
			if (Noise <= -0.8f)
			{
				TileToSpawn = HexTileRiverClass;
			}
			else if (Noise <= 0.2f)
			{
				TileToSpawn = HexTilePlainClass;
			}
			else if (Noise <= 0.75f)
			{
				TileToSpawn = HexTileForestClass;
			}
			else if (Noise <= 1.f)
			{
				TileToSpawn = HexTileMountainClass;
			}
			else
			{
				TileToSpawn = HexTileClass;
			}
			if (Noise == 0.f)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(Noise));
			}
			auto* Tile = GetWorld()->SpawnActor<AAHexTile>(TileToSpawn, FVector(XOffset, YOffset, 0), FRotator::ZeroRotator);
			if (Tile == nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Tile is null"));
				continue;
			}
			Tile->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d_%f"), x, y, Noise));
			(*Grid)[y][x] = Tile;
		} 
	}
}