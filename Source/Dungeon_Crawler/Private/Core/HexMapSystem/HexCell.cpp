// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HexMapSystem/HexCell.h"
#include "Core/HexMapSystem/HexGrid.h"
#include "Core/HexMapSystem/HexTile.h"
#include "Core/HexMapSystem/OverlayTile.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/DungeonPlayerController.h"

// Sets default values
AHexCell::AHexCell()
{	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	bPostInitialized = false;
	PrimaryActorTick.bCanEverTick = true;
	bAllowTickBeforeBeginPlay = false;
}

// Called when the game starts or when spawned
void AHexCell::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	TArray<AActor*> WorldActors;
	UGameplayStatics::GetAllActorsOfClass(World, AHexGrid::StaticClass(), WorldActors);
	for (auto WorldActor : WorldActors)
	{
		if (AHexGrid* WorldHexGrid = Cast<AHexGrid>(WorldActor))
		{
			if (!WorldHexGrid->HasActorBegunPlay())
			{
				WorldHexGrid->DispatchBeginPlay();
			}
		}
	}
	Initialize();
	FTransform OverlayTileTransform(FRotator::ZeroRotator, FVector::UpVector * 10);
	OverlayTile = Cast<UOverlayTile>(AddComponentByClass(OverlayTileType, false, OverlayTileTransform, false));
	HideOverlayTile();
}

void AHexCell::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Warning, TEXT("Constructing HexCell"));
	UWorld* World = GetWorld();
	TArray<AActor*> WorldActors;
	UGameplayStatics::GetAllActorsOfClass(World, AHexGrid::StaticClass(), WorldActors);
	for (auto WorldActor : WorldActors)
	{
		if (AHexGrid* WorldHexGrid = Cast<AHexGrid>(WorldActor))
		{
			ParentHexGrid = WorldHexGrid;
		}
	}
	if (ParentHexGrid != nullptr)
	{
		Initialize();
		ParentHexGrid->StoreHexTile(this);
	}
}

void AHexCell::Initialize()
{
	if (!ParentHexGrid->IsInitialized())
	{
		UE_LOG(LogTemp, Warning, TEXT("Initializing"));
		ParentHexGrid->Initialize();
	}
	int x = round((GetActorLocation().X - ParentHexGrid->GetActorLocation().X) / ParentHexGrid->GetSpacingX());
	int y;
	if (x % 2 == 0)
	{
		y = round((GetActorLocation().Y - ParentHexGrid->GetActorLocation().Y) / ParentHexGrid->GetSpacingY());
	}
	else
	{
		y = round(((GetActorLocation().Y - ParentHexGrid->GetActorLocation().Y) - ParentHexGrid->GetOffset()) / ParentHexGrid->GetSpacingY());
	}
	SetOffsetCoordinates(FIntPoint(x, y));
}

void AHexCell::CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent)
{
	HexTile->SetRenderCustomDepth(true);
	SetMouseOvered(true);
	const UWorld* World = GetWorld();
	Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(World,0))->SetOveredCell(this);
}

void AHexCell::CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent)
{	
	HexTile->SetRenderCustomDepth(false);
	SetMouseOvered(false);
	const UWorld* World = GetWorld();
	Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(World,0))->SetOveredCell(nullptr);
}

void AHexCell::ShowOverlayTile()
{
	OverlayTile->SetVisibility(true);
}

void AHexCell::HideOverlayTile()
{
	OverlayTile->SetVisibility(false);
}

void AHexCell::SetOverlayTileGreen()
{
	OverlayTile->SetGreen();
}

void AHexCell::SetOverlayTileRed()
{
	OverlayTile->SetRed();
}

// Called every frame
void AHexCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bPostInitialized)
	{
		ParentHexGrid->StoreHexTile(this);
		bPostInitialized =true;
	}
	PrimaryActorTick.bCanEverTick = false;
}

