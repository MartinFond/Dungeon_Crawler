// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HexMapSystem/HexGrid.h"
#include "Components/StaticMeshComponent.h"
#include "Core/Characters/GameCharacter.h"
#include "Core/HexMapSystem/HexCell.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/DungeonPlayerController.h"

#include "Tests/AutomationEditorCommon.h"

float AHexGrid::GetSpacingX() const
{
	return SpacingX;
}

float AHexGrid::GetSpacingY() const
{
	return SpacingY;
}

// Sets default values
AHexGrid::AHexGrid()
{
	SetInitialized(false);
}

// Called when the game starts or when spawned
void AHexGrid::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	TArray<AActor*> WorldActors;
	UGameplayStatics::GetAllActorsOfClass(World, AHexGrid::StaticClass(), WorldActors);
	for (auto WorldActor : WorldActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor"));
		if (ADungeonPlayerController* PlayerController = Cast<ADungeonPlayerController>(WorldActor))
		{
			if (!PlayerController->HasActorBegunPlay())
			{
				PlayerController->DispatchBeginPlay();
			}
		}
		if (AHexCell* HexCell = Cast<AHexCell>(WorldActor))
		{
			HexCell->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			UE_LOG(LogTemp, Warning, TEXT("HexCell"));
		}
	}
	Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(World,0))->SetHexGrid(this);

	Initialize();
}

void AHexGrid::Initialize()
{
	if(GEngine)
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Initialize"));	
	//Reduce map size if needed
	if (HexMapArray.Num() > 0)
	{
		for (int xOverload = X; xOverload < HexMapArray.Num(); xOverload++)
		{
			for (int y = 0; y < HexMapArray[xOverload].Num(); y++)
			{
				HexMapArray[xOverload][y]->Destroy();
			}
		}
	
		for (int yOverload = Y; yOverload < HexMapArray[0].Num(); yOverload++)
		{
			for (int x = 0; x < HexMapArray.Num(); x++)
			{
				HexMapArray[x][yOverload]->Destroy();
			}
		}
	}
	
	//Set map size
	HexMapArray.SetNum(X);
	for (int index = 0; index < X; index++)
	{
		HexMapArray[index].SetNum(Y);
	}
	SetInitialized(true);
}


void AHexGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetInitialized(false);
}

void AHexGrid::StoreHexTile(AHexCell* HexTile)
{
	HexMapArray[HexTile->GetQ()][HexTile->GetR()+floor(HexTile->GetQ()/2)] = HexTile;
}

void AHexGrid::HideOverlayTiles()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto AttachedActor : AttachedActors)
	{
		if(AHexCell* HexCell = Cast<AHexCell>(AttachedActor))
		{
			HexCell->HideOverlayTile();
		}
	}
}

void AHexGrid::UnStoreHexTile(FIntPoint OffsetCoordinates)
{
	const FIntPoint AxialCoordinates = AHexCell::OffsetToAxial(OffsetCoordinates);
	HexMapArray[AxialCoordinates.X][AxialCoordinates.Y + floor(AxialCoordinates.X / 2)] = nullptr;
}

void AHexGrid::SpawnTile(const FIntPoint OffSetCoordinates, UWorld* World)
{
	int x = OffSetCoordinates.X;
	int y = OffSetCoordinates.Y;
	const FIntPoint Axial = AHexCell::OffsetToAxial(OffSetCoordinates);
	if (GetCell(Axial.X, Axial.Y) == nullptr)
	{
		FVector Location;

		if (x % 2 == 0)
		{
			Location.X = SpacingX * x;
			Location.Y = SpacingY * y;
			Location.Z = 0;
		}
		else
		{
			Location.X = SpacingX * x;
			Location.Y = SpacingY * y + Offset;
			Location.Z = 0;
		}

			
		FRotator Rotation;
		FActorSpawnParameters SpawnParameters;

		SpawnParameters.bAllowDuringConstructionScript = true;
			
		AHexCell* HexCell = (AHexCell*) World->SpawnActor<AHexCell>(HexCellType,Location, Rotation, SpawnParameters );
		HexCell->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		HexCell->SetOffsetCoordinates(OffSetCoordinates);
		HexCell->OnBuildMap();
		HexCell->SetParentHexGrid(this);
		StoreHexTile(HexCell);
	}
}

