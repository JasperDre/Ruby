#include "GamePCH.h"
#include "AIController.h"

#include "Controllers/AStarPathFinder.h"
#include "Entities/Entity.h"
#include "GameplayHelpers/TileMap.h"

AIController::AIController(TileMap* aTileMap, int aMinIndex, int aMaxIndex, Entity* aNPC)
{
	m_MyTileMap = aTileMap;
	m_MyNPC = aNPC;
	m_MyPathFinder = new AStarPathFinder(aTileMap, aNPC);

	m_MyMapWidth = m_MyTileMap->GetMapWidth();

	m_MyMaxPathSize = abs((aMinIndex % m_MyMapWidth) - (aMaxIndex % m_MyMapWidth)) + abs((aMinIndex / m_MyMapWidth) - (aMaxIndex / m_MyMapWidth));

	m_MyPath = new int[m_MyMaxPathSize + 1];

	for (int i = 0; i < m_MyMaxPathSize + 1; i++)
		m_MyPath[i] = -1;

	m_MyMaxIndex = aMaxIndex;
	m_MyMinIndex = aMinIndex;

	m_CurrentInput = 0;

	m_MyNewDestination = m_MyNPCindex;
	m_PathingComplete = false;

	m_CurrentDirection = SpriteDirection::SpriteDirectionStop;
}

AIController::~AIController()
{
	delete[] m_MyPath;
	delete m_MyPathFinder;
}

bool AIController::GetNextPath()
{
	m_MyNPCindex = SetNPCCurrentPosition(m_MyNPC->GetPosition());
	for (int i = 0; i < m_MyMaxPathSize + 1; i++)
		m_MyPath[i] = -1;

	ResetPathFinder();

	m_PathingComplete = false;

	while (!m_PathingComplete)
	{
		m_MyNewDestination.x = MathUtility::GetRandomRangeInteger(m_MyMinIndex % m_MyMapWidth, m_MyMaxIndex % m_MyMapWidth);
		m_MyNewDestination.y = MathUtility::GetRandomRangeInteger(m_MyMinIndex / m_MyMapWidth, m_MyMaxIndex / m_MyMapWidth);

		m_PathingComplete = m_MyPathFinder->FindPath(m_MyNPCindex.x, m_MyNPCindex.y, m_MyNewDestination.x, m_MyNewDestination.y);
	}

	if (m_PathingComplete)
		m_MyPathFinder->GetPath(m_MyPath, m_MyMaxPathSize, m_MyNewDestination.x, m_MyNewDestination.y);

	m_CurrentInput = 0;

	while (*(m_MyPath + m_CurrentInput) != -1)
		m_CurrentInput++;

	m_CurrentInput--;

	return m_PathingComplete;
}

void AIController::ResetPathFinder() const
{
	m_MyPathFinder->Reset();
}

SpriteDirection AIController::MoveNPC()
{
	m_CurrentDirection = CalculateNextInput();

	if (m_CurrentDirection == SpriteDirection::SpriteDirectionStop)
		return SpriteDirection::SpriteDirectionStop;

	if (m_NextTileColumnRow != m_MyNPCindex)
	{
		if (m_CurrentDirection == SpriteDirection::SpriteWalkRight)
		{
			return SpriteDirection::SpriteWalkRight;
		}
		if (m_CurrentDirection == SpriteDirection::SpriteWalkLeft)
		{
			return SpriteDirection::SpriteWalkLeft;
		}
		if (m_CurrentDirection == SpriteDirection::SpriteWalkDown)
		{
			return SpriteDirection::SpriteWalkDown;
		}
		if (m_CurrentDirection == SpriteDirection::SpriteWalkUp)
		{
			return SpriteDirection::SpriteWalkUp;
		}
	}
	else
	{
		m_CurrentDirection = SpriteDirection::SpriteDirectionStop;
	}

	return m_CurrentDirection;
}

SpriteDirection AIController::CalculateNextInput()
{
	m_CurrentInput--;

	if (m_CurrentInput != -1)
	{
		m_NextTileColumnRow = Vector2Int(*(m_MyPath + m_CurrentInput) % m_MyMapWidth, *(m_MyPath + m_CurrentInput) / m_MyMapWidth);

		if (m_NextTileColumnRow.x != m_MyNPCindex.x)
		{
			if (m_NextTileColumnRow.x > m_MyNPCindex.x)
				return SpriteDirection::SpriteWalkRight;

			if (m_NextTileColumnRow.x < m_MyNPCindex.x)
				return SpriteDirection::SpriteWalkLeft;
		}
		else if (m_NextTileColumnRow.y != m_MyNPCindex.y)
		{
			if (m_NextTileColumnRow.y > m_MyNPCindex.y)
				return SpriteDirection::SpriteWalkUp;
		}

		if (m_NextTileColumnRow.y < m_MyNPCindex.y)
			return SpriteDirection::SpriteWalkDown;
	}
	else
	{
		return SpriteDirection::SpriteDirectionStop;
	}

	return SpriteDirection::SpriteDirectionStop;
}

Vector2Int AIController::SetNPCCurrentPosition(Vector2Float aNPCPosition)
{
	return Vector2Int(static_cast<int>(aNPCPosition.myX / TILESIZE), static_cast<int>(aNPCPosition.myY / TILESIZE));
}

Vector2Int AIController::CalculatedDirection(Vector2Int aCurrentIndex, Vector2Float aDirection)
{
	return Vector2Int(aCurrentIndex.x + static_cast<int>(aDirection.myX), aCurrentIndex.y + static_cast<int>(aDirection.myY));
}