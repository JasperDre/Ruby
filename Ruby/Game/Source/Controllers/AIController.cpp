#include "GamePCH.h"

#include "AIController.h"
#include "Controllers/AStarPathFinder.h"

#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapOakLab.h"
#include "GameplayHelpers/TileMapPalletTown.h"

#include "GameObjects/GameObject.h"


AIController::AIController(TileMap * aTileMap, int aMinIndex, int aMaxIndex, GameObject* aNPC)
{
	m_MyTileMap = aTileMap;
	m_MyNPC = aNPC;
	m_MyPathFinder = new AStarPathFinder(aTileMap, aNPC);

	m_MyMapWidth = m_MyTileMap->GetMapWidth();

	m_MyMaxPathSize = abs((aMinIndex % m_MyMapWidth) - (aMaxIndex % m_MyMapWidth)) + abs((aMinIndex / m_MyMapWidth) - (aMaxIndex / m_MyMapWidth));

	m_MyPath = new int[m_MyMaxPathSize + 1];

	for (int i = 0; i < m_MyMaxPathSize + 1; i++)
	{
		m_MyPath[i] = -1;
	}

	m_MyMaxIndex = aMaxIndex;
	m_MyMinIndex = aMinIndex;

	m_CurrentInput = 0;

	m_MyNewDestination = m_MyNPCindex;
	m_PathingComplete = false;

	m_CurrentDirection = SpriteDirectionStop;
}

AIController::~AIController()
{
	delete m_MyPathFinder;
	delete[] m_MyPath;
}

bool AIController::GetNextPath()
{
	m_MyNPCindex = SetNPCCurrentPosition(m_MyNPC->GetPosition());
	for (int i = 0; i < m_MyMaxPathSize + 1; i++)
	{
		m_MyPath[i] = -1;
	}
	ResetPathFinder();

	m_PathingComplete = false;

	while (m_PathingComplete == false)
	{
		m_MyNewDestination.x = RangeRandomIntAlg(m_MyMinIndex % m_MyMapWidth, m_MyMaxIndex % m_MyMapWidth);
		m_MyNewDestination.y = RangeRandomIntAlg(m_MyMinIndex / m_MyMapWidth, m_MyMaxIndex / m_MyMapWidth);

		m_PathingComplete = m_MyPathFinder->FindPath(m_MyNPCindex.x, m_MyNPCindex.y, m_MyNewDestination.x, m_MyNewDestination.y);
	}
	if (m_PathingComplete == true)
	{
		m_MyPathFinder->GetPath(m_MyPath, m_MyMaxPathSize, m_MyNewDestination.x, m_MyNewDestination.y);
	}

	m_CurrentInput = 0;

	while (*(m_MyPath + m_CurrentInput) != -1)
	{
		m_CurrentInput++;
	}

	m_CurrentInput--;

	return m_PathingComplete;
}

void AIController::ResetPathFinder()
{
	m_MyPathFinder->Reset();
}

SpriteDirection AIController::MoveNPC()
{
	m_CurrentDirection = CalculateNextInput();

	if (m_CurrentDirection == SpriteDirectionStop)
	{
		return SpriteDirectionStop;
	}


	if (m_NextTileColumnRow != m_MyNPCindex)
	{
		if (m_CurrentDirection == SpriteWalkRight)
		{
			return SpriteDirection(SpriteWalkRight);
		}
		if (m_CurrentDirection == SpriteWalkLeft)
		{
			return SpriteDirection(SpriteWalkLeft);
		}
		if (m_CurrentDirection == SpriteWalkDown)
		{
			return SpriteDirection(SpriteWalkDown);
		}
		if (m_CurrentDirection == SpriteWalkUp)
		{
			return SpriteDirection(SpriteWalkUp);
		}
	}
	else
	{
		m_CurrentDirection = SpriteDirectionStop;
	}

}

SpriteDirection AIController::CalculateNextInput()
{
	m_CurrentInput--;

	if (m_CurrentInput != -1)
	{
		m_NextTileColumnRow = ivec2(*(m_MyPath + m_CurrentInput) % m_MyMapWidth, *(m_MyPath + m_CurrentInput) / m_MyMapWidth);

		if (m_NextTileColumnRow.x != m_MyNPCindex.x)
		{

			if (m_NextTileColumnRow.x > m_MyNPCindex.x)
			{
				return SpriteWalkRight;
			}
			if (m_NextTileColumnRow.x < m_MyNPCindex.x)
			{
				return SpriteWalkLeft;
			}
		}
		else if ((m_NextTileColumnRow.y != m_MyNPCindex.y))
		{
			if (m_NextTileColumnRow.y > m_MyNPCindex.y)

				return SpriteWalkUp;
		}

		if (m_NextTileColumnRow.y < m_MyNPCindex.y)
		{
			return SpriteWalkDown;
		}
	}
	else
	{
		return SpriteDirectionStop;
	}
}

ivec2 AIController::SetNPCCurrentPosition(vec2 aNPCPosition)
{
	ivec2 newIndex = ivec2(aNPCPosition.x / TILESIZE, aNPCPosition.y / TILESIZE);

	return newIndex;
}

ivec2 AIController::CalculatedDirection(ivec2 aCurrentIndex, vec2 aDirection)
{
	ivec2 IndexandDirection = ivec2((aCurrentIndex.x + aDirection.x), (aCurrentIndex.y + aDirection.y));

	return IndexandDirection;
}

int AIController::RangeRandomIntAlg(int min, int max)
{
	int aRange = max - min + 1;
	int aRemainder = RAND_MAX % aRange;
	int x;
	do {

		x = rand();

	} while (x >= RAND_MAX - aRemainder);
	return min + x % aRange;

}


