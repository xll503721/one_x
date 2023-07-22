//
//  cache_model.cc
//  oneten_ad_model
//
//  Created by li zhixuan on 2023/5/3.
//

#include "storage.h"

BEGIN_NAMESPACE_ONETEN_AD

Storage& Storage::DefaultStorage() {
    static Storage storage;
    return storage;
}

bool Storage::Save(const std::string& clazz_name, std::shared_ptr<Model> model) {
    auto item_storage_memory = model_storage_memory_[clazz_name];
    item_storage_memory[model->Identifier()] = model;
    model_storage_memory_[clazz_name] = item_storage_memory;
    return true;
}

std::shared_ptr<Model> Storage::Read(const std::string& clazz_name, const std::string& key) {
    auto item_storage_memory = model_storage_memory_[clazz_name];
    auto model_cache = item_storage_memory[key];
    return model_cache;
}

bool Storage::Update(const std::string& clazz_name, std::shared_ptr<Model> model) {
    return Save(clazz_name, model);
}

bool Storage::Delete(std::shared_ptr<Model> model) {
//    return model_storage_memory_.Remove(model->Identifier());
}

END_NAMESPACE_ONETEN_AD
