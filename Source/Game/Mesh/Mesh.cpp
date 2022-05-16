#include "GamePCH.h"
#include "Mesh.h"

Mesh::Mesh()
	: myRadius(0)
	, myWidth(0)
	, myHeight(0)
{
	myVBOIdentifier = 0;
	myShader = nullptr;
	myDebugShader = nullptr;
	myTextureIdentifier = 0;
	myPrimitiveType = -1;
	myNumberOfVertices = 0;
	myIsDebug = false;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &myVBOIdentifier);
	myCanvasVertices.clear();
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

void Mesh::Draw(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float camPos, Vector2Float projScale, GLuint aTexture, Vector2Float aUVscale, Vector2Float aUVoffset) const
{
	assert(myPrimitiveType != static_cast<GLenum>(-1));
	assert(myNumberOfVertices != 0);
	assert(myShader);
	assert(myShader->GetProgram() != 0);

	// Bind buffer and set up attributes.
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);

	const GLint positionLocation = glGetAttribLocation(myShader->GetProgram(), "a_Position");
	if (positionLocation != -1)
	{
		glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myPosition)));
		glEnableVertexAttribArray(positionLocation);
	}

	const GLint colorLocation = glGetAttribLocation(myShader->GetProgram(), "a_Color");
	if (colorLocation != -1)
	{
		glVertexAttribPointer(colorLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myColor)));
		glEnableVertexAttribArray(colorLocation);
	}

	const GLint uvLocation = glGetAttribLocation(myShader->GetProgram(), "a_UVCoord");
	if (uvLocation != -1)
	{
		glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myUVCoordinates)));
		glEnableVertexAttribArray(uvLocation);
	}

	const GLuint program = myShader->GetProgram();
	glUseProgram(program);

	SetUniform2f(program, "u_ObjectScale", objectScale);
	SetUniform1f(program, "u_ObjectAngleRadians", objectAngle / 180.0f * Math::pi);
	SetUniform2f(program, "u_ObjectPosition", objectPos);
	SetUniform2f(program, "u_CameraTranslation", camPos * -1.0f);
	SetUniform2f(program, "u_ProjectionScale", projScale);

	glActiveTexture(GL_TEXTURE0 + 8);
	glBindTexture(GL_TEXTURE_2D, aTexture);
	const int texture = glGetUniformLocation(myShader->GetProgram(), "u_TextureSampler");

	glUniform1i(texture, 8);
	SetUniform2f(program, "u_UVScale", aUVscale);
	SetUniform2f(program, "u_UVOffset", aUVoffset);

	GLHelpers::CheckForGLErrors();

	glDrawArrays(myPrimitiveType, 0, myNumberOfVertices);

	GLHelpers::CheckForGLErrors();

	if (myIsDebug)
		DebugDraw(objectPos, objectAngle, objectScale, camPos, projScale);

	GLHelpers::CheckForGLErrors();
}

