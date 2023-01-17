// Fill out your copyright notice in the Description page of Project Settings.


#include "World/UHexGrid.h"
#include "World/AHexTile.h"

// Sets default values for this component's properties
UHexGrid::UHexGrid()
{
}

void UHexGrid::SetExtent(int32 X, int32 Y)
{
	this->Width = X;
	this->Height = Y;
	Grid.SetNumZeroed(Width * Height);
	for (int32 x = 0; x < Width; x++)
	{
		Grid[x].SetNumZeroed(Height);
	}
}

TArray<AAHexTile*>& UHexGrid::operator[](int32 Index)
{
	if (Index < 0 || Index >= Width)
	{
		UE_LOG(LogTemp, Error, TEXT("Index out of bounds"));
	}
	return Grid[Index];
}

