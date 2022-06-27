#include "Mesh.h"

#include <cassert>
#include <cmath>

#include "GL/GLHelpers.h"
#include "Math/MathConstants.h"
#include "Utility/ShaderProgram.h"

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

void Mesh::Draw(Vector2Float anObjectPos, float anOobjectAngle, Vector2Float anObjectScale, Vector2Float aCameraPos, Vector2Float aProjectionScale, unsigned int aTexture, Vector2Float aUVscale, Vector2Float aUVoffset) const
{
	assert(myPrimitiveType != static_cast<GLenum>(-1));
	assert(myNumberOfVertices != 0);
	assert(myShader);
	assert(myShader->GetProgram() != 0);

	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);

	const GLuint shaderProgram = myShader->GetProgram();
	const GLint positionLocation = GLHelpers::GetAttributeLocation(shaderProgram, "a_Position");
	if (positionLocation != -1)
	{
		glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myPosition)));
		glEnableVertexAttribArray(positionLocation);
	}

	const GLint colorLocation = GLHelpers::GetAttributeLocation(shaderProgram, "a_Color");
	if (colorLocation != -1)
	{
		glVertexAttribPointer(colorLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myColor)));
		glEnableVertexAttribArray(colorLocation);
	}

	const GLint uvLocation = GLHelpers::GetAttributeLocation(shaderProgram, "a_UVCoord");
	if (uvLocation != -1)
	{
		glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myUVCoordinates)));
		glEnableVertexAttribArray(uvLocation);
	}

	glUseProgram(shaderProgram);

	GLHelpers::SetUniform2f(shaderProgram, "u_ObjectScale", anObjectScale);
	GLHelpers::SetUniform1f(shaderProgram, "u_ObjectAngleRadians", anOobjectAngle / 180.0f * Math::pi);
	GLHelpers::SetUniform2f(shaderProgram, "u_ObjectPosition", anObjectPos);
	GLHelpers::SetUniform2f(shaderProgram, "u_CameraTranslation", aCameraPos * -1.0f);
	GLHelpers::SetUniform2f(shaderProgram, "u_ProjectionScale", aProjectionScale);

	glActiveTexture(GL_TEXTURE0 + 8);
	glBindTexture(GL_TEXTURE_2D, aTexture);

	GLHelpers::SetUniform1i(shaderProgram, "u_TextureSampler", 8);
	GLHelpers::SetUniform2f(shaderProgram, "u_UVScale", aUVscale);
	GLHelpers::SetUniform2f(shaderProgram, "u_UVOffset", aUVoffset);

	GLHelpers::CheckForGLErrors();

	glDrawArrays(myPrimitiveType, 0, myNumberOfVertices);

	GLHelpers::CheckForGLErrors();

	if (myIsDebug)
		DebugDraw(anObjectPos, anOobjectAngle, anObjectScale, aCameraPos, aProjectionScale);

	GLHelpers::CheckForGLErrors();
}

