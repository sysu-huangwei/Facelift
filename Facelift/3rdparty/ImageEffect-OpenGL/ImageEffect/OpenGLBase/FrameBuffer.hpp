//
//  FrameBuffer.hpp
//
//  Created by rayyyhuang on 2021/7/1.
//

#ifndef FrameBuffer_hpp
#define FrameBuffer_hpp

#include <memory>
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

typedef struct TextureOptions {
    GLenum minFilter;
    GLenum magFilter;
    GLenum wrapS;
    GLenum wrapT;
    GLenum internalFormat;
    GLenum format;
    GLenum type;
} TextureOptions;

extern const TextureOptions defaultTextureOptions;

// GL FBO封装
class FrameBuffer : public std::enable_shared_from_this<FrameBuffer> {
public:
    
    /// 初始化，必须在GL线程
    /// @param width 宽
    /// @param height 高
    /// @param isOnlyTexture 是否只生成纹理，不生成FrameBuffer
    /// @param textureOptions 纹理相关参数
    /// @param textureID 外部指定的纹理ID，若>0，则内部不会生成纹理
    /// @param frameBufferID 外部指定的FBO，若>0，则内部不会生成FBO
    virtual void init(int width, int height, bool isOnlyTexture = false, TextureOptions textureOptions = defaultTextureOptions, GLuint textureID = 0, GLuint frameBufferID = 0);
    
    /// 释放GL相关资源，必须在GL线程
    virtual void release();
    
    /// 激活此FBO
    void activeFrameBuffer();
    
    /// 是否启用计数
    /// 不启用计数时，需要使用者自行管理 init 和 release 的配对调用
    /// 启用计数时，当计数为0，会自动释放到FrameBufferPool缓存池里。这种情况需要直接通过FrameBufferPool管理FrameBuffer
    /// @param enableReferenceCount 是否启用计数
    void setEnableReferenceCount(bool enableReferenceCount);
    
    /// 当启用计数时，引用+1
    void lock();
    
    /// 当启用计数时，引用-1
    void unlock();
    
    int getWidth() const { return width; }
    
    int getHeight() const { return height; }
    
    bool getIsOnlyTexture() const { return isOnlyTexture; }
    
    TextureOptions getTextureOptions() const { return textureOptions; }
    
    GLuint getTextureID() const { return textureID; }
    
    GLuint getFrameBufferID() const { return frameBufferID; }
    
protected:
    int width = 0, height = 0;
    GLuint textureID = 0, frameBufferID = 0;
    bool isOnlyTexture = false;
    TextureOptions textureOptions = defaultTextureOptions;
    bool isNeedReleaseTexture = false, isNeedReleaseFrameBuffer = false;

    friend class FrameBufferPool;
    bool enableReferenceCount = false;
    int referenceCount = 0;
    
    void createTexture();
    void createAndBindFrameBuffer();
};

}


#endif /* FrameBuffer_hpp */