void AHexCell::OnBuildMap()
{
	HexTile = Cast<UHexTile>(AddComponentByClass(HexTileType, false, FTransform::Identity, false));
	this->AddInstanceComponent(HexTile);
	this->AddOwnedComponent(HexTile);
	HexTile->OnBeginCursorOver.AddDynamic(this, &AHexCell::CustomOnBeginMouseOver);
	HexTile->OnEndCursorOver.AddDynamic(this, &AHexCell::CustomOnEndMouseOver);
}

void AHexCell::SwitchTileType()
{
	HexTile->DestroyComponent();
	HexTile = Cast<UHexTile>(AddComponentByClass(HexTileType, false, FTransform::Identity, false));
	this->AddInstanceComponent(HexTile);
	this->AddOwnedComponent(HexTile);
}

void AHexCell::PrintAxialCoordinates()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("AxialCoordinates: Q:%d, R:%d"), AxialCoordinates.X, AxialCoordinates.Y));
}

void AHexCell::PrintOffSetCoordinates()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("OffsetCoordinate: X:%d, Y:%d"), OffsetCoordinates.X, OffsetCoordinates.Y));
}

FIntPoint AHexCell::GetOffsetCoordinates() const
{
	return OffsetCoordinates;
}

void AHexCell::SetOffsetCoordinates(const FIntPoint& OffsetCoordinates_)
{
	this->OffsetCoordinates = OffsetCoordinates_;
	SetAxialCoordinates(OffsetToAxial(OffsetCoordinates_));
}

FIntPoint AHexCell::GetAxialCoordinates() const
{
	return AxialCoordinates;
}

void AHexCell::SetAxialCoordinates(const FIntPoint& AxialCoordinates_)
{
	this->AxialCoordinates = AxialCoordinates_;
}

bool AHexCell::IsEmpty() const
{
	return OccupierCharacter == nullptr;
}


AHexGrid* AHexCell::GetParentHexGrid() const
{
	return ParentHexGrid;
}

void AHexCell::SetParentHexGrid(AHexGrid* ParentHexGrid_)
{
	this->ParentHexGrid = ParentHexGrid_;
}

bool AHexCell::IsObstacle() const
{
	return HexTile->GetHexTileType() == EHexTileType::Obstacle;
}


int AHexCell::GetQ() const
{
	return AxialCoordinates.X;
}


int AHexCell::GetR() const
{
	return AxialCoordinates.Y;
}

int AHexCell::GetS() const
{
	return -(GetQ() + GetR());
}

AGameCharacter* AHexCell::GetOccupierCharacter() const
{
	return OccupierCharacter;
}

void AHexCell::SetOccupierCharacter(AGameCharacter* OccupierCharacter_)
{
	this->OccupierCharacter = OccupierCharacter_;
}

void AHexCell::SetPostInitialized(bool bPostInitialized_)
{
	this->bPostInitialized = bPostInitialized_;
}

void AHexCell::SetMouseOvered(bool bMouseOvered_)
{
	this->bMouseOvered = bMouseOvered_;
}


FIntPoint AHexCell::OffsetToAxial(const FIntPoint OffsetCoordinates)
{
	int q = OffsetCoordinates.X;
	int r = OffsetCoordinates.Y - (OffsetCoordinates.X - (OffsetCoordinates.X & 1)) / 2 ;
	FIntPoint AxialCoordinates;
	AxialCoordinates.X = q;
	AxialCoordinates.Y = r;
	return AxialCoordinates;
}

TArray<AHexCell*> AHexCell::GetNeighbors()
{
	return ParentHexGrid->GetCellNeighbors(this);
}

double AHexCell::Distance(const AHexCell* HexCell) const
{
	return (abs(GetQ() -HexCell->GetQ()) + abs(GetR() - HexCell->GetR()) + abs(GetS() - HexCell->GetS())) /2;
}

int AHexCell::GetMovementCost(EMovementState MovementState) const
{
	return HexTile->GetMovementCost(MovementState);
}
