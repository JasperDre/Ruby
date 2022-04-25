#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "WildPokemonTile.h"
#include "GameObjects/Trainer.h"

#include "Controllers/AStarPathFinder.h"

#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapWoods.h"
#include "Game/Game.h"

WildPokemonTile::WildPokemonTile(ResourceManager * aResourceManager, TileMap * aTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	myDirection = SpriteWalkDown;
	myNewDirection = SpriteWalkDown;
	myResourceManager = aResourceManager;
	m_MyTileMap = aTileMap;

	m_IsFirstInput = true;

	m_MyState = PathingState;

	m_CurrentInput = 0;

	m_MyMinIndex = 0;
	m_MyMaxIndex = 0;

	m_MyPath = &m_MyInputSet[0];

	m_MyNewDestination = ivec2(0, 0);


	for (int i = 0; i < MAXPATHSIZE_TOWN_NPC; i++)
	{
		m_MyInputSet[i] = -1;
	}

	m_MyPathFinder = new AStarPathFinder(m_MyTileMap, this);

	m_MyIndex = ivec2(m_Position.x / TILESIZE, m_Position.y / TILESIZE);

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
	case PathingState:
		PathingUpdate(deltatime);
		break;

	case WalkingState:
		WalkingUpdate(deltatime);
		break;
	case TrackToPlayerState:
		TrackToPlayerUpdate(deltatime);
		break;
	}
}

void WildPokemonTile::PathingUpdate(float delatime)
{
	if (GetNextPath(GetMyIndex()))
	{
		SetMyState(WalkingState);
	}
}

void WildPokemonTile::WalkingUpdate(float deltatime)
{
	int TargetTile = GetNextTileFromSet(m_CurrentInput);

	ivec2 aNPCIndex = GetMyIndex();


	if (m_IsFirstInput == true)
	{
		myNewDirection = CalculateNextInput(aNPCIndex);
		m_IsFirstInput = false;
	}
	else if (TargetTile == ((GetMyMapWidth() * aNPCIndex.y) + aNPCIndex.x))
	{
		myNewDirection = CalculateNextInput(aNPCIndex);
	}


	if (myNewDirection != SpriteDirectionStop)
	{
		Move(myNewDirection, deltatime);
		SetMyDirection(myNewDirection);
	}
	else
	{
		m_IsFirstInput = true;
		SetMyState(PathingState);
	}

	vec2 PlayerPos = m_pGame->GetMyPlayer()->GetPosition();

	ivec2 aPlayerColumnRow = ivec2(PlayerPos.x / TILESIZE, PlayerPos.y / TILESIZE);

	ivec2 MinRange = m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex);
	ivec2 MaxRange = m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex);

	if (aPlayerColumnRow.x > MinRange.x && aPlayerColumnRow.x < MaxRange.x && aPlayerColumnRow.y > MinRange.y && aPlayerColumnRow.y < MaxRange.y)
	{
		SetMyState(TrackToPlayerState);
	}

}

void WildPokemonTile::TrackToPlayerUpdate(float deltatime)
{
}

void WildPokemonTile::Draw(vec2 camPos, vec2 projecScale)
{
	m_pMesh->DebugDraw(m_Position, 0, TILESIZE, camPos, projecScale);
}

void WildPokemonTile::Move(SpriteDirection dir, float deltatime)
{
	NewPosition = m_Position;

	Resume();

	if (myDirection != dir)
	{
		myDirection = dir;
	}

	vec2 velocity = DIRECTIONVECTOR[dir] * NPC_SPEED;

	NewPosition += velocity * deltatime;

	if (CheckForCollision(NewPosition))
	{
		SetPosition(NewPosition);
	}
	else
	{
		m_MyState = PathingState;
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

	ivec2 aMin = m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex);
	ivec2 aMax = m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex);

	m_MyNewDestination.x = RangeRandomIntAlg(aMin.x, aMax.x);
	m_MyNewDestination.y = RangeRandomIntAlg(aMin.y, aMax.y);

	while (m_PathingComplete == false)
	{
		m_PathingComplete = m_MyPathFinder->FindPath(anIndex.x, anIndex.y, m_MyNewDestination.x, m_MyNewDestination.y);

		if (m_PathingComplete == true)
		{
			m_MyPathFinder->GetPath(m_MyPath, GetMaxPathSize(), m_MyNewDestination.x, m_MyNewDestination.y);
		}
		if (m_MyPath == nullptr)
		{
			m_PathingComplete = false;
		}
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
		int NextTileIndex = GetNextTileFromSet(m_CurrentInput);

		ivec2 m_NextTileColumnRow = ivec2(NextTileIndex % GetMyMapWidth(), NextTileIndex / GetMyMapWidth());

		if (m_NextTileColumnRow.x != anIndex.x)
		{

			if (m_NextTileColumnRow.x > anIndex.x)
			{
				return SpriteWalkRight;
			}
			if (m_NextTileColumnRow.x < anIndex.x)
			{
				return SpriteWalkLeft;
			}
		}
		else if (m_NextTileColumnRow.y != anIndex.y)
		{
			if (m_NextTileColumnRow.y > anIndex.y)
			{
				return SpriteWalkUp;
			}

			if (m_NextTileColumnRow.y < anIndex.y)
			{
				return SpriteWalkDown;
			}
		}
	}
	else
	{
		return SpriteDirectionStop;
	}
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
	ivec2 MinColumnRow = m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex);
	ivec2 MaxColumnRow = m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
	{
		int CheckTileIndex = m_MyTileMap->GetIndexFromColumnRow(tx, ty);
		if (m_MyTileMap->GetTileAtIndex(CheckTileIndex).MyForestType == Forest_Wild_Grass_)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void WildPokemonTile::OnEvent(Event * anEvent)
{

}

bool WildPokemonTile::CheckForCollision(vec2 NPCNewPosition)
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	ivec2 OriginIndex = ivec2((NPCNewPosition.x / TILESIZE), ((NPCNewPosition.y - 0.3f) / TILESIZE));
	ivec2 TopLeftIndex = ivec2((NPCNewPosition.x / TILESIZE), (((NPCNewPosition.y - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	ivec2 TopRightIndex = ivec2(((NPCNewPosition.x + (TILESIZE / 2)) / TILESIZE), (((NPCNewPosition.y - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	ivec2 BottomRightIndex = ivec2(((NPCNewPosition.x + (TILESIZE / 2)) / TILESIZE), ((NPCNewPosition.y - 0.3f) / TILESIZE));

	//Check each index for whether the tile it lands on is walkable
	bool CheckOrigin = m_pGame->GetTileMap()->GetTileAtNPC(OriginIndex);
	bool CheckTopLeft = m_pGame->GetTileMap()->GetTileAtNPC(TopLeftIndex);
	bool CheckTopRight = m_pGame->GetTileMap()->GetTileAtNPC(TopRightIndex);
	bool CheckBottomRight = m_pGame->GetTileMap()->GetTileAtNPC(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}

int * WildPokemonTile::GetInputSet()
{
	return m_MyPath;
}

void WildPokemonTile::SetInputSet(int * aPath)
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
	{
		m_MyInputSet[i] = -1;
	}
	m_CurrentInput = 0;
}

void WildPokemonTile::NPCSeekStartPath()
{
	while (m_MyInputSet[m_CurrentInput] != -1)
	{
		m_CurrentInput++;
	}

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
	int randNum = rand() % (max - min + 1) + min;

	return randNum;
}
