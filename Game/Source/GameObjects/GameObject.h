#ifndef __GameObject_H__
#define __GameObject_H__

class Mesh;
class AStarPathFinder;

class GameObject
{
protected:
    GameCore* m_pGame;

    Mesh* m_pMesh;

    vec2 m_Position;

	GLint m_pMyTexture;

    float m_Angle;

    float m_Radius;

	AStarPathFinder* m_MyPathFinder;

	vec2 my_UVOffset;

	int m_MyMinIndex;
	int m_MyMaxIndex;

public:
    GameObject(GameCore* pGame, Mesh* pMesh, GLuint atexture);
    virtual ~GameObject();

    void OnEvent(Event* pEvent) {}
    virtual void Update(float deltatime) {}
\
	virtual void Draw(vec2 camPos, vec2 projScale);

    virtual bool IsColliding(GameObject* pOtherGameObject);
    virtual void OnCollision(GameObject* pOtherGameObject);

	virtual AI_States GetMyState() { return AI_States(); }
	virtual void SetMyState(AI_States aState) {}

	virtual bool GetNodeIsClearOnSpecial(int tx, int ty) { return false; }
	virtual int RangeRandomIntAlg(int min, int max) { return 0; }

	virtual int* GetInputSet() { return nullptr; }
	virtual void SetInputSet(int* aPath) {}

	virtual int GetCurrentInput() { return 0; }
	virtual void SetCurrentInput(int aCurrentInput) {}

	virtual int GetNextTileFromSet(int aCurrentInput) { return 0; }

	virtual void NPCSeekStartPath() {}
	virtual void ResetInputSet() {}

    // Getters.
    vec2 GetPosition() { return m_Position; }
	ivec2 GetMyIndex() { return ivec2(m_Position.x / TILESIZE, m_Position.y / TILESIZE); }
    float GetAngle() { return m_Angle; }
    float GetRadius() { return m_Radius; }
	virtual ivec2 GetMyMinIndex() { return ivec2(); }
	virtual ivec2 GetMyMaxIndex() { return ivec2(); }
	virtual int GetMyNodeOffset() { return m_MyMinIndex; }
	virtual AStarPathFinder* GetPathFinder() { if (m_MyPathFinder) { return m_MyPathFinder; } else { return nullptr; } }
	virtual int GetMyMapWidth() { return 0; }
	virtual int GetMaxPathSize() { return 0; }

    // Setters.
    void SetPosition(vec2 pos) { m_Position = pos; }
    void SetAngle(float angle) { m_Angle = angle; }
    void SetRadius(float radius) { m_Radius = radius; }
	virtual void SetMyDirection(SpriteDirection aDirection){}
};

#endif //__GameObject_H__
