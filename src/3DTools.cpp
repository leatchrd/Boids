#include "3DTools.hpp"
#include <vector>
#include "p6/p6.h"

std::vector<Vertex2DTex> createCubeVertices()
{
    // create cube
    std::vector<Vertex2DTex> cube;

    // create all 6 walls
    // std::vector<Vertex2DTex> front;
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});

    // std::vector<Vertex2DTex> back;
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});

    // // std::vector<Vertex2DTex> left;
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});

    // // std::vector<Vertex2DTex> right;
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});

    // // std::vector<Vertex2DTex> top;
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, 1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});

    // // std::vector<Vertex2DTex> bottom;
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, 1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    cube.push_back(Vertex2DTex{{-1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    cube.push_back(Vertex2DTex{{1.f, -1.f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});

    return cube;
}
