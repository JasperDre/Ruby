#pragma once

#include <vector>
#include <glad/glad.h>

#include "Math/Color.h"
#include "Math/Vector2Float.h"

class ShaderProgram;

class Mesh
{
public:
	struct VertexFormat
	{
		VertexFormat() : myPosition(0.0f), myUVCoordinates(0.0f) {}
		VertexFormat(Vector2Float pos, Color color, Vector2Float UV)
		{
			myPosition = pos;
			myColor = color;
			myUVCoordinates = UV;
		}

		Vector2Float myPosition;
		Vector2Float myUVCoordinates;
		Color myColor;
	};

	Mesh();
	virtual ~Mesh();

	void Draw(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float camPos, Vector2Float projScale, unsigned int aTexture, Vector2Float aUVscale, Vector2Float aUVoffset) const;
	void DrawCanvas(Vector2Float cameraPos, Vector2Float projectionScale, unsigned int aTexture) const;
	void DebugDraw(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float camPos, Vector2Float projScale) const;
	void GenerateTriangle();
	void GenerateCircle();
	void GeneratePolygon(float radius, int vertices, char r, char g, char b, char a);
	void GenerateFrameMesh();
	void GenerateTileMesh();
	void GenerateWildTileMesh();
	void GenerateTextureMesh(Vector2Float aSize);
	void GenerateDebugMesh();
	void GenterateCanvasMesh(int aSize);

	void SetShader(ShaderProgram* pShader, ShaderProgram* pDebug) { myShader = pShader; myDebugShader = pDebug; }

protected:
	std::vector<VertexFormat> myCanvasVertices;
	ShaderProgram* myShader;
	ShaderProgram* myDebugShader;
	unsigned int myVBOIdentifier;
	unsigned int myTextureIdentifier;
	int myNumberOfVertices;
	float myRadius;
	float myWidth;
	float myHeight;
	GLenum myPrimitiveType;
	bool myIsDebug;
};
