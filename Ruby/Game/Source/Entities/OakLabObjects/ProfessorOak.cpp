#include "GamePCH.h"
#include "ProfessorOak.h"

#include "Controllers/AStarPathFinder.h"
#include "Entities/Entity.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Sprites/AnimatedSprite.h"

ProfessorOak::ProfessorOak(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Entity(aGameCore, aMesh, aTexture)
	, m_PathingComplete(false)
{
	AnimationKeys = { "OakWalkDown_", "OakWalkRight_", "OakWalkLeft_", "OakWalkUp_" };

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
	aMesh->GenerateFrameMesh();

	m_IsFirstInput = true;

	m_MyState = AI_States::PathingState;

	m_CurrentInput = 0;

	myMinIndex = 97;
	myMaxIndex = 239;

	m_MyPath = &m_MyInputSet[0];

	m_MyNewDestination = ivec2(0, 0);

	myPathFinder = new AStarPathFinder(m_MyTileMap, this);

	m_MyIndex = ivec2(myPosition.myX / TILESIZE, myPosition.myY / TILESIZE);
}

ProfessorOak::~ProfessorOak()
{
	delete myPathFinder;

	for (const auto& m_Animation : m_Animations)
		delete m_Animation;
}

void ProfessorOak::Update(float deltatime)
{
	Pause();

	switch (m_MyState)
	{
		case AI_States::PathingState:
			PathingUpdate(deltatime);
			break;
		case AI_States::WalkingState:
			WalkingUpdate(deltatime);
			break;
		case AI_States::IdleState:
		case AI_States::TrackToPlayerState:
			break;
	}

	for (const auto& m_Animation : m_Animations)
	{
		m_Animation->SetPosition(GetPosition());
		m_Animation->Update(deltatime);
	}
}

void ProfessorOak::PathingUpdate(float delatime)
{
	if (GetNextPath(GetMyIndex()))
		SetMyState(AI_States::WalkingState);
}

void ProfessorOak::WalkingUpdate(float deltatime)
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
		for (const auto& m_Animation : m_Animations)
			m_Animation->SetFrameIndex(0);

		m_IsFirstInput = true;
		SetMyState(AI_States::PathingState);
	}
}

void ProfessorOak::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	m_Animations[static_cast<int>(myDirection)]->Draw(camPos, projecScale);
}

void ProfessorOak::Move(SpriteDirection dir, float deltatime)
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
		m_MyState = AI_States::PathingState;
	}
}

void ProfessorOak::Pause() const
{
	for (const auto m_Animation : m_Animations)
		m_Animation->Pause();
}

void ProfessorOak::Resume() const
{
	for (const auto m_Animation : m_Animations)
		m_Animation->Resume();
}

void ProfessorOak::ResetPathFinder() const
{
	myPathFinder->Reset();
}

bool ProfessorOak::GetNextPath(ivec2 anIndex)
{
	ResetInputSet();

	ResetPathFinder();

	m_PathingComplete = false;

	const ivec2 aMin = m_MyTileMap->GetColumRowFromIndex(myMinIndex);
	const ivec2 aMax = m_MyTileMap->GetColumRowFromIndex(myMaxIndex);

	m_MyNewDestination.x = RangeRandomIntAlg(aMin.x, aMax.x);
	m_MyNewDestination.y = RangeRandomIntAlg(aMin.y, aMax.y);

	while (!m_PathingComplete)
	{
		m_PathingComplete = myPathFinder->FindPath(anIndex.x, anIndex.y, m_MyNewDestination.x, m_MyNewDestination.y);

		if (m_PathingComplete)
			myPathFinder->GetPath(m_MyPath, GetMaxPathSize(), m_MyNewDestination.x, m_MyNewDestination.y);

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

SpriteDirection ProfessorOak::CalculateNextInput(ivec2 anIndex)
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

void ProfessorOak::SetMyState(AI_States aState)
{
	m_MyState = aState;
}

bool ProfessorOak::GetNodeIsClearOnSpecial(int tx, int ty) const
{
	const ivec2 MinColumnRow = m_MyTileMap->GetColumRowFromIndex(myMinIndex);
	const ivec2 MaxColumnRow = m_MyTileMap->GetColumRowFromIndex(myMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
		return true;

	return false;
}

bool ProfessorOak::CheckForCollision(Vector2Float NPCNewPosition) const
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	const ivec2 OriginIndex = ivec2((NPCNewPosition.myX / TILESIZE), ((NPCNewPosition.myY - 0.3f) / TILESIZE));
	const ivec2 TopLeftIndex = ivec2((NPCNewPosition.myX / TILESIZE), (((NPCNewPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const ivec2 TopRightIndex = ivec2(((NPCNewPosition.myX + (TILESIZE / 2)) / TILESIZE), (((NPCNewPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const ivec2 BottomRightIndex = ivec2(((NPCNewPosition.myX + (TILESIZE / 2)) / TILESIZE), ((NPCNewPosition.myY - 0.3f) / TILESIZE));

	//Check each index for whether the tile it lands on is walkable
	const bool CheckOrigin = myGameCore->GetTileMap()->GetTileAtNPC(OriginIndex);
	const bool CheckTopLeft = myGameCore->GetTileMap()->GetTileAtNPC(TopLeftIndex);
	const bool CheckTopRight = myGameCore->GetTileMap()->GetTileAtNPC(TopRightIndex);
	const bool CheckBottomRight = myGameCore->GetTileMap()->GetTileAtNPC(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	const bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}

void ProfessorOak::SetInputSet(int * aPath)
{
	m_MyPath = aPath;
}

void ProfessorOak::SetCurrentInput(int aCurrentInput)
{
	m_CurrentInput = aCurrentInput;
}

void ProfessorOak::ResetInputSet()
{
	for (int& i : m_MyInputSet)
		i = -1;

	m_CurrentInput = 0;
}

void ProfessorOak::NPCSeekStartPath()
{
	while (m_MyInputSet[m_CurrentInput] != -1)
		m_CurrentInput++;

	m_CurrentInput--;
}
ivec2 ProfessorOak::GetMyMinIndex() const
{
	return ivec2(m_MyTileMap->GetColumRowFromIndex(myMinIndex));
}

ivec2 ProfessorOak::GetMyMaxIndex() const
{
	return ivec2(m_MyTileMap->GetColumRowFromIndex(myMaxIndex));
}

int ProfessorOak::GetMyMapWidth() const
{
	return m_MyTileMap->GetMapWidth();
}

int ProfessorOak::GetMaxPathSize() const
{
	return OAKMAXPATHSIZE;
}

void ProfessorOak::SetMyDirection(SpriteDirection aDirection)
{
	myNewDirection = aDirection;
}

int ProfessorOak::RangeRandomIntAlg(int min, int max) const
{
	return rand() % (max - min + 1) + min;
}