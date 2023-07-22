//
//  model_factory.h
//  oneten_ad_model
//
//  Created by li zhixuan on 2023/5/2.
//

#ifndef ONETEN_AD_SDK_MODEL_FACTORY_H
#define ONETEN_AD_SDK_MODEL_FACTORY_H

#include <oneten_object.h>
#include "model.h"

BEGIN_NAMESPACE_ONETEN_AD

class ModelFactory: public ONETEN::Object<ModelFactory> {
    
public:
    enum class ModelType {
        kModelTypePlacementModel,
        kModelTypeCacheModel,
    };
    
    static ModelFactory &GetInstance();
    
//    std::shared_ptr<Model> GetModel(ModelType type);
//    void SetModel(ModelType type, std::shared_ptr<Model> model);
    
private:
//    std::map<ModelType, std::shared_ptr<Model>> map_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_MODEL_FACTORY_H */
