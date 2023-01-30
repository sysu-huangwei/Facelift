//
//  EffectEngine.cpp
//
//  Created by rayyy on 2021/11/9.
//

#include "EffectEngine.hpp"
#include "BaseGLUtils.hpp"
#include "EffectConfigParser.hpp"
#include "BaseDefine.h"
#include "BackgroundMeshFilter.hpp"

namespace effect {

EffectEngine::EffectEngine(std::string configFilePath) {
    unsigned long dataSise;
    char *json = BaseGLUtils::loadFileToMemory(configFilePath.c_str(), dataSise);
    nodeDescriptions = EffectConfigParser::parseJsonToDescription(std::string(json));
    SAFE_DELETE_ARRAY(json);
};


void EffectEngine::setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount) {
    for (int i = 0; i < allNodes.size(); i++) {
        std::shared_ptr<BackgroundMeshFilter> meshFilter = std::dynamic_pointer_cast<BackgroundMeshFilter>(allNodes[i]->filter);
        if (meshFilter) {
            meshFilter->setMesh(mesh, meshStd, meshIndex, indexArrayCount);
        }
    }
}

}
