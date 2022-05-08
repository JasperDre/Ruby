#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/OakLabObjects/ProfessorOak.h"

#include "Sprites/AnimatedSprite.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapOakLab.h"
#include "GameplayHelpers/TileMapPalletTown.h"

#include "Mesh/Mesh.h"

#include "GameplayHelpers/SceneManager.h"
#include "Scenes/Scene.h"
#include "Scenes/OakLab.h"
#include "Scenes/PalletTown.h"

#include "Controllers/AStarPathFinder.h"
#include "ProfessorOak.h"

ProfessorOak::ProfessorOak(ResourceManager * aResourceManager, TileMap* aTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	myDirection = SpriteWalkDown;
	myNewDirection = SpriteWalkDown;
	myResourceManager = aResourceManager;
	m_MyTileMap = aTileMap;
	m_pMesh->GenerateFrameMesh();

	//Initialize the animated sprites
	for (int i = 0; i < NUM_DIRECTIONS; i++)
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

	m_IsFirstInput = true;

	m_MyState = PathingState;

	m_CurrentInput = 0;

	m_MyMinIndex = 97;
	m_MyMaxIndex = 239;

	m_MyPath = &m_MyInputSet[0];

	m_MyNewDestination = ivec2(0, 0);

	for (int i = 0; i < OAKMAXPATHSIZE; i++)
	{
		m_MyInputSet[i] = -1;
	}

	m_MyPathFinder = new AStarPathFinder(m_MyTileMap, this);

	m_MyIndex = ivec2(m_Position.x / TILESIZE, m_Position.y / TILESIZE);
}

ProfessorOak::~ProfessorOak()
{

	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		delete m_Animations[i];
		m_Animations[i] = nullptr;
	}

	delete m_MyPathFinder;
	m_MyPathFinder = nullptr;

	myResourceManager = nullptr;

}

void ProfessorOak::Update(float deltatime)
{
	Pause();

	switch (m_MyState)
	{
	case PathingState:
		PathingUpdate(deltatime);
		break;

	case WalkingState:
		WalkingUpdate(deltatime);
		break;
	}


	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		m_Animations[i]->SetPosition(GetPosition());
		m_Animations[i]->Update(deltatime);
	}
}

void ProfessorOak::PathingUpdate(float delatime)
{
	if (GetNextPath(GetMyIndex()))
	{
		SetMyState(WalkingState);
	}
}

void ProfessorOak::WalkingUpdate(float deltatime)
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
		for (int i = 0; i < NUM_DIRECTIONS; i++)
		{
			m_Animations[i]->SetFrameIndex(0);
		}
		m_IsFirstInput = true;
		SetMyState(PathingState);
	}

}

void ProfessorOak::Draw(vec2 camPos, vec2 projecScale)
{
	m_Animations[myDirection]->Draw(camPos, projecScale);
}

void ProfessorOak::Move(SpriteDirection dir, float deltatime)
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

void ProfessorOak::Pause()
{
	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		m_Animations[i]->Pause();
	}
}

void ProfessorOak::Resume()
{
	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		m_Animations[i]->Resume();
	}
}

void ProfessorOak::ResetPathFinder()
{
	m_MyPathFinder->Reset();
}

bool ProfessorOak::GetNextPath(ivec2 anIndex)
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
SpriteDirection ProfessorOak::CalculateNextInput(ivec2 anIndex)
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
AI_States ProfessorOak::GetMyState()
{
	return m_MyState;
}
void ProfessorOak::SetMyState(AI_States aState)
{
	m_MyState = aState;
}
bool ProfessorOak::GetNodeIsClearOnSpecial(int tx, int ty)
{
	ivec2 MinColumnRow = m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex);
	ivec2 MaxColumnRow = m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ProfessorOak::OnEvent(Event * anEvent)
{

}

bool ProfessorOak::CheckForCollision(vec2 NPCNewPosition)
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
int * ProfessorOak::GetInputSet()
{
	return m_MyPath;
}
void ProfessorOak::SetInputSet(int * aPath)
{
	m_MyPath = aPath;
}
int ProfessorOak::GetCurrentInput()
{
	return m_CurrentInput;
}
void ProfessorOak::SetCurrentInput(int aCurrentInput)
{
	m_CurrentInput = aCurrentInput;
}
int ProfessorOak::GetNextTileFromSet(int aCurrentInput)
{
	return m_MyInputSet[aCurrentInput];
}
void ProfessorOak::ResetInputSet()
{
	for (int i = 0; i < OAKMAXPATHSIZE; i++)
	{
		m_MyInputSet[i] = -1;
	}
	m_CurrentInput = 0;
}
void ProfessorOak::NPCSeekStartPath()
{
	while (m_MyInputSet[m_CurrentInput] != -1)
	{
		m_CurrentInput++;
	}

	m_CurrentInput--;
}
ivec2 ProfessorOak::GetMyMinIndex()
{
	return ivec2(m_MyTileMap->GetColumRowFromIndex(m_MyMinIndex));
}
ivec2 ProfessorOak::GetMyMaxIndex()
{
	return ivec2(m_MyTileMap->GetColumRowFromIndex(m_MyMaxIndex));
}
int ProfessorOak::GetMyMapWidth()
{
	return m_MyTileMap->GetMapWidth();
}
int ProfessorOak::GetMaxPathSize()
{
	return OAKMAXPATHSIZE;
}
void ProfessorOak::SetMyDirection(SpriteDirection aDirection)
{
	myNewDirection = aDirection;
}
int ProfessorOak::RangeRandomIntAlg(int min, int max)
{
	int randNum = rand() % (max - min + 1) + min;

	return randNum;
}