void AHexGrid::MoveXPositive()
{
	UWorld* World = GetWorld();
	FVector XMoveLength (XMoveValue * SpacingX, 0, 0);
	for (int Xindex = X - 1; Xindex > -1 - XMoveValue; Xindex--)
	{
		int NewIndex = Xindex + XMoveValue;
		
		//MoveTab
		for (int y = 0; y < Y; y++)
		{
			if (Xindex > -1)
			{
				AHexCell* HexCell = HexMapArray[Xindex][y];
				UnStoreHexTile(FIntPoint(Xindex, y));
				if (NewIndex < X)
				{
					FIntPoint NewOffsetCoordinates(NewIndex, y);
					HexCell->SetOffsetCoordinates(NewOffsetCoordinates);
					FVector YMoveLength;
					if (XMoveValue % 2 == 1)
					{
						if (NewIndex % 2 == 0)
						{
							YMoveLength = FVector(0, -Offset, 0);
						}
						else
						{
							YMoveLength = FVector(0, Offset, 0);
						}
					}

					FVector NewLocation = HexCell->GetActorLocation() + XMoveLength + YMoveLength;
					HexCell->SetActorLocation(NewLocation);
					StoreHexTile(HexCell);
				}
				else
				{
					HexCell->Destroy();
				}
			}
			else
			{
				FIntPoint NewOffsetPosition(NewIndex, y);
				SpawnTile(NewOffsetPosition, World);
			}
		}
	}
}

void AHexGrid::MoveXNegative()
{
	UWorld* World = GetWorld();
	FVector XMoveLength (XMoveValue * SpacingX, 0, 0);
	for (int Xindex = 0; Xindex < X -XMoveValue; Xindex++)
	{
		int NewIndex = Xindex + XMoveValue;
		
		//MoveTab
		for (int y = 0; y < Y; y++)
		{
			if (Xindex < X)
			{
				AHexCell* HexCell = HexMapArray[Xindex][y];
				UnStoreHexTile(FIntPoint(Xindex, y));
				if (NewIndex >= 0)
				{
					FIntPoint NewOffsetCoordinates(NewIndex, y);
					HexCell->SetOffsetCoordinates(NewOffsetCoordinates);
					FVector YMoveLength;
					if (XMoveValue & 1)
					{
						if (NewIndex % 2 == 0)
						{
							YMoveLength = FVector(0, -Offset, 0);
						}
						else
						{
							YMoveLength = FVector(0, Offset, 0);
						}
					}

					FVector NewLocation = HexCell->GetActorLocation() + XMoveLength + YMoveLength;
					HexCell->SetActorLocation(NewLocation);
					StoreHexTile(HexCell);
				}
				else
				{
					HexCell->Destroy();
				}
			}
			else
			{
				FIntPoint NewOffsetPosition(NewIndex, y);
				SpawnTile(NewOffsetPosition, World);
			}
		}
	}
}

void AHexGrid::MoveYPositive()
{
	UWorld* World = GetWorld();
	FVector YMoveLength (0, YMoveValue * SpacingY, 0);
	for (int Yindex = Y - 1; Yindex > -1 - YMoveValue; Yindex--)
	{
		int NewIndex = Yindex + YMoveValue;
		//MoveTab
		for (int x = 0; x < X; x++)
		{
			if (Yindex > -1)
			{
				AHexCell* HexCell = HexMapArray[x][Yindex];
				UnStoreHexTile(FIntPoint(x, Yindex));
				if (NewIndex < Y)
				{
					FIntPoint NewOffsetCoordinates(x, NewIndex);
					HexCell->SetOffsetCoordinates(NewOffsetCoordinates);

					FVector NewLocation = HexCell->GetActorLocation() + YMoveLength;
					HexCell->SetActorLocation(NewLocation);
					StoreHexTile(HexCell);
				}
				else
				{
					HexCell->Destroy();
				}
			}
			else
			{
				FIntPoint NewOffsetPosition(x, NewIndex);
				SpawnTile(NewOffsetPosition, World);
			}
		}
	}
}

