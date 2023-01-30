//
//  ProgramPool.hpp
//
//  Created by rayyyhuang on 2021/7/5.
//

#ifndef ProgramPool_hpp
#define ProgramPool_hpp

#include <map>
#include "Program.hpp"

namespace effect {

/// 全局Program缓存池
class ProgramPool {
public:
    
    /// 获取全局单例
    static std::shared_ptr<ProgramPool> getSharedInstance();
    
    /// 从缓存池获取一个Program，需要在GL线程
    /// @param vertexSource 顶点着色器
    /// @param fragmentSource 片段着色器
    std::shared_ptr<Program> fetchProgramFromPool(std::string vertexSource, std::string fragmentSource);
    
    /// 清空缓存池，需要在GL线程
    void clearProgramFromPool();
    
private:

    ProgramPool();
    ~ProgramPool();
    ProgramPool(const ProgramPool &) = delete;
    const ProgramPool &operator =(const ProgramPool &) = delete;
    
    std::map<std::string, std::shared_ptr<Program>> programCache;
};

}

#endif /* ProgramPool_hpp */
