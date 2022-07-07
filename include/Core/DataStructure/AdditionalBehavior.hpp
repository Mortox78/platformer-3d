#ifndef _ADDITIONALBEHAVIOR_
#define _ADDITIONALBEHAVIOR_

#include <string>
#include <vector>
#include <memory>

#include "Transform.hpp"

namespace Core
{
    namespace DataStructure
    {
        class AdditionalBehavior
        {
        private:

        public:
        
            std::string name {"Empty"};
            Physics::Transform* transform {nullptr};

            virtual void Start(Physics::Transform* trs) {transform = trs;};
       
        
            AdditionalBehavior(){};
            virtual ~AdditionalBehavior(){};
                
            virtual void Update() {};
        };
               
    }
}

#endif