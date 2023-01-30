//
//  FilterFactory.cpp
//
//  Created by rayyy on 2021/9/23.
//

#include "FilterFactory.hpp"

#include "BaseLog.h"

#include "CopyFilter.hpp"
#include "MeshFilter.hpp"
#include "BackgroundMeshFilter.hpp"

namespace effect {
    
std::shared_ptr<BaseFilter> FilterFactory::createFilter(const FilterDescription &filterDesc) {
    std::shared_ptr<BaseFilter> filter = nullptr;
    
    if (filterDesc.type == FilterType_Copy) {
        filter = std::make_shared<CopyFilter>();
    } else if (filterDesc.type == FilterType_Mesh) {
        filter = std::make_shared<MeshFilter>();
    } else if (filterDesc.type == FilterType_BackgroundMesh) {
        filter = std::make_shared<BackgroundMeshFilter>();
    } else {
        LOGE("Error: FilterFactory::createFilter: invalid filter type = %s", filterDesc.type.c_str());
        assert(false);
    }
    
    filter->setEnableRender(filterDesc.enable);
    filter->setOutputSize(filterDesc.outputWidth, filterDesc.outputHeight);
    filter->setParams(filterDesc.params);
    
    return filter;
}

}