void Mesh::DrawCanvas(Vector2Float cameraPos, Vector2Float projectionScale, GLuint aTexture) const
{
	assert(myPrimitiveType != -1);
	assert(myNumberOfVertices != 0);
	assert(myShader);
	assert(myShader->GetProgram() != 0);

	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);

	GLint loc = glGetAttribLocation(myShader->GetProgram(), "a_Position");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myPosition)));
		glEnableVertexAttribArray(loc);
	}

	loc = glGetAttribLocation(myShader->GetProgram(), "a_Color");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myColor)));
		glEnableVertexAttribArray(loc);
	}

	loc = glGetAttribLocation(myShader->GetProgram(), "a_UVCoord");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myUVCoordinates)));
		glEnableVertexAttribArray(loc);
	}

	const GLuint shader = myShader->GetProgram();
	glUseProgram(shader);

	SetUniform2f(shader, "u_ObjectScale", 1);
	SetUniform1f(shader, "u_ObjectAngleRadians", 0 / 180.0f * Math::pi);
	SetUniform2f(shader, "u_ObjectPosition", Vector2Float(0.0f, 0.0f));
	SetUniform2f(shader, "u_CameraTranslation", cameraPos * -1);
	SetUniform2f(shader, "u_ProjectionScale", projectionScale);

	glActiveTexture(GL_TEXTURE0 + 8);
	glBindTexture(GL_TEXTURE_2D, aTexture);
	const GLuint texture = glGetUniformLocation(myShader->GetProgram(), "u_TextureSampler");

	glUniform1i(texture, 8);
	SetUniform2f(shader, "u_UVScale", Vector2Float(1.0f, 1.0f));
	SetUniform2f(shader, "u_UVOffset", Vector2Float(0.0f, 0.0f));

	GLHelpers::CheckForGLErrors();

	glDrawArrays(myPrimitiveType, 0, myNumberOfVertices);

	GLHelpers::CheckForGLErrors();

	if (myIsDebug)
		DebugDraw(Vector2Float(0.0f, 0.0f), 0 / 180.0f * Math::pi, 1, cameraPos, projectionScale);

	GLHelpers::CheckForGLErrors();
}
void Mesh::DebugDraw(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float camPos, Vector2Float projScale) const
{
	assert(myPrimitiveType != -1);
	assert(myNumberOfVertices != 0);
	assert(myDebugShader);
	assert(myDebugShader->GetProgram() != 0);

	// Bind buffer and set up attributes.
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);

	GLint loc = glGetAttribLocation(myDebugShader->GetProgram(), "a_Position");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myPosition)));
		glEnableVertexAttribArray(loc);
	}

	loc = glGetAttribLocation(myDebugShader->GetProgram(), "a_Color");
	if (loc != -1)
	{
		glVertexAttribPointer(loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myColor)));
		glEnableVertexAttribArray(loc);
	}
	// Set up shader.
	const GLuint shader = myDebugShader->GetProgram();
	glUseProgram(shader);

	// Set up uniforms.
	SetUniform2f(shader, "u_ObjectScale", objectScale);
	SetUniform1f(shader, "u_ObjectAngleRadians", objectAngle / 180.0f * Math::pi);
	SetUniform2f(shader, "u_ObjectPosition", objectPos);
	SetUniform2f(shader, "u_CameraTranslation", camPos * -1);
	SetUniform2f(shader, "u_ProjectionScale", projScale);

	glDrawArrays(GL_LINE_LOOP, 0, myNumberOfVertices);
}

