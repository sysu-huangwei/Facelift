//
//  CopyFilter.hpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#ifndef CopyFilter_hpp
#define CopyFilter_hpp

#include "BaseFilter.hpp"

namespace effect {

/// 画原图的滤镜
class CopyFilter : public BaseFilter {
public:
    
    /// 滤镜的类型
    std::string filterType() override { return FilterType_Copy; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;

};

}

#endif /* CopyFilter_hpp */
