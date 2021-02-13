#include "model/primitive_mesh.hpp"

namespace game_engine {
namespace primitive {

static const double PI = 3.14159265;

// clang-format off

std::vector<Vertex> cube(float s) { return cuboid(s, s, s); }

std::vector<Vertex> cuboid(float w, float h, float d) {
    static std::vector<glm::vec3> normals{{0, 0, 1},  {1, 0, 0}, {0, 0, -1},
                                          {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}};
    static std::vector<glm::vec2> uvs{{0, 0}, {0, 1}, {1, 0},
                                      {1, 0}, {0, 1}, {1, 1}};
    static std::vector<glm::vec3> positions{
        {w * -0.5f, h *  0.5f, d *  0.5f},
        {w * -0.5f, h * -0.5f, d *  0.5f},
        {w *  0.5f, h *  0.5f, d *  0.5f},
        {w *  0.5f, h *  0.5f, d *  0.5f},
        {w * -0.5f, h * -0.5f, d *  0.5f},
        {w *  0.5f, h * -0.5f, d *  0.5f},

        {w *  0.5f, h *  0.5f, d *  0.5f},
        {w *  0.5f, h * -0.5f, d *  0.5f},
        {w *  0.5f, h *  0.5f, d * -0.5f},
        {w *  0.5f, h *  0.5f, d * -0.5f},
        {w *  0.5f, h * -0.5f, d *  0.5f},
        {w *  0.5f, h * -0.5f, d * -0.5f},

        {w *  0.5f, h *  0.5f, d * -0.5f},
        {w *  0.5f, h * -0.5f, d * -0.5f},
        {w * -0.5f, h *  0.5f, d * -0.5f},
        {w * -0.5f, h *  0.5f, d * -0.5f},
        {w *  0.5f, h * -0.5f, d * -0.5f},
        {w * -0.5f, h * -0.5f, d * -0.5f},

        {w * -0.5f, h *  0.5f, d * -0.5f},
        {w * -0.5f, h * -0.5f, d * -0.5f},
        {w * -0.5f, h *  0.5f, d *  0.5f},
        {w * -0.5f, h *  0.5f, d *  0.5f},
        {w * -0.5f, h * -0.5f, d * -0.5f},
        {w * -0.5f, h * -0.5f, d *  0.5f},

        {w * -0.5f, h *  0.5f, d * -0.5f},
        {w * -0.5f, h *  0.5f, d *  0.5f},
        {w *  0.5f, h *  0.5f, d * -0.5f},
        {w *  0.5f, h *  0.5f, d * -0.5f},
        {w * -0.5f, h *  0.5f, d *  0.5f},
        {w *  0.5f, h *  0.5f, d *  0.5f},

        {w * -0.5f, h * -0.5f, d *  0.5f},
        {w * -0.5f, h * -0.5f, d * -0.5f},
        {w *  0.5f, h * -0.5f, d *  0.5f},
        {w *  0.5f, h * -0.5f, d *  0.5f},
        {w * -0.5f, h * -0.5f, d * -0.5f},
        {w *  0.5f, h * -0.5f, d * -0.5f}
    };
    std::vector<Vertex> vertices;
    vertices.reserve(36);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            Vertex vertex;
            vertex.position = positions[6*i + j];
            vertex.uv = uvs[j];
            vertex.normal = normals[i];
            vertices.push_back(vertex);
        }
    }
    return vertices;
}
/*
ModelData cylinder(float diameter, float height, unsigned int sides) {
    if (sides < 3) sides = 3;
    ModelData vertices;
    vertices.reserve(8 * 12 * sides);
    for (unsigned int i = 0; i < sides; ++i) {
        float r = i / static_cast<float>(sides);
        float nr = (i + 1) / static_cast<float>(sides);
        float norm_x = static_cast<float>(sin(r * 2 * PI));
        float nnorm_x = static_cast<float>(sin(nr * 2 * PI));
        float x = 0.5f * diameter * norm_x;
        float nx = 0.5f * diameter * nnorm_x;
        float ly = -0.5f * height;
        float hy = 0.5f * height;
        float norm_z = static_cast<float>(cos(r * 2 * PI));
        float nnorm_z = static_cast<float>(cos(nr * 2 * PI));
        float z = 0.5f * diameter * norm_z;
        float nz = 0.5f * diameter * nnorm_z;

        float u = r;
        float nu = nr;
        float tu = 0.25f + 0.25f * static_cast<float>(sin(2 * PI * r));
        float ntu = 0.25f + 0.25f * static_cast<float>(sin(2 * PI * nr));
        float bu = 0.5f + tu;
        float nbu = 0.5f + ntu;
        float v = 0.25f + 0.25f * static_cast<float>(cos(2 * PI * r));
        float nv = 0.25f + 0.25f * static_cast<float>(cos(2 * PI * nr));

        float slice[8 * 12] = {
            // side rectangle
            x, hy,   z,         u,  0.5f,      norm_x,  0.0f,  norm_z,
            x, ly,   z,         u,  1.0f,      norm_x,  0.0f,  norm_z,
            nx, hy,  nz,        nu,  0.5f,     nnorm_x,  0.0f, nnorm_z,
            nx, hy,  nz,        nu,  0.5f,     nnorm_x,  0.0f, nnorm_z,
            x, ly,   z,         u,  1.0f,      norm_x,  0.0f,  norm_z,
            nx, ly,  nz,        nu,  1.0f,     nnorm_x,  0.0f, nnorm_z,
            // top triangle
            0.0f, hy, 0.0f,    0.25f, 0.25f,        0.0f,  1.0f,    0.0f,
            x, hy,    z,       tu,     v,        0.0f,  1.0f,    0.0f,
            nx, hy,   nz,      ntu,    nv,        0.0f,  1.0f,    0.0f,
            // bottom triangle
            x, ly,    z,       bu,     v,        0.0f, -1.0f,    0.0f,
            0.0f, ly, 0.0f,    0.75f, 0.25f,        0.0f, -1.0f,    0.0f,
            nx, ly,   nz,      nbu,    nv,        0.0f, -1.0f,    0.0f,
        };
        vertices.insert(vertices.end(), slice, slice + 8 * 12);
    }
    return vertices;
}
 */

