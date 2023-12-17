//
//  adn_ids.h
//  SDKCommon
//
//  Created by HINLI on 2023/12/3.
//

#ifndef ONETEN_AD_SDK_AD_SDK_ADN_IDS_H
#define ONETEN_AD_SDK_AD_SDK_ADN_IDS_H

class AdnId {
    enum class Internal {
        kGDT,
        kKS,
        kBaidu,
        kCSJ,
        kGromore,
        kMTG,
        kPangle,
        kSigmob,
        kTianmu,
        kTopOn,
    };
    
    enum class Overseas {
        kMax,
        kInmob,
        kDigitalTurbine,
        kChartboost,
        kIronSource,
        kStart,
        kUnity,
        kVungle,
        kYandex
    };
};


#endif /* ONETEN_AD_SDK_AD_SDK_ADN_IDS_H */
