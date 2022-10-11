#include "Object.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

RendererObject::RendererObject(std::string meshFilename, std::string imageFilename)
{
    orientation = glm::mat4(1.0);
    position = glm::translate(glm::vec3(0.0, 0.0, 0.0));
    world = glm::mat4(1.0);
    vertexPositions = loadOBJMesh(meshFilename, vertexPositionsSize, textCoord, textCoordSize);
    imageData = stbi_load(imageFilename.c_str(), &imageWidth, &imageHeight, &bpp, 0);
    setUpRenderingPipelineData();
}

RendererObject::~RendererObject()
{
    glDeleteTextures(1, &texture);

    delete[] vertexPositions;
    delete[] textCoord;
}

void RendererObject::setUpRenderingPipelineData()
{

    GLuint vbo;
    GLuint textureCoordinatesName;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTextureUnit(GL_TEXTURE0, texture);
    glTextureStorage2D(texture, 0, GL_RGB8, imageWidth, imageHeight);
    glTexImage2D(GL_TEXTURE_2D,0, GL_RGB8, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (const void*)imageData);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexPositionsSize, vertexPositions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 8, (void*)0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &textureCoordinatesName);
    glBindBuffer(GL_ARRAY_BUFFER, textureCoordinatesName);
    glBufferData(GL_ARRAY_BUFFER, textCoordSize, textCoord, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 12, (void*)12);
    glEnableVertexAttribArray(1);
}

void RendererObject::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

void RendererObject::update()
{
    world = position * orientation;
}