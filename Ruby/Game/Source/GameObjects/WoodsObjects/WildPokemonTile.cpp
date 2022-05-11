#include "GamePCH.h"
#include "WildPokemonTile.h"

#include "Controllers/AStarPathFinder.h"
#include "Game/Game.h"
#include "GameObjects/Trainer.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

WildPokemonTile::WildPokemonTile(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
	, m_PathingComplete(false)
{
	myDirection = SpriteDirection::SpriteWalkDown;
	myNewDirection = SpriteDirection::SpriteWalkDown;
	myResourceManager = aResourceManager;
	m_MyTileMap = aTileMap;

	m_IsFirstInput = true;

	m_MyState = AI_States::PathingState;

	m_CurrentInput = 0;

	m_MyMinIndex = 0;
	m_MyMaxIndex = 0;

	m_MyPath = &m_MyInputSet[0];

	m_MyNewDestination = ivec2(0, 0);

	for (int& i : m_MyInputSet)
		i = -1;

	m_MyPathFinder = new AStarPathFinder(m_MyTileMap, this);

	m_MyIndex = ivec2(m_Position.myX / TILESIZE, m_Position.myY / TILESIZE);
}

WildPokemonTile::~WildPokemonTile()
{
	delete m_MyPathFinder;
	m_MyPathFinder = nullptr;
	myResourceManager = nullptr;
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

	const ivec2 aNPCIndex = GetMyIndex();

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

	const Vector2Float PlayerPos = m_pGame->GetMyPlayer()->GetPosition();

	const ivec2 aPlayerColumnRow = ivec2(PlayerPos.myX / TILESIZE, PlayerPos.myY / TILESIZE);

	const ivec2 MinRange = m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex);
	const ivec2 MaxRange = m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex);

	if (aPlayerColumnRow.x > MinRange.x && aPlayerColumnRow.x < MaxRange.x && aPlayerColumnRow.y > MinRange.y && aPlayerColumnRow.y < MaxRange.y)
		SetMyState(AI_States::TrackToPlayerState);
}

void WildPokemonTile::TrackToPlayerUpdate(float deltatime)
{
}

void WildPokemonTile::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	m_pMesh->DebugDraw(m_Position, 0, TILESIZE, camPos, projecScale);
}

void WildPokemonTile::Move(SpriteDirection dir, float deltatime)
{
	NewPosition = m_Position;

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

void WildPokemonTile::ResetPathFinder()
{
	m_MyPathFinder->Reset();
}

bool WildPokemonTile::GetNextPath(ivec2 anIndex)
{
	ResetInputSet();

	ResetPathFinder();

	m_PathingComplete = false;

	const ivec2 aMin = m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex);
	const ivec2 aMax = m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex);

	m_MyNewDestination.x = RangeRandomIntAlg(aMin.x, aMax.x);
	m_MyNewDestination.y = RangeRandomIntAlg(aMin.y, aMax.y);

	while (!m_PathingComplete)
	{
		m_PathingComplete = m_MyPathFinder->FindPath(anIndex.x, anIndex.y, m_MyNewDestination.x, m_MyNewDestination.y);

		if (m_PathingComplete)
			m_MyPathFinder->GetPath(m_MyPath, GetMaxPathSize(), m_MyNewDestination.x, m_MyNewDestination.y);

		if (!m_MyPath)
			m_PathingComplete = false;

		if (m_PathingComplete == false)
		{
			m_MyNewDestination.x = RangeRandomIntAlg(aMin.x, aMax.x);
			m_MyNewDestination.y = RangeRandomIntAlg(aMin.y, aMax.y);
		}
	}

	SetCurrentInput(0);
	NPCSeekStartPath();

	return m_PathingComplete;
}

SpriteDirection WildPokemonTile::CalculateNextInput(ivec2 anIndex)
{
	m_CurrentInput--;

	if (m_CurrentInput != -1)
	{
		const int NextTileIndex = GetNextTileFromSet(m_CurrentInput);

		const ivec2 m_NextTileColumnRow = ivec2(NextTileIndex % GetMyMapWidth(), NextTileIndex / GetMyMapWidth());

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

AI_States WildPokemonTile::GetMyState()
{
	return m_MyState;
}

void WildPokemonTile::SetMyState(AI_States aState)
{
	m_MyState = aState;
}

bool WildPokemonTile::GetNodeIsClearOnSpecial(int tx, int ty)
{
	const ivec2 MinColumnRow = m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex);
	const ivec2 MaxColumnRow = m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
	{
		const int CheckTileIndex = m_MyTileMap->GetIndexFromColumnRow(tx, ty);
		if (m_MyTileMap->GetTileAtIndex(CheckTileIndex).MyForestType == Forest_Wild_Grass_)
			return true;
	}

	return false;
}

void WildPokemonTile::OnEvent(Event* anEvent)
{

}

bool WildPokemonTile::CheckForCollision(Vector2Float NPCNewPosition) const
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	const ivec2 OriginIndex = ivec2((NPCNewPosition.myX / TILESIZE), ((NPCNewPosition.myY - 0.3f) / TILESIZE));
	const ivec2 TopLeftIndex = ivec2((NPCNewPosition.myX / TILESIZE), (((NPCNewPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const ivec2 TopRightIndex = ivec2(((NPCNewPosition.myX + (TILESIZE / 2)) / TILESIZE), (((NPCNewPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const ivec2 BottomRightIndex = ivec2(((NPCNewPosition.myX + (TILESIZE / 2)) / TILESIZE), ((NPCNewPosition.myY - 0.3f) / TILESIZE));

	//Check each index for whether the tile it lands on is walkable
	const bool CheckOrigin = m_pGame->GetTileMap()->GetTileAtNPC(OriginIndex);
	const bool CheckTopLeft = m_pGame->GetTileMap()->GetTileAtNPC(TopLeftIndex);
	const bool CheckTopRight = m_pGame->GetTileMap()->GetTileAtNPC(TopRightIndex);
	const bool CheckBottomRight = m_pGame->GetTileMap()->GetTileAtNPC(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	const bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}

int * WildPokemonTile::GetInputSet()
{
	return m_MyPath;
}

void WildPokemonTile::SetInputSet(int* aPath)
{
	m_MyPath = aPath;
}

int WildPokemonTile::GetCurrentInput()
{
	return m_CurrentInput;
}

void WildPokemonTile::SetCurrentInput(int aCurrentInput)
{
	m_CurrentInput = aCurrentInput;
}

int WildPokemonTile::GetNextTileFromSet(int aCurrentInput)
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

ivec2 WildPokemonTile::GetMyMinIndex()
{
	return ivec2(m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex));
}

ivec2 WildPokemonTile::GetMyMaxIndex()
{
	return ivec2(m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex));
}

int WildPokemonTile::GetMyMapWidth()
{
	return m_MyTileMap->GetMapWidth();
}

int WildPokemonTile::GetMaxPathSize()
{
	return MAXPATHSIZE_TOWN_NPC;
}

void WildPokemonTile::SetMyDirection(SpriteDirection aDirection)
{
	myNewDirection = aDirection;
}

int WildPokemonTile::RangeRandomIntAlg(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
