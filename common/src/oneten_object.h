//
//  oneten_object.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef TENONE_SDK_OBJECT_H
#define TENONE_SDK_OBJECT_H

BEGIN_NAMESPACE_ONETEN

template <typename T>
class Object: public std::enable_shared_from_this<T> {
public:
    Object() = default;
    virtual ~Object() {};
    
    virtual std::shared_ptr<T> Clone() const {};
};

END_NAMESPACE_ONETEN

#endif /* TENONE_SDK_OBJECT_H */
