//
//  EffectEngine.hpp
//
//  Created by rayyy on 2021/11/9.
//

#ifndef EffectEngine_hpp
#define EffectEngine_hpp

#include "FilterChain.hpp"
#include "BaseDefine.h"

namespace effect {

/// 效果引擎接口
class EffectEngine : public FilterChain {
public:
    
    EffectEngine(std::string configFilePath);
    
    /// 滤镜的类型
    std::string filterType() override { return "EffectEngine"; }
    
    virtual void setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount);
    
};

}

#endif /* EffectEngine_hpp */