void Mesh::DrawCanvas(Vector2Float aCameraPos, Vector2Float aProjectionScale, unsigned int aTexture) const
{
	assert(myPrimitiveType != static_cast<GLenum>(-1));
	assert(myNumberOfVertices != 0);
	assert(myShader);
	assert(myShader->GetProgram() != 0);

	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);

	const GLuint shaderProgram = myShader->GetProgram();
	const GLint positionLocation = GLHelpers::GetAttributeLocation(shaderProgram, "a_Position");
	if (positionLocation != -1)
	{
		glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myPosition)));
		glEnableVertexAttribArray(positionLocation);
	}

	const GLint colorLocation = GLHelpers::GetAttributeLocation(shaderProgram, "a_Color");
	if (colorLocation != -1)
	{
		glVertexAttribPointer(colorLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myColor)));
		glEnableVertexAttribArray(colorLocation);
	}

	const GLint uvLocation = GLHelpers::GetAttributeLocation(shaderProgram, "a_UVCoord");
	if (uvLocation != -1)
	{
		glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myUVCoordinates)));
		glEnableVertexAttribArray(uvLocation);
	}

	glUseProgram(shaderProgram);

	GLHelpers::SetUniform2f(shaderProgram, "u_ObjectScale", 1.0f);
	GLHelpers::SetUniform1f(shaderProgram, "u_ObjectAngleRadians", 0 / 180.0f * Math::pi);
	GLHelpers::SetUniform2f(shaderProgram, "u_ObjectPosition", Vector2Float(0.0f, 0.0f));
	GLHelpers::SetUniform2f(shaderProgram, "u_CameraTranslation", aCameraPos * -1);
	GLHelpers::SetUniform2f(shaderProgram, "u_ProjectionScale", aProjectionScale);

	glActiveTexture(GL_TEXTURE0 + 8);
	glBindTexture(GL_TEXTURE_2D, aTexture);

	GLHelpers::SetUniform1i(shaderProgram, "u_TextureSampler", 8);
	GLHelpers::SetUniform2f(shaderProgram, "u_UVScale", Vector2Float(1.0f, 1.0f));
	GLHelpers::SetUniform2f(shaderProgram, "u_UVOffset", Vector2Float(0.0f, 0.0f));

	GLHelpers::CheckForGLErrors();

	glDrawArrays(myPrimitiveType, 0, myNumberOfVertices);

	GLHelpers::CheckForGLErrors();

	if (myIsDebug)
		DebugDraw(Vector2Float(0.0f, 0.0f), 0 / 180.0f * Math::pi, 1, aCameraPos, aProjectionScale);

	GLHelpers::CheckForGLErrors();
}
void Mesh::DebugDraw(Vector2Float anObjectPos, float anObjectAngle, Vector2Float anObjectScale, Vector2Float aCameraPos, Vector2Float aProjectionScale) const
{
	assert(myPrimitiveType != static_cast<GLenum>(-1));
	assert(myNumberOfVertices != 0);
	assert(myDebugShader);
	assert(myDebugShader->GetProgram() != 0);

	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);

	const GLuint shaderProgram = myDebugShader->GetProgram();
	const GLint positionLocation = GLHelpers::GetAttributeLocation(shaderProgram, "a_Position");
	if (positionLocation != -1)
	{
		glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myPosition)));
		glEnableVertexAttribArray(positionLocation);
	}

	const GLint colorLocation = GLHelpers::GetAttributeLocation(shaderProgram, "a_Color");
	if (colorLocation != -1)
	{
		glVertexAttribPointer(colorLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), reinterpret_cast<GLvoid*>(offsetof(VertexFormat, myColor)));
		glEnableVertexAttribArray(colorLocation);
	}

	glUseProgram(shaderProgram);

	GLHelpers::SetUniform2f(shaderProgram, "u_ObjectScale", anObjectScale);
	GLHelpers::SetUniform1f(shaderProgram, "u_ObjectAngleRadians", anObjectAngle / 180.0f * Math::pi);
	GLHelpers::SetUniform2f(shaderProgram, "u_ObjectPosition", anObjectPos);
	GLHelpers::SetUniform2f(shaderProgram, "u_CameraTranslation", aCameraPos * -1);
	GLHelpers::SetUniform2f(shaderProgram, "u_ProjectionScale", aProjectionScale);

	glDrawArrays(GL_LINE_LOOP, 0, myNumberOfVertices);
}

void Mesh::GenerateTriangle()
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
	assert(myVBOIdentifier == 0);

	// Vertex info for a diamond.
	const VertexFormat vertexAttributes[] =
	{
		VertexFormat(Vector2Float(0.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(0.5f, 1.0f)),
		VertexFormat(Vector2Float(-0.5f, -1.0f), Color(255, 255, 255, 255), Vector2Float(0.25f, 0.0f)),
		VertexFormat(Vector2Float(0.5f, -1.0f), Color(255, 255, 255, 255), Vector2Float(0.75f, 0.0f)),
	};

	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLES;
	myNumberOfVertices = 3;

	GLHelpers::CheckForGLErrors();
}

