#include "GamePCH.h"
#include "Mesh.h"

Mesh::Mesh()
{
	m_VBO = 0;
	m_pShader = nullptr;
	m_DebugShader = nullptr;

	m_MyTexture = 0;

	m_PrimitiveType = -1;
	m_NumVerts = 0;

	IsDebug = false;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	m_CanvasVerts.clear();
}

void SetUniform1f(GLuint shader, const char* uniformName, float value)
{
	if (const GLint loc = glGetUniformLocation(shader, uniformName); loc != -1)
		glUniform1f(loc, value);
}

void SetUniform2f(GLuint shader, const char* uniformName, Vector2Float value)
{
	if (const GLint loc = glGetUniformLocation(shader, uniformName); loc != -1)
		glUniform2f(loc, value.myX, value.myY);
}

void Mesh::Draw(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float camPos, Vector2Float projScale, GLuint aTexture, Vector2Float aUVscale, Vector2Float aUVoffset)
{
	assert(m_PrimitiveType != -1);
	assert(m_NumVerts != 0);
	assert(m_pShader);
	assert(m_pShader->GetProgram() != 0);

	// Bind buffer and set up attributes.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	GLint loc = glGetAttribLocation(m_pShader->GetProgram(), "a_Position");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Pos));
		glEnableVertexAttribArray(loc);
	}

	loc = glGetAttribLocation(m_pShader->GetProgram(), "a_Color");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Color));
		glEnableVertexAttribArray(loc);
	}

	loc = glGetAttribLocation(m_pShader->GetProgram(), "a_UVCoord");
	if(loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_UV));
		glEnableVertexAttribArray(loc);
	}

	const GLuint shader = m_pShader->GetProgram();
	glUseProgram(shader);

	SetUniform2f(shader, "u_ObjectScale", objectScale);
	SetUniform1f(shader, "u_ObjectAngleRadians", objectAngle / 180.0f * Math::pi);
	SetUniform2f(shader, "u_ObjectPosition", objectPos);
	SetUniform2f(shader, "u_CameraTranslation", camPos * -1);
	SetUniform2f(shader, "u_ProjectionScale", projScale);

	glActiveTexture(GL_TEXTURE0 + 8);
	glBindTexture(GL_TEXTURE_2D, aTexture);
	const int texture = glGetUniformLocation(m_pShader->GetProgram(), "u_TextureSampler");

	glUniform1i(texture, 8);
	SetUniform2f(shader, "u_UVScale", aUVscale);
	SetUniform2f(shader, "u_UVOffset", aUVoffset);

	GLHelpers::CheckForGLErrors();

	glDrawArrays(m_PrimitiveType, 0, m_NumVerts);

	GLHelpers::CheckForGLErrors();

	if (IsDebug)
		DebugDraw(objectPos, objectAngle, objectScale, camPos, projScale);

	GLHelpers::CheckForGLErrors();
}
void Mesh::DrawCanvas(Vector2Float cameraPos, Vector2Float projectionScale, GLuint aTexture)
{
	assert(m_PrimitiveType != -1);
	assert(m_NumVerts != 0);
	assert(m_pShader);
	assert(m_pShader->GetProgram() != 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	GLint loc = glGetAttribLocation(m_pShader->GetProgram(), "a_Position");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Pos));
		glEnableVertexAttribArray(loc);
	}

	loc = glGetAttribLocation(m_pShader->GetProgram(), "a_Color");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Color));
		glEnableVertexAttribArray(loc);
	}

	loc = glGetAttribLocation(m_pShader->GetProgram(), "a_UVCoord");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_UV));
		glEnableVertexAttribArray(loc);
	}

	const GLuint shader = m_pShader->GetProgram();
	glUseProgram(shader);

	SetUniform2f(shader, "u_ObjectScale", 1);
	SetUniform1f(shader, "u_ObjectAngleRadians", 0 / 180.0f * Math::pi);
	SetUniform2f(shader, "u_ObjectPosition", Vector2Float(0.0f, 0.0f));
	SetUniform2f(shader, "u_CameraTranslation", cameraPos * -1);
	SetUniform2f(shader, "u_ProjectionScale", projectionScale);

	glActiveTexture(GL_TEXTURE0 + 8);
	glBindTexture(GL_TEXTURE_2D, aTexture);
	const GLuint texture = glGetUniformLocation(m_pShader->GetProgram(), "u_TextureSampler");

	glUniform1i(texture, 8);
	SetUniform2f(shader, "u_UVScale", Vector2Float(1.0f, 1.0f));
	SetUniform2f(shader, "u_UVOffset", Vector2Float(0.0f, 0.0f));

	GLHelpers::CheckForGLErrors();

	glDrawArrays(m_PrimitiveType, 0, m_NumVerts);

	GLHelpers::CheckForGLErrors();

	if (IsDebug)
		DebugDraw(Vector2Float(0.0f, 0.0f), 0 / 180.0f * Math::pi, 1, cameraPos, projectionScale);

	GLHelpers::CheckForGLErrors();
}
void Mesh::DebugDraw(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float camPos, Vector2Float projScale)
{
	assert(m_PrimitiveType != -1);
	assert(m_NumVerts != 0);
	assert(m_DebugShader);
	assert(m_DebugShader->GetProgram() != 0);

	// Bind buffer and set up attributes.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	GLint loc = glGetAttribLocation(m_DebugShader->GetProgram(), "a_Position");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Pos));
		glEnableVertexAttribArray(loc);
	}

	loc = glGetAttribLocation(m_DebugShader->GetProgram(), "a_Color");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Color));
		glEnableVertexAttribArray(loc);
	}
	// Set up shader.
	const GLuint shader = m_DebugShader->GetProgram();
	glUseProgram(shader);

	// Set up uniforms.
	SetUniform2f(shader, "u_ObjectScale", objectScale);
	SetUniform1f(shader, "u_ObjectAngleRadians", objectAngle / 180.0f * Math::pi);
	SetUniform2f(shader, "u_ObjectPosition", objectPos);
	SetUniform2f(shader, "u_CameraTranslation", camPos * -1);
	SetUniform2f(shader, "u_ProjectionScale", projScale);

	glDrawArrays(GL_LINE_LOOP, 0, m_NumVerts);
}

