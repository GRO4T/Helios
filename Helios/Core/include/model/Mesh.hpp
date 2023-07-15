#pragma once

#include <Utils.hpp>
#include <memory>
#include <vector>

#include "opengl_all.hpp"

namespace helios {

using utils::Vertex;

class Mesh {
public:
    Mesh() {}
    Mesh(const std::vector<Vertex>& vertices) { load(vertices); }
    virtual ~Mesh();
    void load(const std::vector<Vertex>& vertices);
    GLuint getVao() const { return VAO; }
    std::size_t getVertexCount() const { return vertex_count; }
    virtual void draw() const { glDrawArrays(GL_TRIANGLES, 0, vertex_count); }

protected:
    void storeDataInAttribList(GLuint attrib_number, GLuint vector_len,
                               std::vector<GLfloat>& data);  // not used

    GLsizei vertex_count;
    GLuint VAO;
};

class IndexedMesh : public Mesh {
public:
    IndexedMesh(const std::vector<Vertex>& vertices,
                const std::vector<GLuint>& indices) {
        load(vertices, indices);
    }
    virtual void draw() const override {
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (void*)0);
    }
    void load(const std::vector<Vertex>& vertices,
              const std::vector<GLuint>& indices);

protected:
    GLsizei index_count;
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

}  // namespace helios