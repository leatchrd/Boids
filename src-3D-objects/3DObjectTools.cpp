#include "3DObjectTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "loader.h"
#include "p6/p6.h"

std::vector<Vertex2DTex> createCubeVertices()
{
    // create cube
    std::vector<Vertex2DTex> cube;
    // front wall
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    // back wall
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    // left wall
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    // right wall
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    // top wall
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    // bottom wall
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});

    return cube;
}

// for OBJ mesh
void drawMesh(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, glm::vec3 position, float angle, glm::vec3 axis, float scale, const std::vector<vertex>& vertices)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(camMVMatrix, position);
    MVMatrix               = glm::rotate(MVMatrix, angle, axis);
    MVMatrix               = glm::scale(MVMatrix, glm::vec3{scale, scale, scale});
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    // fill matrices with uniform location
    glUniformMatrix4fv(uni_MVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uni_MV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uni_Normal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    // draw
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

// for handmade OpenGL mesh
void drawMesh(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, glm::vec3 position, float angle, glm::vec3 axis, float scale, const std::vector<Vertex2DTex>& vertices)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(camMVMatrix, position);
    MVMatrix               = glm::rotate(MVMatrix, angle, axis);
    MVMatrix               = glm::scale(MVMatrix, glm::vec3{scale});
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    // fill matrices with uniform location
    glUniformMatrix4fv(uni_MVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uni_MV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uni_Normal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    // draw
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
