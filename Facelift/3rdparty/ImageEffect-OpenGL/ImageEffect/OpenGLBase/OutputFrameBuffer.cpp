//
//  OutputFrameBuffer.cpp
//
//  Created by rayyyhuang on 2022/12/1.
//

#include "OutputFrameBuffer.hpp"

namespace effect {

void OutputFrameBuffer::initWithFrameBufferID(GLuint outputFrameBufferID, int width, int height) {
    FrameBuffer::init(width, height, false, defaultTextureOptions, 0, outputFrameBufferID);
    enableReferenceCount = false;
}

}
    
