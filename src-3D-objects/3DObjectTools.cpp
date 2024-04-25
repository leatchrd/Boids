#include "3DObjectTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "loader.h"
#include "p6/p6.h"

std::vector<Vertex2DTex> createCubeVertices()
{
    // create cube
    std::vector<Vertex2DTex> cube;
    // back wall
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});  // 0
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});   // 1
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});  // 2
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});  // 0
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}}); // 3
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});  // 2
    // left wall
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});   // 4
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});  // 0
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}}); // 3
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});   // 4
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});  // 5
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}}); // 3
    // right wall
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});   // 6
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});  // 1
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}}); // 2
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});   // 6
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});  // 7
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}}); // 2
    // top wall
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});  // 4
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});   // 6
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});  // 1
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});  // 4
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}}); // 0
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});  // 1
    // bottom wall
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});  // 5
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});   // 7
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});  // 2
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});  // 5
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}}); // 3
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});  // 2
    // front wall
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});  // 4
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});   // 6
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});  // 7
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});  // 4
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}}); // 5
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});  // 7

    return cube;
}

std::vector<uint32_t> getCubeIndexArray()
{
    return std::vector<uint32_t>{0, 1, 2, 0, 3, 2, 4, 0, 3, 4, 5, 3, 6, 1, 2, 6, 7, 2, 4, 6, 1, 4, 0, 1, 5, 7, 2, 5, 3, 2, 4, 6, 7, 4, 5, 7};
}

// for OBJ mesh
void drawMesh(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, glm::vec3 position, float angle, glm::vec3 axis, float scale, const std::vector<vertex>& vertices)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(camMVMatrix, position);
    MVMatrix               = glm::rotate(MVMatrix, angle, axis);
    MVMatrix               = glm::scale(MVMatrix, glm::vec3{scale});
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    // fill matrices with uniform location
    glUniformMatrix4fv(uniMVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uniMV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uniNormal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    // draw
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

// for handmade OpenGL mesh (using IBO)
void drawMesh(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, glm::vec3 position, float angle, glm::vec3 axis, float scale, const std::vector<uint32_t>& vertices)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(camMVMatrix, position);
    MVMatrix               = glm::rotate(MVMatrix, angle, axis);
    MVMatrix               = glm::scale(MVMatrix, glm::vec3{scale});
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    // fill matrices with uniform location
    glUniformMatrix4fv(uniMVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uniMV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uniNormal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    // draw
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
