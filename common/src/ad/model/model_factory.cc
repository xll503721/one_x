//
//  model_factory.cc
//  oneten_ad_model
//
//  Created by li zhixuan on 2023/5/2.
//

#include "model_factory.h"

BEGIN_NAMESPACE_ONETEN_AD

ModelFactory &ModelFactory::GetInstance() {
    static ModelFactory model_factory;
    return model_factory;
}

//std::shared_ptr<Model> ModelFactory::GetModel(ModelType type) {
//    if (map_.find(type) == map_.end()) {
//        otlog_fault << "not found type:" << "" << "model, check model register";
//        return nullptr;
//    }
//
//    return map_[type];
//}
//
//void ModelFactory::SetModel(ModelType type, std::shared_ptr<Model> model) {
//    map_[type] = model;
//}

END_NAMESPACE_ONETEN_AD
