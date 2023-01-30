//
//  FilterDescription.hpp
//
//  Created by rayyy on 2021/9/23.
//

#ifndef FilterDescription_hpp
#define FilterDescription_hpp

#include <string>
#include <map>

namespace effect {

/// 一个渲染滤镜的描述
typedef struct FilterDescription {

    // 当前滤镜的类型
    std::string type = "";
    
    // 输出尺寸
    int outputWidth = 0;
    int outputHeight = 0;
    
    // 是否开启绘制
    bool enable = true;
    
    // 当前滤镜的一些参数配置
    std::map<std::string, std::string> params;
    
} FilterDescription;

}

#endif /* FilterDescription_hpp */
