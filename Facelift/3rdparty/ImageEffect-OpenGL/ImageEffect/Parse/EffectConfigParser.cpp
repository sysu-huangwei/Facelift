//
//  EffectConfigParser.cpp
//
//  Created by rayyy on 2021/11/10.
//

#include "EffectConfigParser.hpp"
#include "BaseGLUtils.hpp"
#include "cJSON.h"
#include "BaseDefine.h"
#include "BaseLog.h"

namespace effect {

std::vector<FilterNodeDescription> EffectConfigParser::parseJsonToDescription(std::string json) {
    std::vector<FilterNodeDescription> descriptions;
    
    cJSON *root = cJSON_Parse(json.c_str());
    
    if(root && root->type == cJSON_Array) {
        int size = cJSON_GetArraySize(root);
        for (int i = 0; i < size; i++) {
            cJSON *node = cJSON_GetArrayItem(root, i);
            if (node && node->type == cJSON_Object) {
                FilterNodeDescription desc;
                
                cJSON *id = cJSON_GetObjectItem(node, "id");
                if (id && id->type == cJSON_String) {
                    desc.id = std::string(id->valuestring);
                }
                
                cJSON *nextIDs = cJSON_GetObjectItem(node, "nextIDs");
                if (nextIDs && nextIDs->type == cJSON_Array) {
                    int nextIDsSize = cJSON_GetArraySize(nextIDs);
                    for (int j = 0; j < nextIDsSize; j++) {
                        cJSON *nextID = cJSON_GetArrayItem(nextIDs, j);
                        if (nextID->type == cJSON_String) {
                            desc.nextIDs.push_back(nextID->valuestring);
                        }
                    }
                }
                
                cJSON *nextTextureIndices = cJSON_GetObjectItem(node, "nextTextureIndices");
                if (nextTextureIndices && nextTextureIndices->type == cJSON_Array) {
                    int nextTextureIndicesSize = cJSON_GetArraySize(nextTextureIndices);
                    for (int j = 0; j < nextTextureIndicesSize; j++) {
                        cJSON *nextTextureIndex = cJSON_GetArrayItem(nextTextureIndices, j);
                        if (nextTextureIndex->type == cJSON_Number) {
                            desc.nextTextureIndices.push_back(nextTextureIndex->valueint);
                        }
                    }
                }
                
                cJSON *filterDesc = cJSON_GetObjectItem(node, "filterDesc");
                if (filterDesc && filterDesc->type == cJSON_Object) {
                    
                    cJSON *type = cJSON_GetObjectItem(filterDesc, "type");
                    if (type && type->type == cJSON_String) {
                        desc.filterDesc.type = std::string(type->valuestring);
                    }
                    
                    cJSON *outputWidth = cJSON_GetObjectItem(filterDesc, "outputWidth");
                    if (outputWidth && outputWidth->type == cJSON_Number) {
                        desc.filterDesc.outputWidth = outputWidth->valueint;
                    }
                    
                    cJSON *outputHeight = cJSON_GetObjectItem(node, "outputHeight");
                    if (outputHeight && outputHeight->type == cJSON_Number) {
                        desc.filterDesc.outputHeight = outputHeight->valueint;
                    }
                    
                    cJSON *enable = cJSON_GetObjectItem(filterDesc, "enable");
                    if (enable) {
                        desc.filterDesc.enable = enable->type == cJSON_True;
                    }
                    
                    cJSON *params = cJSON_GetObjectItem(filterDesc, "params");
                    if (params && params->type == cJSON_Object) {
                        cJSON *currentParams = params->child;
                        if (currentParams) {
                            desc.filterDesc.params[std::string(currentParams->string)] = std::string(currentParams->valuestring);
                            currentParams = currentParams->next;
                        }
                    }
                }
                
                descriptions.push_back(desc);
            }
        }
    } else {
        LOGE("Error: 素材解析错！ 配置：\n%s", json.c_str());
    }
    
    cJSON_Delete(root);
    
    return descriptions;
}

}
