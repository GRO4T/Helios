#pragma once

#include <iostream>

#include "Camera.hpp"
#include "opengl_all.hpp"

namespace game_engine {

class ShaderProgram {
public:
    ShaderProgram(const GLchar *vertex_path, const GLchar *fragment_path);
    virtual ~ShaderProgram() {}

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec4(const std::string &name, const glm::vec4 vec) const;
    void setVec3(const std::string &name, const glm::vec3 vec) const;

    void setViewMatrix(const Camera &camera) const;
    void setProjectionMatrix(const glm::mat4 &projection_matrix) const;
    void setTransformationMatrix(const glm::mat4 &transformation_matrix) const;

    void use() const { glUseProgram(getProgramID()); }
    GLuint getProgramID() const { return program_id; }

protected:
    void bindAttribute(int attrib_number,
                       const std::string &attrib_name) const {
        glBindAttribLocation(program_id, attrib_number, attrib_name.c_str());
    }

private:
    GLuint program_id;
};

}  // namespace game_engine