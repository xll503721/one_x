//
//  entity_interface.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_ENTITY_INTERFACE_H
#define ONETEN_AD_SDK_ENTITY_INTERFACE_H

#include <oneten_object.h>
#include <error.h>

BEGIN_NAMESPACE_ONETEN_AD

template <typename T>
class EntityInterface: public ONETEN::Object<T> {
    
public:
    virtual std::string Identifier() = 0;
    
protected:
    std::string identifier_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_H */
