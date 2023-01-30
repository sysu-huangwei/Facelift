//
//  ProgramPool.cpp
//
//  Created by rayyyhuang on 2021/7/5.
//

#include "ProgramPool.hpp"
#include <mutex>

namespace effect {

static std::shared_ptr<ProgramPool> programPoolSharedInstance;
static std::mutex programPoolSharedInstanceLock;

std::shared_ptr<ProgramPool> ProgramPool::getSharedInstance() {
    if (programPoolSharedInstance == nullptr) {
        std::lock_guard<std::mutex> lock(programPoolSharedInstanceLock);
        if (programPoolSharedInstance == nullptr) {
            struct Constructor : public ProgramPool {};
            programPoolSharedInstance = std::make_shared<Constructor>();
        }
    }
    return programPoolSharedInstance;
}

ProgramPool::ProgramPool() {
    
}

ProgramPool::~ProgramPool() {
    
}

std::shared_ptr<Program> ProgramPool::fetchProgramFromPool(std::string vertexSource, std::string fragmentSource) {
    std::string key = vertexSource + "_" + fragmentSource;
    if (programCache.find(key) != programCache.end()) {
        return programCache.at(key);
    } else {
        std::shared_ptr<Program> program = std::make_shared<Program>();
        program->init(vertexSource, fragmentSource);
        programCache[key] = program;
        return program;
    }
}

void ProgramPool::clearProgramFromPool() {
    std::map<std::string, std::shared_ptr<Program>>::iterator it;
    for (it = programCache.begin(); it != programCache.end(); it++) {
        (*it).second->release();
    }
    programCache.clear();
}

}
