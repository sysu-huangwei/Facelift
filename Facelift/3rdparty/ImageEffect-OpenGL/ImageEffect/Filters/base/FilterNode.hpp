//
//  FilterNode.hpp
//
//  Created by rayyy on 2021/9/24.
//

#ifndef FilterNode_hpp
#define FilterNode_hpp

#include <vector>
#include "FilterNodeDescription.hpp"
#include "BaseFilter.hpp"

namespace effect {

/// 滤镜节点，这个类主要是为滤镜链类FilterChain服务的
class FilterNode {
public:
    
    FilterNode(const FilterNodeDescription &nodeDesc);
    
    /// 如果需要绘制到特定的FBO上，那么通过这个接口设置。通常滤镜链的最后一个节点需要设置
    /// @param outputFrameBuffer 目标FBO
    void setOutputFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer);
    
    /// 渲染，必须在GL线程
    void render();
    
protected:
    
    // 当前节点的ID
    std::string id = "";
    
    // 当前节点实际的渲染滤镜
    std::shared_ptr<BaseFilter> filter = nullptr;
    
    friend class FilterChain;
    friend class EffectEngine;
    // 下一个(或多个)渲染节点
    std::vector<std::shared_ptr<FilterNode>> nextNodes;
    // 输入给下一个(或多个)渲染节点纹理下标
    std::vector<int> nextIndices;
    
    // 当前节点的输出FBO，配合setOutputFrameBuffer方法使用。通常滤镜链的最后一个节点需要设置。非最后一个节点不需要这个。
    std::shared_ptr<FrameBuffer> outputFrameBuffer = nullptr;
    
    // 设置结果FBO给后续的滤镜节点
    void setResultFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> resultFrameBuffer);
    
    // 告知后续的节点可以进行渲染了
    void informNextNodesToRender();
};

}

#endif /* FilterNode_hpp */
