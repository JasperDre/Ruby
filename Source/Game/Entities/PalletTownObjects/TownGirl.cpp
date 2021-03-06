#include "TownGirl.h"

#include "Controllers/AStarPathFinder.h"
#include "Entities/Entity.h"
#include "GameCore/GameCore.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Sprites/AnimatedSprite.h"
#include "Utility/MathUtility.h"

TownGirl::TownGirl(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Entity(aGameCore, aMesh, aTexture)
{
	myAnimationKeys = { "TownGirlWalkDown_", "TownGirlWalkRight_", "TownGirlWalkLeft_", "TownGirlWalkUp_" };

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
	myMesh->GenerateFrameMesh();

	myIsStopped = true;
	myIsFirstInput = false;

	myCurrentInput = 0;

	myMinIndex = 303;
	myMaxIndex = 667;

	myPath = &myInputSet[0];

	myPathFinder = new AStarPathFinder(myTileMap, this);

	myIsPathingComplete = false;
	myIndex = Vector2Int(static_cast<int>(myPosition.myX / TileSize), static_cast<int>(myPosition.myY / TileSize));
}

TownGirl::~TownGirl()
{
	delete myPathFinder;

	for (const auto& m_Animation : myAnimations)
		delete m_Animation;
}

void TownGirl::Update(float deltatime)
{
	Pause();
	myIndex = Vector2Int(static_cast<int>(myPosition.myX / TileSize), static_cast<int>(myPosition.myY / TileSize));
	if (myIsStopped == true)
	{
		if (GetNextPath(myIndex))
		{
			myIsStopped = false;
			myIsFirstInput = true;
		}
	}
	if (myIsStopped == false)
	{
		const int myTarget = myInputSet[myCurrentInput];

		if (myIsFirstInput == true)
		{
			myNewDirection = CalculateNextInput(myIndex);
			myIsFirstInput = false;
		}
		else if (myTarget == ((Columns * myIndex.y) + myIndex.x))
		{
			myNewDirection = CalculateNextInput(myIndex);
		}
		if (myNewDirection != SpriteDirection::DirectionStop)
		{
			Move(myNewDirection, deltatime);
		}
		else if (myNewDirection == SpriteDirection::DirectionStop)
		{
			for (unsigned int i = 0; i < Directions; i++)
			{
				myAnimations[i]->SetFrameIndex(0);
			}

			myIsStopped = true;
		}
	}

	for (const auto& m_Animation : myAnimations)
	{
		m_Animation->SetPosition(GetPosition());
		m_Animation->Update(deltatime);
	}
}

void TownGirl::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myAnimations[static_cast<int>(myDirection)]->Draw(camPos, projecScale);
}

void TownGirl::Move(SpriteDirection dir, float deltatime)
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
		myIsStopped = true;
	}
}

void TownGirl::Pause()
{
	for (const auto& m_Animation : myAnimations)
		m_Animation->Pause();
}

void TownGirl::Resume()
{
	for (const auto& m_Animation : myAnimations)
		m_Animation->Resume();
}

void TownGirl::SetStop(bool StopNPC)
{
	if (myIsStopped != StopNPC)
		myIsStopped = StopNPC;
}

void TownGirl::ResetPathFinder() const
{
	myPathFinder->Reset();
}

bool TownGirl::GetNextPath(Vector2Int anIndex)
{
	const Vector2Int GirlIndex = anIndex;

	for (int& i : myInputSet)
		i = -1;

	ResetPathFinder();

	myIsPathingComplete = false;

	while (!myIsPathingComplete)
	{
		myNewDestination.x = MathUtility::GetRandomRangeInteger(myMinIndex % Columns, myMaxIndex % Columns);
		myNewDestination.y = MathUtility::GetRandomRangeInteger(myMinIndex / Columns, myMaxIndex / Columns);

		myIsPathingComplete = myPathFinder->FindPath(GirlIndex.x, GirlIndex.y, myNewDestination.x, myNewDestination.y);

		if (myIsPathingComplete)
			myPathFinder->GetPath(myPath, TownNPCMaxPathSize, myNewDestination.x, myNewDestination.y);

		if (!myPath)
			myIsPathingComplete = false;
	}

	myCurrentInput = 0;

	while (myInputSet[myCurrentInput] != -1)
		myCurrentInput++;

	myCurrentInput--;

	return myIsPathingComplete;
}
SpriteDirection TownGirl::CalculateNextInput(Vector2Int anIndex)
{
	myCurrentInput--;

	if (myCurrentInput != -1)
	{
		const Vector2Int m_NextTileColumnRow = Vector2Int(myInputSet[myCurrentInput] % Columns, myInputSet[myCurrentInput] / Columns);

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

bool TownGirl::IsColliding(Vector2Float NPCNewPosition) const
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
int* TownGirl::GetInputSet() const
{
	return myPath;
}

bool TownGirl::IsNodeClearOnSpecial(int tx, int ty) const
{
	const Vector2Int MinColumnRow = myTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int MaxColumnRow = myTileMap->GetColumRowFromIndex(myMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
		return true;

	return false;
}

int TownGirl::GetMyMapWidth() const
{
	return myTileMap->GetMapWidth();
}

int TownGirl::GetMaxPathSize() const
{
	return TownNPCMaxPathSize;
}