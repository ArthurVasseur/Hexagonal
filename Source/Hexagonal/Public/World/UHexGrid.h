// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UHexGrid.generated.h"

class AAHexTile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEXAGONAL_API UHexGrid final : public UActorComponent
{
	GENERATED_BODY()
private:
	TArray<TArray<AAHexTile*>> Grid;
	int32 Width = 0;
	int32 Height = 0;
public:
	// Sets default values for this component's properties
	UHexGrid();
	void SetExtent(int32 Width, int32 Height);

	TArray<AAHexTile*> &operator[](int32 Index);
};