void AHexGrid::MoveYNegative()
{
	UWorld* World = GetWorld();
	FVector YMoveLength (0, YMoveValue * SpacingY, 0);
	for (int Yindex = 0; Yindex < Y -YMoveValue; Yindex++)
	{
		int NewIndex = Yindex + YMoveValue;
		
		//MoveTab
		for (int x = 0; x < X; x++)
		{
			if (Yindex < Y)
			{
				AHexCell* HexCell = HexMapArray[x][Yindex];
				UnStoreHexTile(FIntPoint(x, Yindex));
				if (NewIndex >= 0)
				{
					FIntPoint NewOffsetCoordinates(x, NewIndex);
					HexCell->SetOffsetCoordinates(NewOffsetCoordinates);
					
					FVector NewLocation = HexCell->GetActorLocation() + YMoveLength;
					HexCell->SetActorLocation(NewLocation);
					StoreHexTile(HexCell);
				}
				else
				{
					HexCell->Destroy();
				}
			}
			else
			{
				FIntPoint NewOffsetPosition(x, NewIndex);
				SpawnTile(NewOffsetPosition, World);
			}
		}
	}
	
}

float AHexGrid::Lerp(float FirstCell, float LastCell, float Step) const
{
	return FirstCell + (LastCell - FirstCell) * Step;
}

FCoordinates AHexGrid::CubeLerp(AHexCell* FirstCell, AHexCell* LastCell, float Step) const
{
	FCoordinates Result;
	Result.First = Lerp(FirstCell->GetQ(), LastCell->GetQ(), Step);
	Result.Second = Lerp(FirstCell->GetR(), LastCell->GetR(), Step);
	return Result;
}

AHexCell* AHexGrid::CubeRound(FCoordinates floatCoordinates) const
{
	int Q = round(floatCoordinates.First);
	int R = round(floatCoordinates.Second);
	int S = round(-floatCoordinates.First - floatCoordinates.Second);

	int QDiff = abs(Q - floatCoordinates.First);
	int RDiff = abs(R - floatCoordinates.Second);
	int SDiff = abs(S + floatCoordinates.First + floatCoordinates.Second);

	if (QDiff > RDiff && QDiff > SDiff)
	{
		Q = -R-S;
	}
	else if (RDiff > SDiff)
	{
		R = -Q-S;
	}
	else
	{
		S = -Q-R;
	}
	return GetCell(Q, R);
}

void AHexGrid::MoveY()
{
	if (HexMapArray.Num() <= 0 || HexMapArray.Num() != X)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: X value has changed, please Rebuild Map or set back X"));	
		UE_LOG(LogTemp, Warning, TEXT("Warning: X value has changed, please Rebuild Map or set back X"));
		return;
	}
	if (HexMapArray[0].Num() <= 0 || HexMapArray[0].Num() != Y)
	{
		if(GEngine)GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Y value has changed, please Rebuild Map or set back Y"));	
		UE_LOG(LogTemp, Warning, TEXT("Warning: Y value has changed, please Rebuild Map or set back Y"));
		return;
	}
	if (YMoveValue == 0) return;
	if (YMoveValue > 0) MoveYPositive();
	if (YMoveValue < 0) MoveYNegative();
	
}

int AHexGrid::Distance(const AHexCell* HexCell1, const AHexCell* HexCell2) const
{
	return HexCell1->Distance(HexCell2);
}

AHexCell* AHexGrid::GetCell(int Tq, int Tr) const
{
	if (Tq >= HexMapArray.Num() || Tq < 0)
	{
		return nullptr;
	}
	int TrIndex = Tr+floor(Tq/2);
	if (TrIndex >= HexMapArray[Tq].Num() || TrIndex < 0)
	{
		return nullptr;
	}
	return HexMapArray[Tq][TrIndex];
}

TArray<AHexCell*> AHexGrid::GetCellNeighbors(const AHexCell* HexCell) const
{
	TArray<AHexCell*> Neighbors;
	if (HexCell == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null HexCell"));
		return Neighbors;
	}
	int Q = HexCell->GetQ();
	int R = HexCell->GetR();
	AHexCell* CurrentNeighbor;
	if ((CurrentNeighbor = GetCell(Q+1, R)) != nullptr)
	{
		Neighbors.Add(CurrentNeighbor);
	}
	if ((CurrentNeighbor = GetCell(Q+1, R-1)) != nullptr)
	{
		Neighbors.Add(CurrentNeighbor);
	}
	if ((CurrentNeighbor = GetCell(Q, R-1)) != nullptr)
	{
		Neighbors.Add(CurrentNeighbor);
	}
	if ((CurrentNeighbor = GetCell(Q-1, R)) != nullptr)
	{
		Neighbors.Add(CurrentNeighbor);
	}
	if ((CurrentNeighbor = GetCell(Q-1, R+1)) != nullptr)
	{
		Neighbors.Add(CurrentNeighbor);
	}
	if ((CurrentNeighbor = GetCell(Q, R+1)) != nullptr)
	{
		Neighbors.Add(CurrentNeighbor);
	}
	return Neighbors;
}

