//
//  storage.h
//  SDKCommon
//
//  Created by li zhixuan on 2023/5/3.
//

#ifndef ONETEN_AD_SDK_STORAGE_H
#define ONETEN_AD_SDK_STORAGE_H

#include <oneten_object.h>
#include <storage/memory/storage_memory.h>
#include <ad/model/model.h>
#include <ad/model/placement_model.h>

BEGIN_NAMESPACE_ONETEN_AD

#define STORAGE_SAVE(CLASS_NAME, SHARED_PRT_MODEL)\
Storage::DefaultStorage().Save(#CLASS_NAME, SHARED_PRT_MODEL);

#define STORAGE_READ(CLASS_NAME, IDENTIFIER) Storage::DefaultStorage().Read(#CLASS_NAME, IDENTIFIER)

class Storage: public ONETEN::Object<Storage> {
    
public:
    Storage(const Storage& storage) = delete;
    
    static Storage& DefaultStorage();
    
    bool Save(const std::string& clazz_name, std::shared_ptr<Model> model);
    bool Update(const std::string& clazz_name, std::shared_ptr<Model> model);
    bool Delete(std::shared_ptr<Model> model);
    std::shared_ptr<Model> Read(const std::string& clazz_name, const std::string& key);
    
    template <typename T>
    void Register() {
        otlog_info << "register:" << typeid(T).name() << "into Storage";
        std::string key(typeid(T).name());
        
        StorageMemoryValue model_storage_memory;
        model_storage_memory_[key] = model_storage_memory;
    }
    
    void Test();
    
private:
    Storage() = default;
    
    using StorageMemoryValue = BASE_STORAGE_MEMORY::StorageMemory<std::string, std::shared_ptr<Model>>;
    
    std::map<std::string, StorageMemoryValue> model_storage_memory_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_STORAGE_H */
