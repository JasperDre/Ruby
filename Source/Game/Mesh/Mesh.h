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
		VertexFormat(Vector2Float aPos, Color aColor, Vector2Float anUV)
		{
			myPosition = aPos;
			myColor = aColor;
			myUVCoordinates = anUV;
		}

		Vector2Float myPosition;
		Vector2Float myUVCoordinates;
		Color myColor;
	};

	Mesh();
	virtual ~Mesh();

	void Draw(Vector2Float anObjectPos, float anOobjectAngle, Vector2Float anObjectScale, Vector2Float aCameraPos, Vector2Float aProjectionScale, unsigned int aTexture, Vector2Float aUVscale, Vector2Float aUVoffset) const;
	void DrawCanvas(Vector2Float aCameraPos, Vector2Float aProjectionScale, unsigned int aTexture) const;
	void DebugDraw(Vector2Float anObjectPos, float anObjectAngle, Vector2Float anObjectScale, Vector2Float aCameraPos, Vector2Float aProjectionScale) const;
	void GenerateTriangle();
	void GenerateCircle();
	void GeneratePolygon(float aRadius, int aVertices, char aRed, char aGreen, char aBlue, char anAlpha);
	void GenerateFrameMesh();
	void GenerateTileMesh();
	void GenerateWildTileMesh();
	void GenerateTextureMesh(Vector2Float aSize);
	void GenerateDebugMesh();
	void GenterateCanvasMesh();

	void SetShaders(ShaderProgram* aShader, ShaderProgram* aDebug) { myShader = aShader; myDebugShader = aDebug; }

	[[nodiscard]] unsigned int GetVBOIdentifier() const { return myVBOIdentifier; }
	[[nodiscard]] unsigned int GetTetureIdentifier() const { return myTextureIdentifier; }
	[[nodiscard]] int GetNumberOfVerticesIdentifier() const { return myNumberOfVertices; }
	[[nodiscard]] float GetWidth() const { return myWidth; }
	[[nodiscard]] float GetHeight() const { return myHeight; }
	[[nodiscard]] const std::vector<VertexFormat>& GetCanvasVertices() const { return myCanvasVertices; }

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
