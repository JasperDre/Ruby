#include "GamePCH.h"
#include "TownBoy.h"

#include "Controllers/AStarPathFinder.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Sprites/AnimatedSprite.h"

TownBoy::TownBoy(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Entity(aGameCore, aMesh, aTextureIdentifier)
{
	myAnimationKeys = { "TownBoyWalkDown_", "TownBoyWalkRight_", "TownBoyWalkLeft_", "TownBoyWalkUp_" };

	for (int& i : myInputSet)
		i = -1;

	for (unsigned int i = 0; i < myAnimations.size(); i++)
	{
		myAnimations[i] = new AnimatedSprite(aResourceManager, aGameCore, aMesh, 1, aTextureIdentifier);
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "1.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "2.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "1.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "3.png");
		myAnimations[i]->SetFrameSpeed(6.0f);
		myAnimations[i]->SetLoop(true);
		myAnimations[i]->SetPosition(myPosition);
	}

	myDirection = SpriteDirection::SpriteWalkDown;
	myNewDirection = SpriteDirection::SpriteWalkDown;
	myTileMap = aTileMap;
	myMesh->GenerateFrameMesh();

	myIsStopped = true;
	myIsFirstInput = false;

	myCurrentInput = 0;

	myMinIndex = 583;
	myMaxIndex = 816;

	myPath = &myInputSet[0];

	myPathFinder = new AStarPathFinder(myTileMap, this);

	myIsPathingComplete = false;
	myIndex = Vector2Int(static_cast<int>(myPosition.myX / TILESIZE), static_cast<int>(myPosition.myY / TILESIZE));
}

TownBoy::~TownBoy()
{
	delete myPathFinder;

	for (const auto& m_Animation : myAnimations)
		delete m_Animation;
}

void TownBoy::Update(float deltatime)
{
	Pause();

	myIndex = Vector2Int(static_cast<int>(myPosition.myX / TILESIZE), static_cast<int>(myPosition.myY / TILESIZE));

	if (myIsStopped)
	{
		if (GetNextPath(myIndex))
		{
			myIsStopped = false;
			myIsFirstInput = true;
		}
	}

	if (!myIsStopped)
	{
		const int myTarget = myInputSet[myCurrentInput];

		if (myIsFirstInput == true)
		{
			myNewDirection = CalculateNextInput(myIndex);
			myIsFirstInput = false;
		}
		else if (myTarget == ((NUM_COLUMNS * myIndex.y) + myIndex.x))
		{
			myNewDirection = CalculateNextInput(myIndex);
		}

		if (myNewDirection != SpriteDirection::SpriteDirectionStop)
			Move(myNewDirection, deltatime);

		else if (myNewDirection == SpriteDirection::SpriteDirectionStop)
		{
			for (unsigned int i = 0; i < NUM_DIRECTIONS; i++)
				myAnimations[i]->SetFrameIndex(0);

			myIsStopped = true;
		}
	}


	for (unsigned int i = 0; i < NUM_DIRECTIONS; i++)
	{
		myAnimations[i]->SetPosition(GetPosition());
		myAnimations[i]->Update(deltatime);
	}
}

void TownBoy::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myAnimations[static_cast<int>(myDirection)]->Draw(camPos, projecScale);
}

void TownBoy::Move(SpriteDirection dir, float deltatime)
{
	myNewPosition = myPosition;

	Resume();

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
		myIsStopped = true;
	}

}

void TownBoy::Pause() const
{
	for (unsigned int i = 0; i < NUM_DIRECTIONS; i++)
	{
		myAnimations[i]->Pause();
	}
}

void TownBoy::Resume() const
{
	for (unsigned int i = 0; i < NUM_DIRECTIONS; i++)
	{
		myAnimations[i]->Resume();
	}
}

void TownBoy::SetStop(bool StopNPC)
{
	if (myIsStopped != StopNPC)
	{
		myIsStopped = StopNPC;
	}
}

void TownBoy::ResetPathFinder() const
{
	myPathFinder->Reset();
}

bool TownBoy::GetNextPath(Vector2Int anIndex)
{
	const Vector2Int BoyIndex = anIndex;

	for (int i = 0; i < MAXPATHSIZE_TOWN_NPC; i++)
	{
		myInputSet[i] = -1;
	}

	ResetPathFinder();

	myIsPathingComplete = false;

	while (myIsPathingComplete == false)
	{
		myNewDestination.x = MathUtility::GetRandomRangeInteger(myMinIndex % NUM_COLUMNS, myMaxIndex % NUM_COLUMNS);
		myNewDestination.y = MathUtility::GetRandomRangeInteger(myMinIndex / NUM_COLUMNS, myMaxIndex / NUM_COLUMNS);

		myIsPathingComplete = myPathFinder->FindPath(BoyIndex.x, BoyIndex.y, myNewDestination.x, myNewDestination.y);

		if (myIsPathingComplete == true)
		{
			myPathFinder->GetPath(myPath, MAXPATHSIZE_TOWN_NPC, myNewDestination.x, myNewDestination.y);
		}
		if (myPath == nullptr)
		{
			myIsPathingComplete = false;
		}
	}
	myCurrentInput = 0;

	while (myInputSet[myCurrentInput] != -1)
	{
		myCurrentInput++;
	}

	myCurrentInput--;

	return myIsPathingComplete;
}
SpriteDirection TownBoy::CalculateNextInput(Vector2Int anIndex)
{
	myCurrentInput--;

	if (myCurrentInput != -1)
	{
		const Vector2Int m_NextTileColumnRow = Vector2Int(myInputSet[myCurrentInput] % NUM_COLUMNS, myInputSet[myCurrentInput] / NUM_COLUMNS);

		if (m_NextTileColumnRow.x != anIndex.x)
		{
			if (m_NextTileColumnRow.x > anIndex.x)
			{
				return SpriteDirection::SpriteWalkRight;
			}
			if (m_NextTileColumnRow.x < anIndex.x)
			{
				return SpriteDirection::SpriteWalkLeft;
			}
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

bool TownBoy::IsColliding(Vector2Float NPCNewPosition) const
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

int* TownBoy::GetInputSet() const
{
	return myPath;
}

bool TownBoy::IsNodeClearOnSpecial(int tx, int ty) const
{
	const Vector2Int MinColumnRow = myTileMap->GetColumRowFromIndex(myMinIndex);
	const Vector2Int MaxColumnRow = myTileMap->GetColumRowFromIndex(myMaxIndex);
	if (tx > MinColumnRow.x && tx < MaxColumnRow.x && ty > MinColumnRow.y && ty < MaxColumnRow.y)
		return true;

	return false;
}
int TownBoy::GetMyMapWidth() const
{
	return myTileMap->GetMapWidth();
}

int TownBoy::GetMaxPathSize() const
{
	return MAXPATHSIZE_TOWN_NPC;
}