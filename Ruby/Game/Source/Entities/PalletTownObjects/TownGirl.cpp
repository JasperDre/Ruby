#include "GamePCH.h"
#include "TownGirl.h"

#include "Controllers/AStarPathFinder.h"
#include "Entities/Entity.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Sprites/AnimatedSprite.h"

TownGirl::TownGirl(ResourceManager * aResourceManager, TileMap* aTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : Entity(myGame, myMesh, aTexture)
{
	myDirection = SpriteDirection::SpriteWalkDown;
	myNewDirection = SpriteDirection::SpriteWalkDown;
	myResourceManager = aResourceManager;
	m_MyTileMap = aTileMap;
	m_pMesh->GenerateFrameMesh();

	AnimationKeys[0] = "TownGirlWalkDown_";
	AnimationKeys[1] = "TownGirlWalkRight_";
	AnimationKeys[2] = "TownGirlWalkLeft_";
	AnimationKeys[3] = "TownGirlWalkUp_";

	for (unsigned int i = 0; i < NUM_DIRECTIONS; i++)
	{
		m_Animations[i] = new AnimatedSprite(myResourceManager, myGame, myMesh, 1, aTexture);
		m_Animations[i]->AddFrame(AnimationKeys[i] + "1.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "2.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "1.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "3.png");
		m_Animations[i]->SetFrameSpeed(6.0f);
		m_Animations[i]->SetLoop(true);
		m_Animations[i]->SetPosition(m_Position);
	}

	m_Stop = true;
	m_IsFirstInput = false;

	m_CurrentInput = 0;

	m_MyMinIndex = 303;
	m_MyMaxIndex = 667;

	m_MyPath = &m_MyInputSet[0];

	for (int& i : m_MyInputSet)
		i = -1;

	m_MyPathFinder = new AStarPathFinder(m_MyTileMap, this);

	m_PathingComplete = false;
	m_MyIndex = ivec2(m_Position.myX / TILESIZE, m_Position.myY / TILESIZE);
}

TownGirl::~TownGirl()
{
	for (auto& m_Animation : m_Animations)
	{
		delete m_Animation;
		m_Animation = nullptr;
	}

	myResourceManager = nullptr;
	delete m_MyPathFinder;
	m_MyPath = nullptr;
}

void TownGirl::Update(float deltatime)
{
	Pause();
	m_MyIndex = ivec2(m_Position.myX / TILESIZE, m_Position.myY / TILESIZE);
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
			for (int i = 0; i < NUM_DIRECTIONS; i++)
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
	NewPosition = m_Position;

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
	m_MyPathFinder->Reset();
}

bool TownGirl::GetNextPath(ivec2 anIndex)
{
	const ivec2 GirlIndex = anIndex;

	for (int& i : m_MyInputSet)
		i = -1;

	ResetPathFinder();

	m_PathingComplete = false;

	while (!m_PathingComplete)
	{
		m_MyNewDestination.x = RangeRandomIntAlg(m_MyMinIndex % NUM_COLUMNS, m_MyMaxIndex % NUM_COLUMNS);
		m_MyNewDestination.y = RangeRandomIntAlg(m_MyMinIndex / NUM_COLUMNS, m_MyMaxIndex / NUM_COLUMNS);

		m_PathingComplete = m_MyPathFinder->FindPath(GirlIndex.x, GirlIndex.y, m_MyNewDestination.x, m_MyNewDestination.y);

		if (m_PathingComplete)
			m_MyPathFinder->GetPath(m_MyPath, MAXPATHSIZE_TOWN_NPC, m_MyNewDestination.x, m_MyNewDestination.y);

		if (!m_MyPath)
			m_PathingComplete = false;
	}

	m_CurrentInput = 0;

	while (m_MyInputSet[m_CurrentInput] != -1)
		m_CurrentInput++;

	m_CurrentInput--;

	return m_PathingComplete;
}
SpriteDirection TownGirl::CalculateNextInput(ivec2 anIndex)
{
	m_CurrentInput--;

	if (m_CurrentInput != -1)
	{
		const ivec2 m_NextTileColumnRow = ivec2(m_MyInputSet[m_CurrentInput] % NUM_COLUMNS, m_MyInputSet[m_CurrentInput] / NUM_COLUMNS);

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
void TownGirl::OnEvent(Event* anEvent)
{
}

bool TownGirl::CheckForCollision(Vector2Float NPCNewPosition) const
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
int* TownGirl::GetInputSet()
{
	return m_MyPath;
}

bool TownGirl::GetNodeIsClearOnSpecial(int tx, int ty)
{
	const ivec2 MinColumnRow = m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex);
	const ivec2 MaxColumnRow = m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
		return true;

	return false;
}

int TownGirl::GetMyMapWidth()
{
	return m_MyTileMap->GetMapWidth();
}

int TownGirl::GetMaxPathSize()
{
	return MAXPATHSIZE_TOWN_NPC;
}

int TownGirl::RangeRandomIntAlg(int min, int max)
{
	return rand() % (max - min + 1) + min;
}