#pragma once

#include <memory>
#include <utils.hpp>
#include <vector>

#include "opengl_all.hpp"

namespace game_engine {

using utils::Vertex;

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices) { load(vertices); }
    virtual ~Mesh();
    void load(const std::vector<Vertex>& vertices);
    GLuint getVao() const { return VAO; }
    int getVertexCount() const { return vertex_count; }
    virtual void draw() const { glDrawArrays(GL_TRIANGLES, 0, vertex_count); }

protected:
    void storeDataInAttribList(GLuint attrib_number, GLuint vector_len,
                               std::vector<GLfloat>& data);  // not used

    int vertex_count;
    GLuint VAO;
};

class IndexedMesh : public Mesh {
public:
    virtual void draw() const override {
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (void*)0);
    }
    void load(std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals,
              std::vector<GLfloat>& tex_coords, std::vector<GLuint>& indices);

protected:
    int index_count;
};

class StripedMesh : public IndexedMesh {
public:
    void draw() const override {
        glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_INT,
                       (void*)0);
    }
};

using MeshPtr = std::unique_ptr<Mesh>;
using IndexedMeshPtr = std::unique_ptr<IndexedMesh>;
using StripedMeshPtr = std::unique_ptr<StripedMesh>;

}  // namespace game_engine