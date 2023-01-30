//
//  OutputFrameBuffer.hpp
//
//  Created by rayyyhuang on 2022/12/1.
//

#ifndef OutputFrameBuffer_hpp
#define OutputFrameBuffer_hpp

#include "FrameBuffer.hpp"

namespace effect {

class OutputFrameBuffer : public FrameBuffer {
public:
    
    void initWithFrameBufferID(GLuint outputFrameBufferID, int width, int height);
    
};


}

#endif /* OutputFrameBuffer_hpp */
