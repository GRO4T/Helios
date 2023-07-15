#pragma once

#include <vector>

#include "model/Mesh.hpp"
#include "opengl_all.hpp"

namespace helios {

namespace primitive_mesh {

std::vector<Vertex> cube(float size = 1.0);
std::vector<Vertex> cuboid(float width, float height, float depth);
std::vector<Vertex> cylinder(float diameter, float height, unsigned int sides);
std::vector<Vertex> sphere(float diameter, unsigned int sides);
std::vector<Vertex> cone(float diameter, float height, unsigned int sides);
std::vector<Vertex> plane(float width, float height, unsigned int w_segments,
                          unsigned int h_segments);

}  // namespace primitive
}  // namespace helios