void Mesh::GenerateCircle()
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
	assert(myVBOIdentifier == 0);

	// Vertex position info for a diamond.
	const VertexFormat vertexAttributes[] = {
		VertexFormat(Vector2Float(0.0f, 1.0f), Color(0, 255, 0, 255), Vector2Float(0.5f, 1.0f)),
		VertexFormat(Vector2Float(-1.0f, 0.0f), Color(0, 255, 0, 255), Vector2Float(0.0f, 0.5f)),
		VertexFormat(Vector2Float(1.0f, 0.0f), Color(0, 255, 0, 255), Vector2Float(1.0f, 0.5f)),
		VertexFormat(Vector2Float(0.0f, -1.0f), Color(0, 255, 0, 255), Vector2Float(0.5f, 0.0f)),
	};

	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_STRIP;
	myNumberOfVertices = 4;

	GLHelpers::CheckForGLErrors();
}
void Mesh::GeneratePolygon(float aRadius, int aVertices, char aRed, char aGreen, char aBlue, char anAlpha)
{
	// ATM this can only be called once, so we assert if it's called again with a VBO already allocated
	assert(myVBOIdentifier == 0);

	myRadius = aRadius;
	myWidth = aRadius * 2;
	myHeight = aRadius * 2;

	std::vector<float> m_Circle;

	float x = 0.0f;
	float y = 0.0f;

	m_Circle.push_back(x);
	m_Circle.push_back(y);

	for (int i = 1; i <= aVertices; i++)
	{
		x = -(aRadius * std::cos(static_cast<float>(i) * (2.0f * Math::pi / static_cast<float>(aVertices))));
		y = -(aRadius * std::sin(static_cast<float>(i) * (2.0f * Math::pi / static_cast<float>(aVertices))));

		m_Circle.push_back(x);
		m_Circle.push_back(y);
		m_Circle.push_back(aRed);
		m_Circle.push_back(aGreen);
		m_Circle.push_back(aBlue);
		m_Circle.push_back(anAlpha);
	}

	x = -(aRadius * std::cos(1.0f * (2.0f * Math::pi / static_cast<float>(aVertices))));
	y = -(aRadius * std::sin(1.0f * (2.0f * Math::pi / static_cast<float>(aVertices))));

	m_Circle.push_back(x);
	m_Circle.push_back(y);
	m_Circle.push_back(aRed);
	m_Circle.push_back(aGreen);
	m_Circle.push_back(aBlue);
	m_Circle.push_back(anAlpha);

	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(m_Circle[0]) * m_Circle.size()), &m_Circle.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_FAN;
	myNumberOfVertices = aVertices + 2;

	GLHelpers::CheckForGLErrors();
}

void Mesh::GenerateFrameMesh()
{
	assert(myVBOIdentifier == 0);

	const VertexFormat vertexAttributes[] = {
		VertexFormat(Vector2Float(0.0f, 0.0f), Color(0, 255, 0, 255), Vector2Float(0.0f, 0.0f)),
		VertexFormat(Vector2Float(0.0f, 1.0f), Color(0, 255, 0, 255), Vector2Float(0.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 1.0f), Color(0, 255, 0, 255), Vector2Float(1.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 0.0f), Color(0, 255, 0, 255), Vector2Float(1.0f, 0.0f)),
	};

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
		VertexFormat(Vector2Float(0.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
		VertexFormat(Vector2Float(0.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
	};

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
		VertexFormat(Vector2Float(0.0f, 0.0f), Color(255, 0, 0, 255), Vector2Float(0.0f, 0.0f)),
		VertexFormat(Vector2Float(0.0f, 1.0f), Color(255, 0, 0, 255), Vector2Float(0.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 1.0f), Color(255, 0, 0, 255), Vector2Float(1.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 0.0f), Color(255, 0, 0, 255), Vector2Float(1.0f, 0.0f)),
	};

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
		VertexFormat(Vector2Float(0.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
		VertexFormat(Vector2Float(0.0f, aSize.myY), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f)),
		VertexFormat(Vector2Float(aSize.myX, aSize.myY), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f)),
		VertexFormat(Vector2Float(aSize.myX, 0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
	};

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
		VertexFormat(Vector2Float(0.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
		VertexFormat(Vector2Float(0.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
	};

	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myNumberOfVertices = 4;
}

void Mesh::GenterateCanvasMesh()
{
	assert(myVBOIdentifier == 0);

	glGenBuffers(1, &myVBOIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOIdentifier);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(VertexFormat) * myCanvasVertices.size()), &myCanvasVertices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	myPrimitiveType = GL_TRIANGLE_STRIP;
	myNumberOfVertices = static_cast<int>(myCanvasVertices.size());
}
