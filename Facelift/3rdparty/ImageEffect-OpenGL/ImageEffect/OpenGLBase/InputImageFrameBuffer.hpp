//
//  InputImageFrameBuffer.hpp
//
//  Created by rayyyhuang on 2022/11/26.
//

#ifndef InputImageFrameBuffer_hpp
#define InputImageFrameBuffer_hpp

#include "FrameBuffer.hpp"

namespace effect {

class InputImageFrameBuffer : public FrameBuffer {
public:
    
    void initWithImageFile(const char *filePath);
    
    void initWithRGBAImageData(unsigned char *rgbaData, int width, int height);
    
};


}

#endif /* InputImageFrameBuffer_hpp */
