//
//  FrameBufferPool.hpp
//
//  Created by rayyyhuang on 2021/7/3.
//

#ifndef FrameBufferPool_hpp
#define FrameBufferPool_hpp

#include <string>
#include <map>
#include <vector>
#include "FrameBuffer.hpp"

namespace effect {

/// 全局FBO缓存池
class FrameBufferPool {
public:
    
    /// 获取全局单例
    static std::shared_ptr<FrameBufferPool> getSharedInstance();
    
    /// 从缓存池获取一个FBO，需要在GL线程
    /// @param width 宽
    /// @param height 高
    /// @param isOnlyTexture 是否只生成纹理，不生成FrameBuffer
    /// @param textureOptions 纹理相关参数
    std::shared_ptr<FrameBuffer> fetchFrameBufferFromPool(int width, int height, bool isOnlyTexture = false, TextureOptions textureOptions = defaultTextureOptions);
    
    /// 把一个FBO放回缓存池
    /// @param frameBuffer FBO
    void returnFrameBufferToPool(std::shared_ptr<FrameBuffer> frameBuffer);
    
    /// 清空缓存池，需要在GL线程
    void clearFrameBufferPool();
    
private:
    
    FrameBufferPool();
    ~FrameBufferPool();
    FrameBufferPool(const FrameBufferPool &) = delete;
    const FrameBufferPool &operator =(const FrameBufferPool &) = delete;
    
    std::map<std::string, std::vector<std::shared_ptr<FrameBuffer>>> frameBufferCache;
    
    std::string getTextureKey(int width, int height, bool isOnlyTexture, TextureOptions textureOptions);
};

}

#endif /* FrameBufferPool_hpp */