TArray<AHexCell*> AHexGrid::AStarPath( AHexCell* StartingCell, AHexCell* EndCell, const EMovementState MovementState) const
{
	TArray<AHexCell*> ResultPath;
	
	TArray<HexPriority> Frontier;
	Frontier.HeapPush(HexPriority(0, StartingCell), HexPriorityPredicate());
	TMap<AHexCell*,AHexCell*> CameFrom;
	TMap<AHexCell*, int> CostSoFar;
	CameFrom.Add(StartingCell, nullptr);
	CostSoFar.Add(StartingCell, 0);
	
	while (!Frontier.IsEmpty())
	{
		HexPriority CurrentPriority(0, nullptr);
		Frontier.HeapPop(CurrentPriority, HexPriorityPredicate());
		AHexCell* Current = CurrentPriority.HexCell;
	
		if(Current == EndCell)
		{
			break;
		}
	
		for (AHexCell* Next : GetCellNeighbors(Current))
		{
			int NewCost = *CostSoFar.Find(Current) + Next->GetMovementCost(MovementState);
			if ((Next->IsEmpty() || Next == EndCell) && !Next->IsObstacle() && (!CostSoFar.Find(Next) || NewCost < *CostSoFar.Find(Next)))
			{
				CostSoFar.Add(Next, NewCost);
				double Priority = NewCost + Distance(EndCell, Next);
				Frontier.HeapPush(HexPriority(Priority, Next), HexPriorityPredicate());
				CameFrom.Add(Next, Current);
			}
		}
	}
	if (CameFrom.IsEmpty())
	{
		return ResultPath;
	}
	AHexCell* Current = EndCell;
	do
	{
		ResultPath.Insert(Current, 0);
		Current = *CameFrom.Find(Current);
	}
	while (ResultPath[0] != StartingCell);

	
	return ResultPath;
}

TArray<AHexCell*> AHexGrid::LinePath(AHexCell* StartingCell, AHexCell* EndCell) const
{
	float N = StartingCell->Distance(EndCell);
	TArray<AHexCell*> Result;

	for(int i = 0; i <= N; i++ )
	{
		Result.Add(CubeRound(CubeLerp(StartingCell, EndCell, 1/N * i)));
	}

	return Result;
}

bool AHexGrid::IsInitialized() const
{
	return bInitialized;
}

void AHexGrid::SetInitialized(bool bInitialized_)
{
	this->bInitialized = bInitialized_;
}

float AHexGrid::GetOffset() const
{
	return Offset;
}


void AHexGrid::BuildMap()
{
	Initialize();
	UWorld* World = GetWorld();

	//Add none existent tiles
	for (int x = 0; x < X; x++)
	{
		for (int y = 0; y < Y; y++)
		{
			FIntPoint OffSetCoordinates;
			OffSetCoordinates.X = x;
			OffSetCoordinates.Y = y;
			SpawnTile(OffSetCoordinates, World);
			
		}
	}
}

void AHexGrid::ClearMap()
{
	TArray<AActor*> Actors;
	GetAttachedActors(Actors);
	for (auto Actor : Actors)
	{
		if (Cast<AHexCell>(Actor))
		{
			Actor->Destroy();
		}
	}
	for (int i = 0; i <HexMapArray.Num(); i++)
	{
		HexMapArray[i].Reset(HexMapArray[i].Num());
	}
	SetInitialized(false);
}

void AHexGrid::MoveX()
{
	if (HexMapArray.Num() <= 0 || HexMapArray.Num() != X)
	{
		if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: X value has changed, please Rebuild Map or set back X"));	
		UE_LOG(LogTemp, Warning, TEXT("Warning: X value has changed, please Rebuild Map or set back X"));
		return;
	}
	if (HexMapArray[0].Num() <= 0 || HexMapArray[0].Num() != Y)
	{
		if(GEngine)GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Y value has changed, please Rebuild Map or set back Y"));	
		UE_LOG(LogTemp, Warning, TEXT("Warning: Y value has changed, please Rebuild Map or set back Y"));
		return;
	}
	if (XMoveValue == 0) return;
	if (XMoveValue > 0) MoveXPositive();
	if (XMoveValue < 0) MoveXNegative();
}



