#ifndef __Mesh_H__
#define __Mesh_H__

using namespace std;
class Mesh
{
protected:
	struct VertexFormat
	{
		vec2 m_Pos;
		MyColor m_Color;
		vec2 m_UV;

		VertexFormat(vec2 pos, MyColor color, vec2 UV)
		{
			m_Pos = pos;
			m_Color = color;
			m_UV = UV;
		}
		VertexFormat() {}
	};
    GLuint m_VBO;
    ShaderProgram* m_pShader;
	ShaderProgram* m_DebugShader;

	GLuint m_MyTexture;

    GLenum m_PrimitiveType;
    unsigned int m_NumVerts;
	float p_MyRadius;
	float p_MyWidth;
	float p_MyHeight;

	vector<VertexFormat>*m_CanvasVerts = new vector<VertexFormat>;

	bool IsDebug;

public:
    Mesh();
    virtual ~Mesh();

	void SetShader(ShaderProgram* pShader, ShaderProgram* pDebug) { m_pShader = pShader; m_DebugShader = pDebug; }

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

};

#endif //__Mesh_H__
