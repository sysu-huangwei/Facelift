//
//  Program.hpp
//
//  Created by rayyyhuang on 2021/7/5.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>
#include <map>
#include "BasePlatform.h"

#if PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif PLATFORM_IOS
#define GLES_SILENCE_DEPRECATION 1
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

namespace effect {

/// GL Program封装，API都需要在GL线程调用
class Program {
public:
    
    /// 初始化
    /// @param vertexSource 顶点着色器
    /// @param fragmentSource 片段着色器
    void init(std::string vertexSource, std::string fragmentSource);
    
    /// 释放GL资源
    void release();
    
    /// 使用此Program进行draw
    void use();
    
    /// 设置顶点到Program [arrtibute]
    /// @param name [arrtibute] 的名字
    /// @param ptr 数组指针，float类型，（x，y）
    void setVertexAttribPointer(std::string name, const GLvoid* ptr);
    
    /// 设置uniform到Program
    /// @param name [uniform] 的名字
    /// @param x glUniform1i
    void setUniform1i(std::string name, int x);
    
    /// 设置uniform到Program
    /// @param name [uniform] 的名字
    /// @param x glUniform1f
    void setUniform1f(std::string name, float x);
    
    /// 设置uniform到Program
    /// @param name [uniform] 的名字
    /// @param x glUniform2i
    void setUniform2i(std::string name, int x, int y);
    
    /// 设置uniform到Program
    /// @param name [uniform] 的名字
    /// @param x glUniform2f
    void setUniform2f(std::string name, float x, float y);
    
    /// 设置纹理到Program
    /// @param name [uniform] 的名字
    /// @param textureID 纹理ID
    /// @param index 需要设置到哪一个纹理单元
    void setTextureAtIndex(std::string name, GLuint textureID, int index);
    
private:
    
    GLuint compileShader(GLenum type, const char *shaderSource);
    
    GLuint createProgram(const char *vertexSource, const char *fragmentSource);
    
    GLint getUniformLocation(std:: string name);
    
    GLint getAttributeLocation(std:: string name);
    
    GLuint programID = 0;
    std::map<std::string, GLint> uniformLocationMap;
    std::map<std::string, GLint> attributeLocationMap;
    
};

}

#endif /* Program_hpp */
