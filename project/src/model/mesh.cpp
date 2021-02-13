#include "model/mesh.hpp"

#include "model/primitive_mesh.hpp"

namespace game_engine {

Mesh::~Mesh() { glDeleteVertexArrays(1, &VAO); }

void Mesh::load(const std::vector<Vertex>& vertices) {
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
    vertex_count = vertices.size();
}

void IndexedMesh::load(std::vector<GLfloat> &vertices,
                        std::vector<GLfloat> &normals,
                        std::vector<GLfloat> &tex_coords,
                        std::vector<GLuint> &indices) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);
    storeDataInAttribList(0, 3, vertices);
    storeDataInAttribList(1, 2, tex_coords);
    storeDataInAttribList(2, 3, normals);
    glBindVertexArray(0);
    vertex_count = static_cast<int>(vertices.size()) / 3;
    index_count = static_cast<int>(indices.size());
}

void Mesh::storeDataInAttribList(GLuint attrib_number, GLuint vector_len,
                                  std::vector<GLfloat> &data) {
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    GLuint data_size = sizeof(GLfloat) * static_cast<GLuint>(data.size());
    glBufferData(GL_ARRAY_BUFFER, data_size, data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attrib_number, vector_len, GL_FLOAT, GL_FALSE, 0,
                          (void *)0);
    glEnableVertexAttribArray(attrib_number);
}

}  // namespace game_engine