void Mesh::GenerateTriangle()
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
	assert(m_VBO == 0);

	// Vertex info for a diamond.
	VertexFormat vertexAttributes[] = {
		VertexFormat(Vector2Float(0.0f,  1.0f), Color(255, 255, 255, 255), Vector2Float(0.5f, 1.0f)),
		VertexFormat(Vector2Float(-0.5f, -1.0f), Color(255, 255, 255, 255), Vector2Float(0.25f, 0.0f)),
		VertexFormat(Vector2Float(0.5f, -1.0f), Color(255, 255, 255, 255), Vector2Float(0.75f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_PrimitiveType = GL_TRIANGLES;
	m_NumVerts = 3;

	// Check for errors.
	GLHelpers::CheckForGLErrors();
}

void Mesh::GenerateCircle()
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
	assert(m_VBO == 0);

	// Vertex position info for a diamond.
	VertexFormat vertexAttributes[] = {
		VertexFormat(Vector2Float(0.0f,  1.0f), Color(0, 255,   0, 255), Vector2Float(0.5f, 1.0f)),
		VertexFormat(Vector2Float(-1.0f,  0.0f), Color(0, 255,   0, 255), Vector2Float(0.0f, 0.5f)),
		VertexFormat(Vector2Float(1.0f,  0.0f), Color(0, 255,   0, 255), Vector2Float(1.0f, 0.5f)),
		VertexFormat(Vector2Float(0.0f, -1.0f), Color(0, 255,   0, 255), Vector2Float(0.5f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_PrimitiveType = GL_TRIANGLE_STRIP;
	m_NumVerts = 4;

	// Check for errors.
	GLHelpers::CheckForGLErrors();
}
void Mesh::GeneratePolygon(float radius, int vertices, char r, char g, char b, char a)
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated
	assert(m_VBO == 0);

	p_MyRadius = radius;
	p_MyWidth = radius * 2;
	p_MyHeight = radius * 2;

	std::vector<float> m_Circle;

	float x = 0.0f;
	float y = 0.0f;

	int num_floats = (vertices + 2) * 2;

	m_Circle.push_back(x);
	m_Circle.push_back(y);
	for (int i = 1; i <= vertices; i++)
	{
		x = -(radius * cos(i * (2.0f * Math::pi / vertices)));
		y = -(radius * sin(i * (2.0f * Math::pi / vertices)));

		m_Circle.push_back(x);
		m_Circle.push_back(y);
		m_Circle.push_back(r);
		m_Circle.push_back(g);
		m_Circle.push_back(b);
		m_Circle.push_back(a);


	}
	x = -(radius * cos(1 * (2.0f * Math::pi / vertices)));
	y = -(radius * sin(1 * (2.0f * Math::pi / vertices)));
	m_Circle.push_back(x);
	m_Circle.push_back(y);
	m_Circle.push_back(r);
	m_Circle.push_back(g);
	m_Circle.push_back(b);
	m_Circle.push_back(a);


	/*for (int i = 0; i < m_Circle.mySize(); i++);
	{

	}*/

	// Generate and fill buffer with our attributes.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Circle.size(), &m_Circle.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_PrimitiveType = GL_TRIANGLE_FAN;
	m_NumVerts = vertices + 2;

	// Check for errors.
	GLHelpers::CheckForGLErrors();
}

void Mesh::GenerateFrameMesh()
{
	assert(m_VBO == 0);

	VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  0.0f), Color(0, 255,   0, 255), Vector2Float(0.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f, 1.0f), Color(0, 255,   0, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  1.0f), Color(0, 255,   0, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f, 0.0f), Color(0, 255,   0, 255), Vector2Float(1.0f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_PrimitiveType = GL_TRIANGLE_FAN;
	m_NumVerts = 4;
}

void Mesh::GenerateTileMesh()
{
	assert(m_VBO == 0);

	VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f,  1.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  1.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_PrimitiveType = GL_TRIANGLE_FAN;
	m_NumVerts = 4;
}

void Mesh::GenerateWildTileMesh()
{
	assert(m_VBO == 0);

	VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  0.0f), Color(255, 0, 0, 255), Vector2Float(0.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f,  1.0f), Color(255, 0, 0, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  1.0f), Color(255, 0, 0, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  0.0f), Color(255, 0, 0, 255), Vector2Float(1.0f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_PrimitiveType = GL_LINE_LOOP;
	m_NumVerts = 4;
}

void Mesh::GenerateTextureMesh(Vector2Float aSize)
{
	assert(m_VBO == 0);

	VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f,  aSize.myY), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(aSize.myX,  aSize.myY), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(aSize.myX,  0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_PrimitiveType = GL_TRIANGLE_FAN;
	m_NumVerts = 4;
}

void Mesh::GenerateDebugMesh()
{
	assert(m_VBO == 0);

	VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  1.0f), Color(255, 255,   255, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  1.0f), Color(255, 255,   255, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  0.0f), Color(255, 255,   255, 255), Vector2Float(1.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f, 0.0f), Color(255, 255,   255, 255), Vector2Float(0.0f, 0.0f)),
	};

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_NumVerts = 4;
}

void Mesh::GenterateCanvasMesh(int aSize)
{
    assert(m_VBO == 0);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * aSize, &m_CanvasVerts.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_PrimitiveType = GL_TRIANGLE_STRIP;
    m_NumVerts = aSize;
}

