//
//  model.hpp
//  oneten_ad_model
//
//  Created by li zhixuan on 2023/5/2.
//

#ifndef ONETEN_AD_SDK_MODEL_H
#define ONETEN_AD_SDK_MODEL_H

#include <oneten_object.h>
#include <storage/memory/storage_memory.h>
#include <ad/entity/entity_interface.h>
#include <storage/database/database.h>

BEGIN_NAMESPACE_ONETEN_AD

#define MODEL_MAPPING_PROPERTY(TYPE, VAR_NAME, MAPPING_OBJ) \
public:\
    TYPE Get##TYPE() {\
        return MAPPING_OBJ##->VAR_NAME##();\
    }\
private:\
    TYPE VAR_NAME##_;\

class Model: public EntityInterface<Model> {
    
public:
    Model() = default;
    virtual std::string Identifier() {};
    
    virtual bool Save();
    
    static std::shared_ptr<Model> Read(const std::string& key);
    
    bool Update(const std::shared_ptr<Model> objc);
    
    bool Remove(const std::string& key);
    
private:
    std::shared_ptr<BASE_STORAGE_DATABASE::DataBase> data_base_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_MODEL_H */
