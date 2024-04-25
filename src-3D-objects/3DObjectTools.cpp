#include "3DObjectTools.hpp"
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
