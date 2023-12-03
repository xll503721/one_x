#ifndef ONETEN_AD_SDK_PCH_H
#define ONETEN_AD_SDK_PCH_H

#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <sstream>
#include <unordered_map>
#include <log/log.h>
#include <cross/platform.h>
#include <any>
#include "error_code.h"

#ifndef __FILE_NAME__
#define __FILE_NAME__ __FILE__
#endif

#define REGISTER_MODEL(NAME) \
std::shared_ptr<NAME> model_##NAME = std::make_shared<NAME>();\
otlog_info << "register model:" << #NAME;\
ModelFactory::GetInstance().SetModel(ModelFactory::ModelType::kModelType##NAME, model_##NAME);\

#define ONETEN_AD oneten_ad
#define BEGIN_NAMESPACE_ONETEN_AD BEGIN_NAMESPACE(ONETEN_AD)
#define END_NAMESPACE_ONETEN_AD END_NAMESPACE()

#define ONETEN oneten
#define BEGIN_NAMESPACE_ONETEN BEGIN_NAMESPACE(ONETEN)
#define END_NAMESPACE_ONETEN END_NAMESPACE()

#define BEGIN_NAMESPACE(ns) namespace ns {
#define END_NAMESPACE() }

#define READONLY_PROPERTY(TYPE, METHOD, VAR_NAME) \
public:\
    TYPE Get##METHOD() {\
        return VAR_NAME##_;\
    }\
private:\
    TYPE VAR_NAME##_;\

#endif /* ONETEN_AD_SDK_PCH_H */