std::vector<Vertex> sphere(float diameter, unsigned int sides) {
    if (sides < 3) sides = 3;
    std::vector<Vertex> vertices;
    vertices.reserve(6 * sides * sides);
    for (unsigned int i = 0; i < sides; ++i) {
        float r = i / static_cast<float>(sides);
        float nr = (i + 1) / static_cast<float>(sides);
        for (unsigned int u = 0; u < sides; ++u) {
            float d = u / static_cast<float>(sides);
            float nd = (u + 1) / static_cast<float>(sides);
            float hrad = 0.5f * diameter * static_cast<float>(sin(d * PI));
            float lrad = static_cast<float>(0.5) * diameter * static_cast<float>(sin(nd * PI));
            float hx = hrad * static_cast<float>(sin(r * 2 * PI));
            float lx = lrad * static_cast<float>(sin(r * 2 * PI));
            float nhx = hrad * static_cast<float>(sin(nr * 2 * PI));
            float nlx = lrad * static_cast<float>(sin(nr * 2 * PI));
            float y = 0.5f * diameter * static_cast<float>(cos(d * PI));
            float ny = 0.5f * diameter * static_cast<float>(cos(nd * PI));
            float hz = hrad * static_cast<float>(cos(r * 2 * PI));
            float lz = lrad * static_cast<float>(cos(r * 2 * PI));
            float nhz = hrad * static_cast<float>(cos(nr * 2 * PI));
            float nlz = lrad * static_cast<float>(cos(nr * 2 * PI));

            float lny = static_cast<float>(cos(d * PI));
            float nlny =  static_cast<float>(cos(nd * PI));
            float xzs = static_cast<float>(sin(d * PI));
            float nxzs = static_cast<float>(sin(nd * PI));
            float lnx = static_cast<float>(sin(r * 2 * PI));
            float nlnx = static_cast<float>(sin(nr * 2 * PI));
            float lnz = static_cast<float>(cos(r * 2 * PI));
            float nlnz = static_cast<float>(cos(nr * 2 * PI));

            // clang-format on
            Vertex slice[6] = {
                {{hx, y, hz}, {lnx * xzs, lny, lnz * xzs}, {r, d}},
                {{lx, ny, lz}, {lnx * nxzs, nlny, lnz * nxzs}, {r, nd}},
                {{nhx, y, nhz}, {nlnx * xzs, lny, nlnz * xzs}, {nr, d}},
                {{nhx, y, nhz}, {nlnx * xzs, lny, nlnz * xzs}, {nr, d}},
                {{lx, ny, lz}, {lnx * nxzs, nlny, lnz * nxzs}, {r, nd}},
                {{nlx, ny, nlz}, {nlnx * nxzs, nlny, nlnz * nxzs}, {nr, nd}}};
            vertices.insert(vertices.end(), slice, slice + 6);
            // clang-format off
        }
    }
    return vertices;
}
/*

ModelData cone(float diameter, float height, unsigned int sides) {
    if (sides < 3) sides = 3;
    ModelData vertices;

    float clen = static_cast<float>(sqrt(diameter * diameter / 4.0 + height * height));
    float lny = static_cast<float>((diameter / 2.0) / clen);
    float xzs = static_cast<float>(height / clen);

    vertices.reserve(8 * 6 * sides);
    for (unsigned int i = 0; i < sides; ++i) {
        float r = i / static_cast<float>(sides);
        float nr = (i + 1) / static_cast<float>(sides);
        float norm_x = static_cast<float>(sin(r * 2 * PI));
        float nnorm_x = static_cast<float>(sin(nr * 2 * PI));
        float x = 0.5f * diameter * norm_x;
        float nx = 0.5f * diameter * nnorm_x;
        float ly = -0.5f * height;
        float hy = 0.5f * height;
        float norm_z = static_cast<float>(cos(r * 2 * PI));
        float nnorm_z = static_cast<float>(cos(nr * 2 * PI));
        float z = 0.5f * diameter * norm_z;
        float nz = 0.5f * diameter * nnorm_z;

        float u = 0.5f + 0.25f * static_cast<float>(sin(2 * PI * r));
        float nu = 0.5f + 0.25f * static_cast<float>(sin(2 * PI * nr));
        float tv = 0.25f + 0.25f * static_cast<float>(cos(2 * PI * r));
        float ntv = 0.25f + 0.25f * static_cast<float>(cos(2 * PI * nr));
        float bv = 0.5f + tv;
        float nbv = 0.5f + ntv;

        float lnx = static_cast<float>(sin(r * 2 * PI));
        float mlnx = static_cast<float>(sin(((r + nr) / 2.0f) * 2 * PI));
        float nlnx = static_cast<float>(sin(nr * 2 * PI));
        float lnz = static_cast<float>(cos(r * 2 * PI));
        float mlnz = static_cast<float>(cos(((r + nr) / 2.0f) * 2 * PI));
        float nlnz = static_cast<float>(cos(nr * 2 * PI));

        float slice[8 * 6] = {
            0.0f, hy, 0.0f,    0.5f, 0.25f,    mlnx * xzs,   lny, mlnz * xzs,
            x, ly,    z,       u,    tv,     lnx * xzs,   lny,  lnz * xzs,
            nx, ly,   nz,      nu,   ntv,    nlnx * xzs,   lny, nlnz * xzs,

            x, ly,    z,       u,    bv,          0.0f, -1.0f,       0.0f,
            0.0f, ly, 0.0f,    0.5f, 0.75f,          0.0f, -1.0f,       0.0f,
            nx, ly,   nz,      nu,   nbv,          0.0f, -1.0f,       0.0f,
        };
        vertices.insert(vertices.end(), slice, slice + 8 * 6);
    }
    return vertices;
}
 */

std::vector<Vertex> plane(float w, float h, unsigned int w_segments, unsigned int h_segments) {
    if (w_segments < 1) w_segments = 1;
    if (h_segments < 1) h_segments = 1;
    std::vector<Vertex> vertices;
    vertices.reserve(6 * w_segments * h_segments);
    for (unsigned int i = 0; i < w_segments; ++i) {
        for (unsigned int u = 0; u < h_segments; ++u) {
            float x = i / static_cast<float>(w_segments);
            float nx = (i + 1) / static_cast<float>(w_segments);
            float y = u / static_cast<float>(h_segments);
            float ny = (u + 1) / static_cast<float>(h_segments);
            x = (-1.0f + 2 * x);
            nx = (-1.0f + 2 * nx);
            y = (-1.0f + 2 * y);
            ny = (-1.0f + 2 * ny);

            // clang-format on
            Vertex slice[6] = {
                {{w * x, h * y, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{w * x, h * ny, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
                {{w * nx, h * y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                {{w * nx, h * y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                {{w * x, h * ny, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
                {{w * nx, h * ny, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}};
            vertices.insert(vertices.end(), slice, slice + 6);
        }
    }
    return vertices;
}

}  // namespace primitive
}  // namespace game_engine