void Mesh::GenerateTriangle()
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
	assert(myVBOIdentifier == 0);

	// Vertex info for a diamond.
	const VertexFormat vertexAttributes[] = {
		VertexFormat(Vector2Float(0.0f,  1.0f), Color(255, 255, 255, 255), Vector2Float(0.5f, 1.0f)),
		VertexFormat(Vector2Float(-0.5f, -1.0f), Color(255, 255, 255, 255), Vector2Float(0.25f, 0.0f)),
		VertexFormat(Vector2Float(0.5f, -1.0f), Color(255, 255, 255, 255), Vector2Float(0.75f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLES;
	myNumberOfVertices = 3;

	// Check for errors.
	GLHelpers::CheckForGLErrors();
}

void Mesh::GenerateCircle()
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
	assert(myVBOIdentifier == 0);

	// Vertex position info for a diamond.
	const VertexFormat vertexAttributes[] = {
		VertexFormat(Vector2Float(0.0f,  1.0f), Color(0, 255,   0, 255), Vector2Float(0.5f, 1.0f)),
		VertexFormat(Vector2Float(-1.0f,  0.0f), Color(0, 255,   0, 255), Vector2Float(0.0f, 0.5f)),
		VertexFormat(Vector2Float(1.0f,  0.0f), Color(0, 255,   0, 255), Vector2Float(1.0f, 0.5f)),
		VertexFormat(Vector2Float(0.0f, -1.0f), Color(0, 255,   0, 255), Vector2Float(0.5f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_STRIP;
	myNumberOfVertices = 4;

	// Check for errors.
	GLHelpers::CheckForGLErrors();
}
void Mesh::GeneratePolygon(float radius, int vertices, char r, char g, char b, char a)
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated
	assert(myVBOIdentifier == 0);

	myRadius = radius;
	myWidth = radius * 2;
	myHeight = radius * 2;

	std::vector<float> m_Circle;

	float x = 0.0f;
	float y = 0.0f;

	m_Circle.push_back(x);
	m_Circle.push_back(y);

	for (int i = 1; i <= vertices; i++)
	{
		x = -(radius * std::cos(i * (2.0f * Math::pi / static_cast<float>(vertices))));
		y = -(radius * std::sin(i * (2.0f * Math::pi / static_cast<float>(vertices))));

		m_Circle.push_back(x);
		m_Circle.push_back(y);
		m_Circle.push_back(r);
		m_Circle.push_back(g);
		m_Circle.push_back(b);
		m_Circle.push_back(a);
	}

	x = -(radius * std::cos(1.0f * (2.0f * Math::pi / static_cast<float>(vertices))));
	y = -(radius * std::sin(1.0f * (2.0f * Math::pi / static_cast<float>(vertices))));

	m_Circle.push_back(x);
	m_Circle.push_back(y);
	m_Circle.push_back(r);
	m_Circle.push_back(g);
	m_Circle.push_back(b);
	m_Circle.push_back(a);

	// Generate and fill buffer with our attributes.
	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(m_Circle[0]) * m_Circle.size()), &m_Circle.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_FAN;
	myNumberOfVertices = vertices + 2;

	// Check for errors.
	GLHelpers::CheckForGLErrors();
}

void Mesh::GenerateFrameMesh()
{
	assert(myVBOIdentifier == 0);

	const VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  0.0f), Color(0, 255,   0, 255), Vector2Float(0.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f, 1.0f), Color(0, 255,   0, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  1.0f), Color(0, 255,   0, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f, 0.0f), Color(0, 255,   0, 255), Vector2Float(1.0f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_FAN;
	myNumberOfVertices = 4;
}

void Mesh::GenerateTileMesh()
{
	assert(myVBOIdentifier == 0);

	const VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f,  1.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  1.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_FAN;
	myNumberOfVertices = 4;
}

void Mesh::GenerateWildTileMesh()
{
	assert(myVBOIdentifier == 0);

	const VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  0.0f), Color(255, 0, 0, 255), Vector2Float(0.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f,  1.0f), Color(255, 0, 0, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  1.0f), Color(255, 0, 0, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  0.0f), Color(255, 0, 0, 255), Vector2Float(1.0f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_LINE_LOOP;
	myNumberOfVertices = 4;
}

void Mesh::GenerateTextureMesh(Vector2Float aSize)
{
	assert(myVBOIdentifier == 0);

	const VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f,  aSize.myY), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(aSize.myX,  aSize.myY), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(aSize.myX,  0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
	};

	// Gen and fill buffer with our attributes.
	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_FAN;
	myNumberOfVertices = 4;
}

void Mesh::GenerateDebugMesh()
{
	assert(myVBOIdentifier == 0);

	const VertexFormat vertexAttributes[] = {
	VertexFormat(Vector2Float(0.0f,  1.0f), Color(255, 255,   255, 255), Vector2Float(0.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  1.0f), Color(255, 255,   255, 255), Vector2Float(1.0f, 1.0f)),
	VertexFormat(Vector2Float(1.0f,  0.0f), Color(255, 255,   255, 255), Vector2Float(1.0f, 0.0f)),
	VertexFormat(Vector2Float(0.0f, 0.0f), Color(255, 255,   255, 255), Vector2Float(0.0f, 0.0f)),
	};

	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myNumberOfVertices = 4;
}

void Mesh::GenterateCanvasMesh(int aSize)
{
    assert(myVBOIdentifier == 0);

    glGenBuffers(1, &myVBOIdentifier);
    glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * aSize, &myCanvasVertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_STRIP;
    myNumberOfVertices = aSize;
}

