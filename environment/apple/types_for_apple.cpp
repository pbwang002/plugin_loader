#include "../include/types.h"

class BaseTypeApple : public BaseType {
public:
    string GetSuffix() override
    {
        return "dylib";
    } 
};