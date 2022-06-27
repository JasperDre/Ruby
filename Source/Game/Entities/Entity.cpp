#include "Entities/Entity.h"

#include "Mesh/Mesh.h"

Entity::Entity(GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: myPosition(0.0f)
	, myUVOffset(0.0f)
	, myGameCore(aGameCore)
	, myMesh(aMesh)
	, myPathFinder(nullptr)
	, myTextureIdentifier(aTextureIdentifier)
	, myAngle(0.0f)
	, myRadius(10.0f)
	, myMinIndex(0)
	, myMaxIndex(0)
{}

void Entity::Draw(Vector2Float camPos, Vector2Float projScale)
{
	if (myMesh)
		myMesh->Draw(myPosition, myAngle, 1, camPos, projScale, myTextureIdentifier, Vector2Float(1.0f, 1.0f), myUVOffset);
}

AIStates Entity::GetMyState() const
{
	return AIStates::Idle;
}

Vector2Int Entity::GetMyIndex() const
{
	return Vector2Int(static_cast<int>(myPosition.myX / TileSize), static_cast<int>(myPosition.myY / TileSize));
}
