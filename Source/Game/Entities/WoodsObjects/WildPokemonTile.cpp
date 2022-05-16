#include "GamePCH.h"
#include "WildPokemonTile.h"

#include "Controllers/AStarPathFinder.h"
#include "Game/Game.h"
#include "Entities/Player.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

WildPokemonTile::WildPokemonTile(TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Entity(aGameCore, aMesh, aTexture)
	, myPathingComplete(false)
{
	for (int& i : myInputSet)
		i = -1;

	myDirection = SpriteDirection::SpriteWalkDown;
	myNewDirection = SpriteDirection::SpriteWalkDown;
	myTileMap = aTileMap;

	myIsFirstInput = true;

	myState = AI_States::PathingState;

	myCurrentInput = 0;

	myMinIndex = 0;
	myMaxIndex = 0;

	myPath = &myInputSet[0];

	myNewDestination = Vector2Int(0, 0);

	myPathFinder = new AStarPathFinder(myTileMap, this);

	myIndex = Vector2Int(static_cast<int>(myPosition.myX / TILESIZE), static_cast<int>(myPosition.myY / TILESIZE));
}

WildPokemonTile::~WildPokemonTile()
{
	delete myPathFinder;
}

void WildPokemonTile::Update(float deltatime)
{
	switch (myState)
	{
		case AI_States::PathingState:
			PathingUpdate(deltatime);
			break;
		case AI_States::WalkingState:
			WalkingUpdate(deltatime);
			break;
		case AI_States::TrackToPlayerState:
			TrackToPlayerUpdate(deltatime);
			break;
		case AI_States::IdleState:
			break;
	}
}

void WildPokemonTile::PathingUpdate(float delatime)
{
	if (GetNextPath(GetMyIndex()))
		SetMyState(AI_States::WalkingState);
}

void WildPokemonTile::WalkingUpdate(float deltatime)
{
	const int TargetTile = GetNextTileFromSet(myCurrentInput);

	const Vector2Int aNPCIndex = GetMyIndex();

	if (myIsFirstInput == true)
	{
		myNewDirection = CalculateNextInput(aNPCIndex);
		myIsFirstInput = false;
	}
	else if (TargetTile == ((GetMyMapWidth() * aNPCIndex.y) + aNPCIndex.x))
	{
		myNewDirection = CalculateNextInput(aNPCIndex);
	}

	if (myNewDirection != SpriteDirection::SpriteDirectionStop)
	{
		Move(myNewDirection, deltatime);
		SetMyDirection(myNewDirection);
	}
	else
	{
		myIsFirstInput = true;
		SetMyState(AI_States::PathingState);
	}

	const Vector2Float PlayerPos = myGameCore->GetMyPlayer()->GetPosition();

	const Vector2Int aPlayerColumnRow = Vector2Int(static_cast<int>(PlayerPos.myX / TILESIZE), static_cast<int>(PlayerPos.myY / TILESIZE));

	const Vector2Int MinRange = myTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int MaxRange = myTileMap->GetColumRowFromIndex(myMaxIndex);

	if (aPlayerColumnRow.x > MinRange.x && aPlayerColumnRow.x < MaxRange.x && aPlayerColumnRow.y > MinRange.y && aPlayerColumnRow.y < MaxRange.y)
		SetMyState(AI_States::TrackToPlayerState);
}

void WildPokemonTile::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myMesh->DebugDraw(myPosition, 0, TILESIZE, camPos, projecScale);
}

void WildPokemonTile::Move(SpriteDirection dir, float deltatime)
{
	myNewPosition = myPosition;

	if (myDirection != dir)
		myDirection = dir;

	const Vector2Float velocity = DIRECTIONVECTOR[static_cast<int>(dir)] * NPC_SPEED;

	myNewPosition += velocity * deltatime;

	if (IsColliding(myNewPosition))
	{
		SetPosition(myNewPosition);
	}
	else
	{
		myState = AI_States::PathingState;
	}
}

void WildPokemonTile::ResetPathFinder() const
{
	myPathFinder->Reset();
}

bool WildPokemonTile::GetNextPath(Vector2Int anIndex)
{
	ResetInputSet();

	ResetPathFinder();

	myPathingComplete = false;

	const Vector2Int aMin = myTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int aMax = myTileMap->GetColumRowFromIndex(myMaxIndex);

	myNewDestination.x = MathUtility::GetRandomRangeInteger(aMin.x, aMax.x);
	myNewDestination.y = MathUtility::GetRandomRangeInteger(aMin.y, aMax.y);

	while (!myPathingComplete)
	{
		myPathingComplete = myPathFinder->FindPath(anIndex.x, anIndex.y, myNewDestination.x, myNewDestination.y);

		if (myPathingComplete)
			myPathFinder->GetPath(myPath, GetMaxPathSize(), myNewDestination.x, myNewDestination.y);

		if (!myPath)
			myPathingComplete = false;

		if (myPathingComplete == false)
		{
			myNewDestination.x = MathUtility::GetRandomRangeInteger(aMin.x, aMax.x);
			myNewDestination.y = MathUtility::GetRandomRangeInteger(aMin.y, aMax.y);
		}
	}

	SetCurrentInput(0);
	NPCSeekStartPath();

	return myPathingComplete;
}

