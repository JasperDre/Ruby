#pragma once

#include <vector>

class Mesh
{
protected:
	struct VertexFormat
	{
		vec2 m_Pos;
		MyColor m_Color;
		vec2 m_UV;

		VertexFormat() : m_Pos(0.0f), m_UV(0.0f) {}
		VertexFormat(vec2 pos, MyColor color, vec2 UV)
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
	unsigned int m_NumVerts;
	float p_MyRadius;
	float p_MyWidth;
	float p_MyHeight;
	GLenum m_PrimitiveType;
	bool IsDebug;

public:
	Mesh();
	virtual ~Mesh();

	void Draw(vec2 objectPos, float objectAngle, vec2 objectScale, vec2 camPos, vec2 projScale, GLuint aTexture, vec2 aUVscale, vec2 aUVoffset);
	void DrawCanvas(vec2 cameraPos, vec2 projectionScale, GLuint aTexture);
	void DebugDraw(vec2 objectPos, float objectAngle, vec2 objectScale, vec2 camPos, vec2 projScale);
	void GenerateTriangle();
	void GenerateCircle();
	void GeneratePolygon(float radius, int vertices, char r, char g, char b, char a);
	void GenerateFrameMesh();
	void GenerateTileMesh();
	void GenerateWildTileMesh();
	void GenerateTextureMesh(vec2 aSize);
	void GenerateDebugMesh();
	void GenterateCanvasMesh(int aSize);

	void SetShader(ShaderProgram* pShader, ShaderProgram* pDebug) { m_pShader = pShader; m_DebugShader = pDebug; }
};