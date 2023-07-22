//
//  model.cc
//  oneten_ad_model
//
//  Created by li zhixuan on 2023/5/2.
//

#include "model.h"
#include <ad/entity/entity_interface.h>
#include <ad/util/storage.h>

BEGIN_NAMESPACE_ONETEN_AD

//std::string Model::Identifier() {
//}

bool Model::Save() {
//    Storage::DefaultStorage().Save(shared_from_this());
}

std::shared_ptr<Model> Model::Read(const std::string& key) {
    
}

bool Model::Update(const std::shared_ptr<Model> objc) {
    
}

bool Model::Remove(const std::string& key) {
    
}

END_NAMESPACE_ONETEN_AD
