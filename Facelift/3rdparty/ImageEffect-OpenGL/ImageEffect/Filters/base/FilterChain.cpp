//
//  FilterChain.cpp
//
//  Created by rayyy on 2021/9/23.
//

#include "FilterChain.hpp"
#include "FilterFactory.hpp"

namespace effect {

using namespace std;

void FilterChain::init() {
    
    // 以下是根据滤镜链描述，来构造滤镜链的过程
    
    map<string, vector<string>> nodeIDToNextIDs;  // 当前节点ID对应的下一个(或几个)节点的ID
    map<string, vector<int>> nodeIDToNextIndices;  // 当前节点ID对应下一个(或几个)节点的纹理下标
    map<string, shared_ptr<FilterNode>> nodeIDToNode;  // 当前节点ID对应的真正渲染节点
    
    for (size_t i = 0; i < nodeDescriptions.size(); i++) {
        // 遍历滤镜链描述里的每一个节点描述
        const FilterNodeDescription &nodeDescription = nodeDescriptions[i];
        
        // 根据滤镜节点描述，构造滤镜节点实例
        shared_ptr<FilterNode> filterNode = make_shared<FilterNode>(nodeDescription);
        
        if (nodeDescription.id != defaultBeginID) {
            // 如果是正常的实体节点，那么初始化内部的滤镜
            filterNode->filter->init();
            allNodes.push_back(filterNode);
        } else {
            // 如果是虚拟起始节点，记录下来
            beginVirtualNode = filterNode;
        }
        
        // 如果一个滤镜节点没有后续节点，就说明这个节点是最后的节点（最后的节点可能不止一个）
        if (nodeDescription.nextIDs.empty()) {
            lastNodes.push_back(filterNode);
        }
        
        // 记录当前节点ID对应的下一个节点的ID和纹理下标
        nodeIDToNextIDs[nodeDescription.id] = nodeDescription.nextIDs;
        nodeIDToNextIndices[nodeDescription.id] = nodeDescription.nextTextureIndices;
        // 记录当前节点ID对应的真正节点对象
        nodeIDToNode[nodeDescription.id] = filterNode;
    }
    
    // 根据记录下来的各个节点ID先后顺序的关系，对应到真正的节点实例中去
    for (auto it = nodeIDToNextIDs.begin(); it != nodeIDToNextIDs.end(); it++) {
        const string &nodeID = (*it).first;
        const vector<string> &nextIDs = (*it).second;
        for (const string &nextID : nextIDs) {
            nodeIDToNode[nodeID]->nextNodes.push_back(nodeIDToNode[nextID]);
            nodeIDToNode[nodeID]->nextIndices = nodeIDToNextIndices[nodeID];
        }
    }
    
}

void FilterChain::release() {
    for (size_t i = 0; i < allNodes.size(); i++) {
        allNodes[i]->filter->release();
    }
    beginVirtualNode = nullptr;
    lastNodes.clear();
    allNodes.clear();
    BaseFilter::release();
}

void FilterChain::setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    BaseFilter::setInputFrameBufferAtIndex(inputFrameBuffer, index);
    // 把起始的输入FBO传递给虚拟起始节点，起始节点会将输入的FBO设置给各个真正的起始滤镜
    beginVirtualNode->setResultFrameBufferToNextNodes(inputFrameBuffer);
}

void FilterChain::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (isNeedRender() && outputFrameBuffer) {
        // 把目标FBO标记给最后的滤镜节点，让最好的滤镜节点直接绘制到这个FBO上
        for (size_t i = 0; i < lastNodes.size(); i++) {
            lastNodes[i]->setOutputFrameBuffer(outputFrameBuffer);
        }
        
        // 启动整个滤镜链的渲染
        beginVirtualNode->render();
    }
    
    unlockAndClearAllInputFrameBuffers();
}

void FilterChain::setParams(const std::map<std::string, std::string> &param) {
    for (size_t i = 0; i < allNodes.size(); i++) {
        allNodes[i]->filter->setParams(param);
    }
}

const std::shared_ptr<BaseFilter> FilterChain::getFilterByNodeID(const std::string &id) {
    std::shared_ptr<BaseFilter> filter = nullptr;
    for (size_t i = 0; i < allNodes.size(); i++) {
        if (allNodes[i]->id == id) {
            filter = allNodes[i]->filter;
        }
    }
    return filter;
}

}
