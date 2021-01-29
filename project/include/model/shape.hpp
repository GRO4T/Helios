#pragma once

#include <vector>

#include "opengl_all.hpp"

using Shape = std::vector<GLfloat>;

namespace game_engine {
Shape cube(GLfloat size = 1.0);
Shape cuboid(GLfloat width, GLfloat height, GLfloat depth);
Shape cylinder(GLfloat diameter, GLfloat height, unsigned int sides);
Shape sphere(GLfloat diameter, unsigned int sides);
Shape cone(GLfloat diameter, GLfloat height, unsigned int sides);
Shape plane(GLfloat width, GLfloat height, unsigned int w_segments, unsigned int h_segments);
Shape cubemap();

void invert_normals(Shape &shape);
}  // namespace game_engine
