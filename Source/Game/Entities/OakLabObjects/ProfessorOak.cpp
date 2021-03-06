#include "ProfessorOak.h"

#include "Controllers/AStarPathFinder.h"
#include "Entities/Entity.h"
#include "GameCore/GameCore.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Sprites/AnimatedSprite.h"
#include "Utility/MathUtility.h"

ProfessorOak::ProfessorOak(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Entity(aGameCore, aMesh, aTexture)
	, myIsPathingComplete(false)
{
	myAnimationKeys = { "OakWalkDown_", "OakWalkRight_", "OakWalkLeft_", "OakWalkUp_" };

	for (int& i : myInputSet)
		i = -1;

	for (unsigned int i = 0; i < myAnimations.size(); i++)
	{
		myAnimations[i] = new AnimatedSprite(aResourceManager, aGameCore, aMesh, 1, aTexture);
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "1.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "2.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "1.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "3.png");
		myAnimations[i]->SetFrameSpeed(6.0f);
		myAnimations[i]->SetLoop(true);
		myAnimations[i]->SetPosition(myPosition);
	}

	myDirection = SpriteDirection::WalkDown;
	myNewDirection = SpriteDirection::WalkDown;
	myTileMap = aTileMap;
	aMesh->GenerateFrameMesh();

	myIsFirstInput = true;

	myState = AIStates::Pathing;

	myCurrentInput = 0;

	myMinIndex = 97;
	myMaxIndex = 239;

	myPath = &myInputSet[0];

	myNewDestination = Vector2Int(0, 0);

	myPathFinder = new AStarPathFinder(myTileMap, this);

	myIndex = Vector2Int(static_cast<int>(myPosition.myX / TileSize), static_cast<int>(myPosition.myY / TileSize));
}

ProfessorOak::~ProfessorOak()
{
	delete myPathFinder;

	for (const auto& m_Animation : myAnimations)
		delete m_Animation;
}

void ProfessorOak::Update(float deltatime)
{
	Pause();

	switch (myState)
	{
		case AIStates::Pathing:
			PathingUpdate(deltatime);
			break;
		case AIStates::Walking:
			WalkingUpdate(deltatime);
			break;
		case AIStates::Idle:
		case AIStates::TrackToPlayer:
			break;
	}

	for (const auto& m_Animation : myAnimations)
	{
		m_Animation->SetPosition(GetPosition());
		m_Animation->Update(deltatime);
	}
}

void ProfessorOak::PathingUpdate(float delatime)
{
	if (GetNextPath(GetMyIndex()))
		SetMyState(AIStates::Walking);
}

void ProfessorOak::WalkingUpdate(float deltatime)
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

	if (myNewDirection != SpriteDirection::DirectionStop)
	{
		Move(myNewDirection, deltatime);
		SetMyDirection(myNewDirection);
	}
	else
	{
		for (const auto& m_Animation : myAnimations)
			m_Animation->SetFrameIndex(0);

		myIsFirstInput = true;
		SetMyState(AIStates::Pathing);
	}
}

void ProfessorOak::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myAnimations[static_cast<int>(myDirection)]->Draw(camPos, projecScale);
}

void ProfessorOak::Move(SpriteDirection dir, float deltatime)
{
	myNewPosition = myPosition;

	Resume();

	if (myDirection != dir)
		myDirection = dir;

	const Vector2Float velocity = DirectionVector[static_cast<int>(dir)] * NPCSpeed;

	myNewPosition += velocity * deltatime;

	if (IsColliding(myNewPosition))
	{
		SetPosition(myNewPosition);
	}
	else
	{
		myState = AIStates::Pathing;
	}
}

void ProfessorOak::Pause() const
{
	for (const auto m_Animation : myAnimations)
		m_Animation->Pause();
}

void ProfessorOak::Resume() const
{
	for (const auto m_Animation : myAnimations)
		m_Animation->Resume();
}

void ProfessorOak::ResetPathFinder() const
{
	myPathFinder->Reset();
}

bool ProfessorOak::GetNextPath(Vector2Int anIndex)
{
	ResetInputSet();

	ResetPathFinder();

	myIsPathingComplete = false;

	const Vector2Int aMin = myTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int aMax = myTileMap->GetColumRowFromIndex(myMaxIndex);

	myNewDestination.x = MathUtility::GetRandomRangeInteger(aMin.x, aMax.x);
	myNewDestination.y = MathUtility::GetRandomRangeInteger(aMin.y, aMax.y);

	while (!myIsPathingComplete)
	{
		myIsPathingComplete = myPathFinder->FindPath(anIndex.x, anIndex.y, myNewDestination.x, myNewDestination.y);

		if (myIsPathingComplete)
			myPathFinder->GetPath(myPath, GetMaxPathSize(), myNewDestination.x, myNewDestination.y);

		if (!myPath)
			myIsPathingComplete = false;

		if (myIsPathingComplete == false)
		{
			myNewDestination.x = MathUtility::GetRandomRangeInteger(aMin.x, aMax.x);
			myNewDestination.y = MathUtility::GetRandomRangeInteger(aMin.y, aMax.y);
		}
	}

	SetCurrentInput(0);
	NPCSeekStartPath();

	return myIsPathingComplete;
}

