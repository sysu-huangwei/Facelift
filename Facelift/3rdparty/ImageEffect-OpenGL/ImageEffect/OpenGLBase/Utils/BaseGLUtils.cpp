//
//  BaseGLUtils.cpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#include "BaseGLUtils.hpp"
#include "BaseDefine.h"
#include "BaseLog.h"
#ifdef PLATFORM_IOS
#include "FileUtilsForIOS.h"
#endif

namespace effect {

std::string BaseGLUtils::getResourcePath() {
#ifdef PLATFORM_IOS
    return getResourcePathForIOS();
#endif
}

std::string BaseGLUtils::getVertexShaderSourceByName(std::string shaderName) {
    return getShaderSourceByName(shaderName, GL_VERTEX_SHADER);
}

std::string BaseGLUtils::getFragmengShaderSourceByName(std::string shaderName) {
    return getShaderSourceByName(shaderName, GL_FRAGMENT_SHADER);
}

std::string BaseGLUtils::getFilterDescriptionByName(std::string descriptionName) {
    std::string filePath = getResourcePath() + "/descriptions/" + descriptionName + ".json";
    unsigned long dataSize;
    const char *memoryData = loadFileToMemory(filePath.c_str(), dataSize);
    if (memoryData == NULL || dataSize == 0) {
        LOGE("Error: getFilterDescriptionByName: loadFileToMemory failed: filePath = %s", filePath.c_str());
        return "";
    } else {
        std::string description = std::string(memoryData);
        SAFE_DELETE_ARRAY(memoryData);
        return description;
    }
}

unsigned char *BaseGLUtils::loadImageFileToRGBAPixels(const char *filePath, int &outWidth, int &outHeight) {
    outWidth = 0;
    outHeight = 0;
    
    if (filePath == NULL || strcmp(filePath, "") == 0) {
        LOGE("Error: loadImageFileToRGBAPixels: filePath = NULL");
        return NULL;
    }
    
    unsigned long dataSize;
    char *memoryData = (char *) loadFileToMemory(filePath, dataSize);
    if (memoryData == NULL || dataSize == 0) {
        LOGE("Error: loadImageFileToRGBAPixels: loadFileToMemory failed: filePath = %s", filePath);
        return NULL;
    }
    
    unsigned char *data = loadMemoryToRGBAPixels(memoryData, dataSize, outWidth, outHeight);
    
    SAFE_DELETE_ARRAY(memoryData);
    
    if (data == NULL || outWidth == 0 || outHeight == 0) {
        LOGE("Error: loadImageFileToRGBAPixels: loadMemoryToRGBAPixels failed: filePath = %s", filePath);
        return NULL;
    }
    
    return data;
}

GLuint BaseGLUtils::loadImageFileToTexture(const char *filePath, int &outWidth, int &outHeight) {
    outWidth = 0;
    outHeight = 0;
    
    if (filePath == NULL || strcmp(filePath, "") == 0) {
        LOGE("Error: loadImageFileToTexture: filePath = NULL");
        return 0;
    }
    
    unsigned char *data = loadImageFileToRGBAPixels(filePath, outWidth, outHeight);
    if (data == NULL || outHeight * outHeight <= 0) {
        LOGE("Error: loadImageFileToTexture failed to load image: filePath: %s, pData = %p, w * h: %d * %d", filePath, data, outHeight, outHeight);
        return 0;
    }
    
    GLuint result = loadPixelsToTexture(data, outWidth, outHeight, GL_RGBA);
    SAFE_DELETE_ARRAY(data);
    
    return result;
}


std::string BaseGLUtils::getShaderSourceByName(std::string shaderName, GLenum shaderType) {
    std::string filePath = "";
    switch (shaderType) {
        case GL_VERTEX_SHADER:
            filePath = getResourcePath() + "/shaders/" + shaderName + ".vs";
            break;
        case GL_FRAGMENT_SHADER:
            filePath = getResourcePath() + "/shaders/" + shaderName + ".fs";
            break;
        default:
            break;
    }
    unsigned long dataSize;
    const char *memoryData = loadFileToMemory(filePath.c_str(), dataSize);
    if (memoryData == NULL || dataSize == 0) {
        LOGE("Error: getShaderSourceByName: loadFileToMemory failed: filePath = %s", filePath.c_str());
        return "";
    } else {
        std::string shaderSource = std::string(memoryData);
        SAFE_DELETE_ARRAY(memoryData);
        return shaderSource;
    }
}

char *BaseGLUtils::loadFileToMemory(const char *filePath, unsigned long &outDataSize) {
    char *data = NULL;
    FILE *file = fopen(filePath, "r");
    if (file) {
        // 先读取大小
        fseek(file,0,SEEK_END);
        long length = ftell(file);
        fseek(file,0,SEEK_SET);
        
        if (length > 0) {
            data = new char[length + 1];
            memset(data, 0, length + 1);
            fread(data, length, 1, file);
            outDataSize = length;
        } else {
            LOGE("Error: loadFileToMemory file size < 0: %ld", length);
        }
        
        fclose(file);
    } else {
        LOGE("Error: loadFileToMemory failed to open file, filePath = %s", filePath);
    }
    return data;
}


GLuint BaseGLUtils::loadPixelsToTexture(const unsigned char *data, int width, int height, GLenum glFormat) {
    GLuint textures;
    glGenTextures(1, &textures);
    if (textures != 0) {
        glBindTexture(GL_TEXTURE_2D, textures);
        if (glFormat == GL_LUMINANCE) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);
        }
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        return textures;
    } else {
        LOGE("Error: loadRGBAPixelsToTexture failed to glGenTextures");
        return 0;
    }
}

unsigned char *BaseGLUtils::loadMemoryToRGBAPixels(const char *memoryData, unsigned long dataSize, int &outWidth, int &outHeight) {
#ifdef PLATFORM_IOS
    return loadMemoryToRGBAPixelsForIOS(memoryData, dataSize, outWidth, outHeight);
#endif
}

}
