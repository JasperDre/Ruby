#include "GamePCH.h"
#include "WildPokemonTile.h"

#include "Controllers/AStarPathFinder.h"
#include "Game/Game.h"
#include "Entities/Player.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

WildPokemonTile::WildPokemonTile(TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Entity(aGameCore, aMesh, aTexture)
	, m_PathingComplete(false)
{
	for (int& i : m_MyInputSet)
		i = -1;

	myDirection = SpriteDirection::SpriteWalkDown;
	myNewDirection = SpriteDirection::SpriteWalkDown;
	m_MyTileMap = aTileMap;

	m_IsFirstInput = true;

	m_MyState = AI_States::PathingState;

	m_CurrentInput = 0;

	myMinIndex = 0;
	myMaxIndex = 0;

	m_MyPath = &m_MyInputSet[0];

	m_MyNewDestination = Vector2Int(0, 0);

	myPathFinder = new AStarPathFinder(m_MyTileMap, this);

	m_MyIndex = Vector2Int(static_cast<int>(myPosition.myX / TILESIZE), static_cast<int>(myPosition.myY / TILESIZE));
}

WildPokemonTile::~WildPokemonTile()
{
	delete myPathFinder;
}

void WildPokemonTile::Update(float deltatime)
{
	switch (m_MyState)
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
	const int TargetTile = GetNextTileFromSet(m_CurrentInput);

	const Vector2Int aNPCIndex = GetMyIndex();

	if (m_IsFirstInput == true)
	{
		myNewDirection = CalculateNextInput(aNPCIndex);
		m_IsFirstInput = false;
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
		m_IsFirstInput = true;
		SetMyState(AI_States::PathingState);
	}

	const Vector2Float PlayerPos = myGameCore->GetMyPlayer()->GetPosition();

	const Vector2Int aPlayerColumnRow = Vector2Int(static_cast<int>(PlayerPos.myX / TILESIZE), static_cast<int>(PlayerPos.myY / TILESIZE));

	const Vector2Int MinRange = m_MyTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int MaxRange = m_MyTileMap->GetColumRowFromIndex(myMaxIndex);

	if (aPlayerColumnRow.x > MinRange.x && aPlayerColumnRow.x < MaxRange.x && aPlayerColumnRow.y > MinRange.y && aPlayerColumnRow.y < MaxRange.y)
		SetMyState(AI_States::TrackToPlayerState);
}

void WildPokemonTile::TrackToPlayerUpdate(float deltatime)
{
}

void WildPokemonTile::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myMesh->DebugDraw(myPosition, 0, TILESIZE, camPos, projecScale);
}

