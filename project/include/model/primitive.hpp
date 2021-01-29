#pragma once

#include <vector>

#include "opengl_all.hpp"

namespace game_engine {

using ModelData = std::vector<float>;

namespace primitive {

ModelData cube(float size = 1.0);
ModelData cuboid(float width, float height, float depth);
ModelData cylinder(float diameter, float height, unsigned int sides);
ModelData sphere(float diameter, unsigned int sides);
ModelData cone(float diameter, float height, unsigned int sides);
ModelData plane(float width, float height, unsigned int w_segments, unsigned int h_segments);
ModelData cubemap();

void invert_normals(ModelData &shape);

}  // namespace primitive
}  // namespace game_engine
