//
//  FilterNode.cpp
//
//  Created by rayyy on 2021/9/24.
//

#include "FilterNode.hpp"
#include "FilterFactory.hpp"

namespace effect {

FilterNode::FilterNode(const FilterNodeDescription &nodeDesc) {
    id = nodeDesc.id;
    if (nodeDesc.id != defaultBeginID) {
        filter = FilterFactory::createFilter(nodeDesc.filterDesc);
    }
}

void FilterNode::render() {
    if (id != defaultBeginID) {
        if (outputFrameBuffer) {
            filter->renderToFrameBuffer(outputFrameBuffer);
            setResultFrameBufferToNextNodes(outputFrameBuffer);
        } else {
            std::shared_ptr<FrameBuffer> output = filter->render();
            setResultFrameBufferToNextNodes(output);
            output->unlock();
        }
    }
    informNextNodesToRender();
}

void FilterNode::setOutputFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    this->outputFrameBuffer = outputFrameBuffer;
}

void FilterNode::setResultFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> resultFrameBuffer) {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        if (i < nextIndices.size()) {
            nextNodes[i]->filter->setInputFrameBufferAtIndex(resultFrameBuffer, nextIndices[i]);
        } else {
            nextNodes[i]->filter->setInputFrameBufferAtIndex(resultFrameBuffer);
        }
    }
}

void FilterNode::informNextNodesToRender() {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        if (nextNodes[i]->filter->isAllInputReady()) {
            nextNodes[i]->render();
        }
    }
}

}
