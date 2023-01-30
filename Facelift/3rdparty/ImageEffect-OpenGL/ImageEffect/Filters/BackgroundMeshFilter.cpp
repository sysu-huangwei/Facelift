//
//  BackgroundMeshFilter.cpp
//
//  Created by rayyyhuang on 2021/6/7.
//

#include "BackgroundMeshFilter.hpp"
#include "MeshFilter.hpp"

namespace effect {

BackgroundMeshFilter::BackgroundMeshFilter() {
    FilterNodeDescription begin = defaultBeginNodeDescription;
    begin.nextIDs.push_back("copy");
    begin.nextTextureIndices.push_back(0);
    begin.nextIDs.push_back("mesh");
    begin.nextTextureIndices.push_back(0);
    
    FilterNodeDescription copy;
    copy.id = "copy";
    copy.filterDesc.type = FilterType_Copy;
    
    FilterNodeDescription mesh;
    mesh.id = "mesh";
    mesh.filterDesc.type = FilterType_Mesh;
    
    nodeDescriptions.push_back(begin);
    nodeDescriptions.push_back(copy);
    nodeDescriptions.push_back(mesh);
}

void BackgroundMeshFilter::setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount) {
    std::shared_ptr<MeshFilter> meshFilter = std::static_pointer_cast<MeshFilter>(getFilterByNodeID("mesh"));
    if (meshFilter) {
        meshFilter->setMesh(mesh, meshStd, meshIndex, indexArrayCount);
    }
}

}
