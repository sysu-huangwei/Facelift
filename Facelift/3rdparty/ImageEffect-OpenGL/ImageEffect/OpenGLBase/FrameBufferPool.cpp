//
//  FrameBufferPool.cpp
//
//  Created by rayyyhuang on 2021/7/3.
//

#include "FrameBufferPool.hpp"
#include <mutex>
#include "BaseDefine.h"

namespace effect {

static std::shared_ptr<FrameBufferPool> frameBufferPoolSharedInstance;
static std::mutex frameBufferPoolSharedInstanceLock;
static std::map<std::string, std::weak_ptr<FrameBuffer>> testRayyy;

std::shared_ptr<FrameBufferPool> FrameBufferPool::getSharedInstance() {
    if (frameBufferPoolSharedInstance == nullptr) {
        std::lock_guard<std::mutex> lock(frameBufferPoolSharedInstanceLock);
        if (frameBufferPoolSharedInstance == nullptr) {
            struct Constructor : public FrameBufferPool {};
            frameBufferPoolSharedInstance = std::make_shared<Constructor>();
        }
    }
    return frameBufferPoolSharedInstance;
}

FrameBufferPool::FrameBufferPool() {
    
}

FrameBufferPool::~FrameBufferPool() {
    
}

std::shared_ptr<FrameBuffer> FrameBufferPool::fetchFrameBufferFromPool(int width, int height, bool isOnlyTexture, TextureOptions textureOptions) {
    std::shared_ptr<FrameBuffer> frameBuffer = nullptr;
    std::string key = getTextureKey(width, height, isOnlyTexture, textureOptions);
    if (frameBufferCache.find(key) != frameBufferCache.end()) {
        std::vector<std::shared_ptr<FrameBuffer>> &frameBuffers = frameBufferCache.at(key);
        if (!frameBuffers.empty()) {
            frameBuffer = frameBuffers.back();
            frameBuffers.pop_back();
            if (frameBuffers.empty()) {
                frameBufferCache.erase(key);
            }
        }
    } else {
        frameBuffer = std::make_shared<FrameBuffer>();
        frameBuffer->init(width, height, isOnlyTexture, textureOptions);
        frameBuffer->setEnableReferenceCount(true);
        while (testRayyy.find(key) != testRayyy.end()) {
            key += "!";
        }
        testRayyy[key] = frameBuffer;
    }
    frameBuffer->lock();
    return frameBuffer;
}

void FrameBufferPool::returnFrameBufferToPool(std::shared_ptr<FrameBuffer> frameBuffer) {
    if (frameBuffer) {
        frameBuffer->referenceCount = 0;
        std::string key = getTextureKey(frameBuffer->getWidth(), frameBuffer->getHeight(), frameBuffer->getIsOnlyTexture(), frameBuffer->getTextureOptions());
        if (frameBufferCache.find(key) != frameBufferCache.end()) {
            frameBufferCache.at(key).push_back(frameBuffer);
        } else {
            std::vector<std::shared_ptr<FrameBuffer>> frameBuffers {frameBuffer};
            frameBufferCache[key] = frameBuffers;
        }
    }
}

void FrameBufferPool::clearFrameBufferPool() {
    std::map<std::string, std::vector<std::shared_ptr<FrameBuffer>>>::iterator it;
    for (it = frameBufferCache.begin(); it != frameBufferCache.end(); it++) {
        std::vector<std::shared_ptr<FrameBuffer>> frameBuffers = (*it).second;
        for (std::shared_ptr<FrameBuffer> frameBuffer : frameBuffers) {
            frameBuffer->release();
        }
    }
    frameBufferCache.clear();
}


std::string FrameBufferPool::getTextureKey(int width, int height, bool isOnlyTexture, TextureOptions textureOptions) {
    std::string key;
    key += std::to_string(width) + "_";
    key += std::to_string(height) + "_";
    key += std::to_string(isOnlyTexture) + "_";
    key += std::to_string(textureOptions.minFilter) + "_";
    key += std::to_string(textureOptions.magFilter) + "_";
    key += std::to_string(textureOptions.wrapS) + "_";
    key += std::to_string(textureOptions.wrapT) + "_";
    key += std::to_string(textureOptions.internalFormat) + "_";
    key += std::to_string(textureOptions.format) + "_";
    key += std::to_string(textureOptions.type) + "_";
    return key;
}

}