SpriteDirection WildPokemonTile::CalculateNextInput(Vector2Int anIndex)
{
	myCurrentInput--;

	if (myCurrentInput != -1)
	{
		const int NextTileIndex = GetNextTileFromSet(myCurrentInput);

		const Vector2Int m_NextTileColumnRow = Vector2Int(NextTileIndex % GetMyMapWidth(), NextTileIndex / GetMyMapWidth());

		if (m_NextTileColumnRow.x != anIndex.x)
		{
			if (m_NextTileColumnRow.x > anIndex.x)
				return SpriteDirection::SpriteWalkRight;

			if (m_NextTileColumnRow.x < anIndex.x)
				return SpriteDirection::SpriteWalkLeft;
		}
		else if (m_NextTileColumnRow.y != anIndex.y)
		{
			if (m_NextTileColumnRow.y > anIndex.y)
				return SpriteDirection::SpriteWalkUp;

			if (m_NextTileColumnRow.y < anIndex.y)
				return SpriteDirection::SpriteWalkDown;
		}
	}
	else
	{
		return SpriteDirection::SpriteDirectionStop;
	}

	return SpriteDirection::SpriteDirectionStop;
}

AI_States WildPokemonTile::GetMyState() const
{
	return myState;
}

void WildPokemonTile::SetMyState(AI_States aState)
{
	myState = aState;
}

bool WildPokemonTile::IsNodeClearOnSpecial(int tx, int ty) const
{
	const Vector2Int MinColumnRow = myTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int MaxColumnRow = myTileMap->GetColumRowFromIndex(myMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
	{
		const int CheckTileIndex = myTileMap->GetIndexFromColumnRow(tx, ty);
		if (myTileMap->GetTileAtIndex(CheckTileIndex).myForestType == Forest_Wild_Grass_)
			return true;
	}

	return false;
}

bool WildPokemonTile::IsColliding(Vector2Float NPCNewPosition) const
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	const Vector2Int OriginIndex = Vector2Int(static_cast<int>(NPCNewPosition.myX / TILESIZE), static_cast<int>((NPCNewPosition.myY - 0.3f) / TILESIZE));
	const Vector2Int TopLeftIndex = Vector2Int(static_cast<int>(NPCNewPosition.myX / TILESIZE), static_cast<int>(((NPCNewPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const Vector2Int TopRightIndex = Vector2Int(static_cast<int>((NPCNewPosition.myX + (TILESIZE / 2)) / TILESIZE), static_cast<int>(((NPCNewPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const Vector2Int BottomRightIndex = Vector2Int(static_cast<int>((NPCNewPosition.myX + (TILESIZE / 2)) / TILESIZE), static_cast<int>((NPCNewPosition.myY - 0.3f) / TILESIZE));

	//Check each index for whether the tile it lands on is walkable
	const bool CheckOrigin = myGameCore->GetTileMap()->IsTileAtNPC(OriginIndex);
	const bool CheckTopLeft = myGameCore->GetTileMap()->IsTileAtNPC(TopLeftIndex);
	const bool CheckTopRight = myGameCore->GetTileMap()->IsTileAtNPC(TopRightIndex);
	const bool CheckBottomRight = myGameCore->GetTileMap()->IsTileAtNPC(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	const bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}

int* WildPokemonTile::GetInputSet() const
{
	return myPath;
}

void WildPokemonTile::SetInputSet(int* aPath)
{
	myPath = aPath;
}

int WildPokemonTile::GetCurrentInput() const
{
	return myCurrentInput;
}

void WildPokemonTile::SetCurrentInput(int aCurrentInput)
{
	myCurrentInput = aCurrentInput;
}

int WildPokemonTile::GetNextTileFromSet(int aCurrentInput) const
{
	return myInputSet[aCurrentInput];
}

void WildPokemonTile::ResetInputSet()
{
	for (int i = 0; i < MAXPATHSIZE_TOWN_NPC; i++)
		myInputSet[i] = -1;

	myCurrentInput = 0;
}

void WildPokemonTile::NPCSeekStartPath()
{
	while (myInputSet[myCurrentInput] != -1)
		myCurrentInput++;

	myCurrentInput--;
}

Vector2Int WildPokemonTile::GetMyMinIndex() const
{
	return Vector2Int(myTileMap->GetColumRowFromIndex(myMinIndex));
}

Vector2Int WildPokemonTile::GetMyMaxIndex() const
{
	return Vector2Int(myTileMap->GetColumRowFromIndex(myMaxIndex));
}

int WildPokemonTile::GetMyMapWidth() const
{
	return myTileMap->GetMapWidth();
}

int WildPokemonTile::GetMaxPathSize() const
{
	return MAXPATHSIZE_TOWN_NPC;
}

void WildPokemonTile::SetMyDirection(SpriteDirection aDirection)
{
	myNewDirection = aDirection;
}