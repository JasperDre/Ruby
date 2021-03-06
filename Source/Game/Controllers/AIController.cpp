#include "AIController.h"

#include "Controllers/AStarPathFinder.h"
#include "Entities/Entity.h"
#include "GameplayHelpers/TileMap.h"
#include "Utility/MathUtility.h"

AIController::AIController(TileMap* aTileMap, int aMinIndex, int aMaxIndex, Entity* aNPC)
{
	myTileMap = aTileMap;
	myNPC = aNPC;
	myPathFinder = new AStarPathFinder(aTileMap, aNPC);

	myMapWidth = myTileMap->GetMapWidth();

	myMaxPathSize = abs((aMinIndex % myMapWidth) - (aMaxIndex % myMapWidth)) + abs((aMinIndex / myMapWidth) - (aMaxIndex / myMapWidth));

	myPath = new int[myMaxPathSize + 1];

	for (int i = 0; i < myMaxPathSize + 1; i++)
		myPath[i] = -1;

	myMaxIndex = aMaxIndex;
	myMinIndex = aMinIndex;

	myCurrentInput = 0;

	myNewDestination = myNPCindex;
	myIsPathingComplete = false;

	myCurrentDirection = SpriteDirection::DirectionStop;
}

AIController::~AIController()
{
	delete[] myPath;
	delete myPathFinder;
}

bool AIController::GetNextPath()
{
	myNPCindex = SetNPCCurrentPosition(myNPC->GetPosition());
	for (int i = 0; i < myMaxPathSize + 1; i++)
		myPath[i] = -1;

	ResetPathFinder();

	myIsPathingComplete = false;

	while (!myIsPathingComplete)
	{
		myNewDestination.x = MathUtility::GetRandomRangeInteger(myMinIndex % myMapWidth, myMaxIndex % myMapWidth);
		myNewDestination.y = MathUtility::GetRandomRangeInteger(myMinIndex / myMapWidth, myMaxIndex / myMapWidth);

		myIsPathingComplete = myPathFinder->FindPath(myNPCindex.x, myNPCindex.y, myNewDestination.x, myNewDestination.y);
	}

	if (myIsPathingComplete)
		myPathFinder->GetPath(myPath, myMaxPathSize, myNewDestination.x, myNewDestination.y);

	myCurrentInput = 0;

	while (*(myPath + myCurrentInput) != -1)
		myCurrentInput++;

	myCurrentInput--;

	return myIsPathingComplete;
}

void AIController::ResetPathFinder() const
{
	myPathFinder->Reset();
}

SpriteDirection AIController::MoveNPC()
{
	myCurrentDirection = CalculateNextInput();

	if (myCurrentDirection == SpriteDirection::DirectionStop)
		return SpriteDirection::DirectionStop;

	if (myNextTileColumnRow != myNPCindex)
	{
		if (myCurrentDirection == SpriteDirection::WalkRight)
		{
			return SpriteDirection::WalkRight;
		}
		if (myCurrentDirection == SpriteDirection::WalkLeft)
		{
			return SpriteDirection::WalkLeft;
		}
		if (myCurrentDirection == SpriteDirection::WalkDown)
		{
			return SpriteDirection::WalkDown;
		}
		if (myCurrentDirection == SpriteDirection::WalkUp)
		{
			return SpriteDirection::WalkUp;
		}
	}
	else
	{
		myCurrentDirection = SpriteDirection::DirectionStop;
	}

	return myCurrentDirection;
}

SpriteDirection AIController::CalculateNextInput()
{
	myCurrentInput--;

	if (myCurrentInput != -1)
	{
		myNextTileColumnRow = Vector2Int(*(myPath + myCurrentInput) % myMapWidth, *(myPath + myCurrentInput) / myMapWidth);

		if (myNextTileColumnRow.x != myNPCindex.x)
		{
			if (myNextTileColumnRow.x > myNPCindex.x)
				return SpriteDirection::WalkRight;

			if (myNextTileColumnRow.x < myNPCindex.x)
				return SpriteDirection::WalkLeft;
		}
		else if (myNextTileColumnRow.y != myNPCindex.y)
		{
			if (myNextTileColumnRow.y > myNPCindex.y)
				return SpriteDirection::WalkUp;
		}

		if (myNextTileColumnRow.y < myNPCindex.y)
			return SpriteDirection::WalkDown;
	}
	else
	{
		return SpriteDirection::DirectionStop;
	}

	return SpriteDirection::DirectionStop;
}

Vector2Int AIController::SetNPCCurrentPosition(Vector2Float aNPCPosition)
{
	return Vector2Int(static_cast<int>(aNPCPosition.myX / TileSize), static_cast<int>(aNPCPosition.myY / TileSize));
}

Vector2Int AIController::CalculatedDirection(Vector2Int aCurrentIndex, Vector2Float aDirection)
{
	return Vector2Int(aCurrentIndex.x + static_cast<int>(aDirection.myX), aCurrentIndex.y + static_cast<int>(aDirection.myY));
}