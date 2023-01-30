//
//  EffectConfigParser.hpp
//
//  Created by rayyy on 2021/11/10.
//

#ifndef EffectConfigParser_hpp
#define EffectConfigParser_hpp

#include <vector>
#include "FilterNodeDescription.hpp"

namespace effect {

class EffectConfigParser {
public:
    
    static std::vector<FilterNodeDescription> parseJsonToDescription(std::string json);
    
};

}

#endif /* EffectConfigParser_hpp */
