//
//  Program.cpp
//
//  Created by rayyyhuang on 2021/7/5.
//

#include "Program.hpp"
#include "BaseLog.h"

namespace effect {

void Program::init(std::string vertexSource, std::string fragmentSource) {
    programID = createProgram(vertexSource.c_str(), fragmentSource.c_str());
}

void Program::release() {
    glDeleteProgram(programID);
    programID = 0;
}

void Program::use() {
    glUseProgram(programID);
}

GLuint Program::compileShader(GLenum type, const char *shaderSource) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        int infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen) {
            char *buf = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, NULL, buf);
            LOGE("Error: Could not compile shader, type = %d \n "
                 "ShaderInfoLog = %s, shaderSource = %s \n", type, buf, shaderSource);
            delete[] buf;
        }
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

GLuint Program::createProgram(const char *vertexSource, const char *fragmentSource) {
    unsigned vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0) {
        LOGE("Error in load vertex shader! ");
        return 0;
    }
    unsigned pixelShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (pixelShader == 0) {
        LOGE("Error in load fragment shader!");
        glDeleteShader(vertexShader);
        return 0;
    }
    
    unsigned program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
        int linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            int bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = new char[bufLength];
                glGetProgramInfoLog(program, bufLength, NULL, buf);
                LOGE("Could not link program:\n%s", buf);
                delete[] buf;
            }
            glDeleteProgram(program);
            program = 0;
        }
    } else {
        LOGE("Error: Could not create program");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(pixelShader);
    return program;
}

void Program::setVertexAttribPointer(std::string name, const GLvoid* ptr) {
    GLint location = getAttributeLocation(name);
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 2, GL_FLOAT, false, 0, ptr);
}

void Program::setUniform1i(std::string name, int x) {
    GLint location = getUniformLocation(name);
    glUniform1i(location, x);
}

void Program::setUniform1f(std::string name, float x) {
    GLint location = getUniformLocation(name);
    glUniform1f(location, x);
}

void Program::setUniform2i(std::string name, int x, int y) {
    GLint location = getUniformLocation(name);
    glUniform2i(location, x, y);
}

void Program::setUniform2f(std::string name, float x, float y) {
    GLint location = getUniformLocation(name);
    glUniform2f(location, x, y);
}

void Program::setTextureAtIndex(std::string name, GLuint textureID, int index) {
    GLint location = getUniformLocation(name);
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(location, index);
}

GLint Program::getUniformLocation(std:: string name) {
    if (uniformLocationMap.find(name) == uniformLocationMap.end()) {
        GLint location = glGetUniformLocation(programID, name.c_str());
        uniformLocationMap[name] = location;
        return location;
    } else {
        return uniformLocationMap[name];
    }
}

GLint Program::getAttributeLocation(std:: string name) {
    if (attributeLocationMap.find(name) == attributeLocationMap.end()) {
        GLint location = glGetAttribLocation(programID, name.c_str());
        attributeLocationMap[name] = location;
        return location;
    } else {
        return attributeLocationMap[name];
    }
}

}
