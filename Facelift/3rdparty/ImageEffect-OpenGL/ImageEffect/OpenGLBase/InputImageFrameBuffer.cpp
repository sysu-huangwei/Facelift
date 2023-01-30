//
//  InputImageFrameBuffer.cpp
//
//  Created by rayyyhuang on 2022/11/26.
//

#include "InputImageFrameBuffer.hpp"
#include "BaseGLUtils.hpp"

namespace effect {

void InputImageFrameBuffer::initWithImageFile(const char *filePath) {
    int width, height;
    unsigned char *rgbaData = BaseGLUtils::loadImageFileToRGBAPixels(filePath, width, height);
    if (rgbaData && width > 0 && height > 0) {
        initWithRGBAImageData(rgbaData, width, height);
    }
}

void InputImageFrameBuffer::initWithRGBAImageData(unsigned char *rgbaData, int width, int height) {
    if (rgbaData && width > 0 && height > 0) {
        GLuint textureID = BaseGLUtils::loadPixelsToTexture(rgbaData, width, height);
        if (textureID > 0) {
            FrameBuffer::init(width, height, true, defaultTextureOptions, textureID);
        }
    }
}
    
}
