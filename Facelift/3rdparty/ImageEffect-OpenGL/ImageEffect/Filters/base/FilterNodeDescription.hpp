//
//  FilterNodeDescription.hpp
//
//  Created by rayyy on 2021/9/23.
//

#ifndef FilterNodeDescription_hpp
#define FilterNodeDescription_hpp

#include <vector>
#include "FilterDescription.hpp"

namespace effect {

/// 滤镜节点的描述
typedef struct FilterNodeDescription {
    
    // 当前节点的ID
    std::string id = "";

    // 后继节点的ID
    std::vector<std::string> nextIDs;
    // 输入到后继节点的下标，与 nextIDs 一一对应
    std::vector<int> nextTextureIndices;
    
    // 当前滤镜的描述
    FilterDescription filterDesc;
    
} FilterNodeDescription;

extern const std::string defaultBeginID;  // 默认的起始节点的ID
extern const FilterNodeDescription defaultBeginNodeDescription;  // 默认的起始节点

}

#endif /* FilterNodeDescription_hpp */
