#include "GamePCH.h"
#include "TownGirl.h"

#include "Controllers/AStarPathFinder.h"
#include "Entities/Entity.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Sprites/AnimatedSprite.h"

TownGirl::TownGirl(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Entity(aGameCore, aMesh, aTexture)
{
	AnimationKeys = { "TownGirlWalkDown_", "TownGirlWalkRight_", "TownGirlWalkLeft_", "TownGirlWalkUp_" };

	for (int& i : m_MyInputSet)
		i = -1;

	for (unsigned int i = 0; i < m_Animations.size(); i++)
	{
		m_Animations[i] = new AnimatedSprite(aResourceManager, aGameCore, aMesh, 1, aTexture);
		m_Animations[i]->AddFrame(AnimationKeys[i] + "1.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "2.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "1.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "3.png");
		m_Animations[i]->SetFrameSpeed(6.0f);
		m_Animations[i]->SetLoop(true);
		m_Animations[i]->SetPosition(myPosition);
	}

	myDirection = SpriteDirection::SpriteWalkDown;
	myNewDirection = SpriteDirection::SpriteWalkDown;
	m_MyTileMap = aTileMap;
	myMesh->GenerateFrameMesh();

	m_Stop = true;
	m_IsFirstInput = false;

	m_CurrentInput = 0;

	myMinIndex = 303;
	myMaxIndex = 667;

	m_MyPath = &m_MyInputSet[0];

	myPathFinder = new AStarPathFinder(m_MyTileMap, this);

	m_PathingComplete = false;
	m_MyIndex = Vector2Int(static_cast<int>(myPosition.myX / TILESIZE), static_cast<int>(myPosition.myY / TILESIZE));
}

TownGirl::~TownGirl()
{
	delete myPathFinder;

	for (const auto& m_Animation : m_Animations)
		delete m_Animation;
}

void TownGirl::Update(float deltatime)
{
	Pause();
	m_MyIndex = Vector2Int(static_cast<int>(myPosition.myX / TILESIZE), static_cast<int>(myPosition.myY / TILESIZE));
	if (m_Stop == true)
	{
		if (GetNextPath(m_MyIndex))
		{
			m_Stop = false;
			m_IsFirstInput = true;
		}
	}
	if (m_Stop == false)
	{
		const int myTarget = m_MyInputSet[m_CurrentInput];

		if (m_IsFirstInput == true)
		{
			myNewDirection = CalculateNextInput(m_MyIndex);
			m_IsFirstInput = false;
		}
		else if (myTarget == ((NUM_COLUMNS * m_MyIndex.y) + m_MyIndex.x))
		{
			myNewDirection = CalculateNextInput(m_MyIndex);
		}
		if (myNewDirection != SpriteDirection::SpriteDirectionStop)
		{
			Move(myNewDirection, deltatime);
		}
		else if (myNewDirection == SpriteDirection::SpriteDirectionStop)
		{
			for (unsigned int i = 0; i < NUM_DIRECTIONS; i++)
			{
				m_Animations[i]->SetFrameIndex(0);
			}

			m_Stop = true;
		}
	}

	for (const auto& m_Animation : m_Animations)
	{
		m_Animation->SetPosition(GetPosition());
		m_Animation->Update(deltatime);
	}
}

void TownGirl::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	m_Animations[static_cast<int>(myDirection)]->Draw(camPos, projecScale);
}

void TownGirl::Move(SpriteDirection dir, float deltatime)
{
	NewPosition = myPosition;

	Resume();

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
		m_Stop = true;
	}
}

void TownGirl::Pause()
{
	for (const auto& m_Animation : m_Animations)
		m_Animation->Pause();
}

void TownGirl::Resume()
{
	for (const auto& m_Animation : m_Animations)
		m_Animation->Resume();
}

void TownGirl::SetStop(bool StopNPC)
{
	if (m_Stop != StopNPC)
		m_Stop = StopNPC;
}

void TownGirl::ResetPathFinder() const
{
	myPathFinder->Reset();
}

bool TownGirl::GetNextPath(Vector2Int anIndex)
{
	const Vector2Int GirlIndex = anIndex;

	for (int& i : m_MyInputSet)
		i = -1;

	ResetPathFinder();

	m_PathingComplete = false;

	while (!m_PathingComplete)
	{
		m_MyNewDestination.x = MathUtility::GetRandomRangeInteger(myMinIndex % NUM_COLUMNS, myMaxIndex % NUM_COLUMNS);
		m_MyNewDestination.y = MathUtility::GetRandomRangeInteger(myMinIndex / NUM_COLUMNS, myMaxIndex / NUM_COLUMNS);

		m_PathingComplete = myPathFinder->FindPath(GirlIndex.x, GirlIndex.y, m_MyNewDestination.x, m_MyNewDestination.y);

		if (m_PathingComplete)
			myPathFinder->GetPath(m_MyPath, MAXPATHSIZE_TOWN_NPC, m_MyNewDestination.x, m_MyNewDestination.y);

		if (!m_MyPath)
			m_PathingComplete = false;
	}

	m_CurrentInput = 0;

	while (m_MyInputSet[m_CurrentInput] != -1)
		m_CurrentInput++;

	m_CurrentInput--;

	return m_PathingComplete;
}
SpriteDirection TownGirl::CalculateNextInput(Vector2Int anIndex)
{
	m_CurrentInput--;

	if (m_CurrentInput != -1)
	{
		const Vector2Int m_NextTileColumnRow = Vector2Int(m_MyInputSet[m_CurrentInput] % NUM_COLUMNS, m_MyInputSet[m_CurrentInput] / NUM_COLUMNS);

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

bool TownGirl::CheckForCollision(Vector2Float NPCNewPosition) const
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
int* TownGirl::GetInputSet() const
{
	return m_MyPath;
}

bool TownGirl::GetNodeIsClearOnSpecial(int tx, int ty) const
{
	const Vector2Int MinColumnRow = m_MyTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int MaxColumnRow = m_MyTileMap->GetColumRowFromIndex(myMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
		return true;

	return false;
}

int TownGirl::GetMyMapWidth() const
{
	return m_MyTileMap->GetMapWidth();
}

int TownGirl::GetMaxPathSize() const
{
	return MAXPATHSIZE_TOWN_NPC;
}