SpriteDirection ProfessorOak::CalculateNextInput(Vector2Int anIndex)
{
	myCurrentInput--;

	if (myCurrentInput != -1)
	{
		const int NextTileIndex = GetNextTileFromSet(myCurrentInput);
		const Vector2Int m_NextTileColumnRow = Vector2Int(NextTileIndex % GetMyMapWidth(), NextTileIndex / GetMyMapWidth());

		if (m_NextTileColumnRow.x != anIndex.x)
		{
			if (m_NextTileColumnRow.x > anIndex.x)
				return SpriteDirection::WalkRight;

			if (m_NextTileColumnRow.x < anIndex.x)
				return SpriteDirection::WalkLeft;
		}
		else if (m_NextTileColumnRow.y != anIndex.y)
		{
			if (m_NextTileColumnRow.y > anIndex.y)
				return SpriteDirection::WalkUp;

			if (m_NextTileColumnRow.y < anIndex.y)
				return SpriteDirection::WalkDown;
		}
	}
	else
	{
		return SpriteDirection::DirectionStop;
	}

	return SpriteDirection::DirectionStop;
}

void ProfessorOak::SetMyState(AIStates aState)
{
	myState = aState;
}

bool ProfessorOak::IsNodeClearOnSpecial(int tx, int ty) const
{
	const Vector2Int MinColumnRow = myTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int MaxColumnRow = myTileMap->GetColumRowFromIndex(myMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
		return true;

	return false;
}

bool ProfessorOak::IsColliding(Vector2Float NPCNewPosition) const
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	const Vector2Int OriginIndex = Vector2Int(static_cast<int>(NPCNewPosition.myX / TileSize), static_cast<int>((NPCNewPosition.myY - 0.3f) / TileSize));
	const Vector2Int TopLeftIndex = Vector2Int(static_cast<int>(NPCNewPosition.myX / TileSize), static_cast<int>(((NPCNewPosition.myY - 0.5f) + (TileSize / 2)) / TileSize));
	const Vector2Int TopRightIndex = Vector2Int(static_cast<int>((NPCNewPosition.myX + (TileSize / 2)) / TileSize), static_cast<int>(((NPCNewPosition.myY - 0.5f) + (TileSize / 2)) / TileSize));
	const Vector2Int BottomRightIndex = Vector2Int(static_cast<int>((NPCNewPosition.myX + (TileSize / 2)) / TileSize), static_cast<int>((NPCNewPosition.myY - 0.3f) / TileSize));

	//Check each index for whether the tile it lands on is walkable
	const bool CheckOrigin = myGameCore->GetTileMap()->IsTileAtNPC(OriginIndex);
	const bool CheckTopLeft = myGameCore->GetTileMap()->IsTileAtNPC(TopLeftIndex);
	const bool CheckTopRight = myGameCore->GetTileMap()->IsTileAtNPC(TopRightIndex);
	const bool CheckBottomRight = myGameCore->GetTileMap()->IsTileAtNPC(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	const bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}

void ProfessorOak::SetInputSet(int* aPath)
{
	myPath = aPath;
}

void ProfessorOak::SetCurrentInput(int aCurrentInput)
{
	myCurrentInput = aCurrentInput;
}

void ProfessorOak::ResetInputSet()
{
	for (int& i : myInputSet)
		i = -1;

	myCurrentInput = 0;
}

void ProfessorOak::NPCSeekStartPath()
{
	while (myInputSet[myCurrentInput] != -1)
		myCurrentInput++;

	myCurrentInput--;
}
Vector2Int ProfessorOak::GetMyMinIndex() const
{
	return Vector2Int(myTileMap->GetColumRowFromIndex(myMinIndex));
}

Vector2Int ProfessorOak::GetMyMaxIndex() const
{
	return Vector2Int(myTileMap->GetColumRowFromIndex(myMaxIndex));
}

int ProfessorOak::GetMyMapWidth() const
{
	return myTileMap->GetMapWidth();
}

int ProfessorOak::GetMaxPathSize() const
{
	return OakMaxPathSize;
}

void ProfessorOak::SetMyDirection(SpriteDirection aDirection)
{
	myNewDirection = aDirection;
}