void WildPokemonTile::Move(SpriteDirection dir, float deltatime)
{
	NewPosition = myPosition;

	if (myDirection != dir)
		myDirection = dir;

	const Vector2Float velocity = DIRECTIONVECTOR[static_cast<int>(dir)] * NPC_SPEED;

	NewPosition += velocity * deltatime;

	if (CheckForCollision(NewPosition))
	{
		SetPosition(NewPosition);
	}
	else
	{
		m_MyState = AI_States::PathingState;
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

	m_PathingComplete = false;

	const Vector2Int aMin = m_MyTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int aMax = m_MyTileMap->GetColumRowFromIndex(myMaxIndex);

	m_MyNewDestination.x = MathUtility::GetRandomRangeInteger(aMin.x, aMax.x);
	m_MyNewDestination.y = MathUtility::GetRandomRangeInteger(aMin.y, aMax.y);

	while (!m_PathingComplete)
	{
		m_PathingComplete = myPathFinder->FindPath(anIndex.x, anIndex.y, m_MyNewDestination.x, m_MyNewDestination.y);

		if (m_PathingComplete)
			myPathFinder->GetPath(m_MyPath, GetMaxPathSize(), m_MyNewDestination.x, m_MyNewDestination.y);

		if (!m_MyPath)
			m_PathingComplete = false;

		if (m_PathingComplete == false)
		{
			m_MyNewDestination.x = MathUtility::GetRandomRangeInteger(aMin.x, aMax.x);
			m_MyNewDestination.y = MathUtility::GetRandomRangeInteger(aMin.y, aMax.y);
		}
	}

	SetCurrentInput(0);
	NPCSeekStartPath();

	return m_PathingComplete;
}

SpriteDirection WildPokemonTile::CalculateNextInput(Vector2Int anIndex)
{
	m_CurrentInput--;

	if (m_CurrentInput != -1)
	{
		const int NextTileIndex = GetNextTileFromSet(m_CurrentInput);

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
	return m_MyState;
}

void WildPokemonTile::SetMyState(AI_States aState)
{
	m_MyState = aState;
}

bool WildPokemonTile::GetNodeIsClearOnSpecial(int tx, int ty) const
{
	const Vector2Int MinColumnRow = m_MyTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int MaxColumnRow = m_MyTileMap->GetColumRowFromIndex(myMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
	{
		const int CheckTileIndex = m_MyTileMap->GetIndexFromColumnRow(tx, ty);
		if (m_MyTileMap->GetTileAtIndex(CheckTileIndex).MyForestType == Forest_Wild_Grass_)
			return true;
	}

	return false;
}

bool WildPokemonTile::CheckForCollision(Vector2Float NPCNewPosition) const
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	const Vector2Int OriginIndex = Vector2Int(static_cast<int>(NPCNewPosition.myX / TILESIZE), static_cast<int>((NPCNewPosition.myY - 0.3f) / TILESIZE));
	const Vector2Int TopLeftIndex = Vector2Int(static_cast<int>(NPCNewPosition.myX / TILESIZE), static_cast<int>(((NPCNewPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const Vector2Int TopRightIndex = Vector2Int(static_cast<int>((NPCNewPosition.myX + (TILESIZE / 2)) / TILESIZE), static_cast<int>(((NPCNewPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const Vector2Int BottomRightIndex = Vector2Int(static_cast<int>((NPCNewPosition.myX + (TILESIZE / 2)) / TILESIZE), static_cast<int>((NPCNewPosition.myY - 0.3f) / TILESIZE));

	//Check each index for whether the tile it lands on is walkable
	const bool CheckOrigin = myGameCore->GetTileMap()->GetTileAtNPC(OriginIndex);
	const bool CheckTopLeft = myGameCore->GetTileMap()->GetTileAtNPC(TopLeftIndex);
	const bool CheckTopRight = myGameCore->GetTileMap()->GetTileAtNPC(TopRightIndex);
	const bool CheckBottomRight = myGameCore->GetTileMap()->GetTileAtNPC(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	const bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}

int* WildPokemonTile::GetInputSet() const
{
	return m_MyPath;
}

void WildPokemonTile::SetInputSet(int* aPath)
{
	m_MyPath = aPath;
}

int WildPokemonTile::GetCurrentInput() const
{
	return m_CurrentInput;
}

void WildPokemonTile::SetCurrentInput(int aCurrentInput)
{
	m_CurrentInput = aCurrentInput;
}

int WildPokemonTile::GetNextTileFromSet(int aCurrentInput) const
{
	return m_MyInputSet[aCurrentInput];
}

void WildPokemonTile::ResetInputSet()
{
	for (int i = 0; i < MAXPATHSIZE_TOWN_NPC; i++)
		m_MyInputSet[i] = -1;

	m_CurrentInput = 0;
}

void WildPokemonTile::NPCSeekStartPath()
{
	while (m_MyInputSet[m_CurrentInput] != -1)
		m_CurrentInput++;

	m_CurrentInput--;
}

Vector2Int WildPokemonTile::GetMyMinIndex() const
{
	return Vector2Int(m_MyTileMap->GetColumRowFromIndex(myMinIndex));
}

Vector2Int WildPokemonTile::GetMyMaxIndex() const
{
	return Vector2Int(m_MyTileMap->GetColumRowFromIndex(myMaxIndex));
}

int WildPokemonTile::GetMyMapWidth() const
{
	return m_MyTileMap->GetMapWidth();
}

int WildPokemonTile::GetMaxPathSize() const
{
	return MAXPATHSIZE_TOWN_NPC;
}

void WildPokemonTile::SetMyDirection(SpriteDirection aDirection)
{
	myNewDirection = aDirection;
}