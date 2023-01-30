//
//  MeshFilter.hpp
//
//  Created by rayyyhuang on 2021/4/22.
//

#ifndef MeshFilter_hpp
#define MeshFilter_hpp

#include <vector>
#include "BaseFilter.hpp"
#include "BaseDefine.h"

namespace effect {

/// 画三角网格的滤镜
class MeshFilter : public BaseFilter {
public:
    ~MeshFilter();
    
    /// 滤镜的类型
    std::string filterType() override { return FilterType_Mesh; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;
    
    /// 设置需要画的网格，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param mesh 点位信息
    /// @param meshStd 标准点位信息
    /// @param meshIndex 下标索引数组
    /// @param indexArrayCount meshIndex数组长度
    virtual void setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount);
    
protected:
    int positionStdAttribute = -1;
    float *mesh = nullptr;
    float *meshStd = nullptr;
    int meshArrayCount = 0;
    unsigned int *meshIndex = nullptr;
    int indexArrayCount = 0;
    
    /// 在最终渲染之前判断是否需要渲染
    virtual bool isNeedRender() override;
};

}

#endif /* MeshFilter_hpp */
