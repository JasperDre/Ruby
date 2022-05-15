#pragma once

#include <vector>

class Mesh
{
protected:
	struct VertexFormat
	{
		Vector2Float m_Pos;
		Color m_Color;
		Vector2Float m_UV;

		VertexFormat() : m_Pos(0.0f), m_UV(0.0f) {}
		VertexFormat(Vector2Float pos, Color color, Vector2Float UV)
		{
			m_Pos = pos;
			m_Color = color;
			m_UV = UV;
		}
	};

	std::vector<VertexFormat> m_CanvasVerts;
	ShaderProgram* m_pShader;
	ShaderProgram* m_DebugShader;
	GLuint m_VBO;
	GLuint m_MyTexture;
	int m_NumVerts;
	float p_MyRadius;
	float p_MyWidth;
	float p_MyHeight;
	GLenum m_PrimitiveType;
	bool IsDebug;

public:
	Mesh();
	virtual ~Mesh();

	void Draw(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float camPos, Vector2Float projScale, GLuint aTexture, Vector2Float aUVscale, Vector2Float aUVoffset);
	void DrawCanvas(Vector2Float cameraPos, Vector2Float projectionScale, GLuint aTexture);
	void DebugDraw(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float camPos, Vector2Float projScale);
	void GenerateTriangle();
	void GenerateCircle();
	void GeneratePolygon(float radius, int vertices, char r, char g, char b, char a);
	void GenerateFrameMesh();
	void GenerateTileMesh();
	void GenerateWildTileMesh();
	void GenerateTextureMesh(Vector2Float aSize);
	void GenerateDebugMesh();
	void GenterateCanvasMesh(int aSize);

	void SetShader(ShaderProgram* pShader, ShaderProgram* pDebug) { m_pShader = pShader; m_DebugShader = pDebug; }
};