//
//  header_bid_loader.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/12/3.
//

#include "header_bid_loader.h"

#include "../oneten_ad_sdk.h"

BEGIN_NAMESPACE_ONETEN_AD

HeaderBidLoader::HeaderBidLoader(std::shared_ptr<LoaderInterface> loader): MainLoader(loader) {
    otlog_info << "";
    ad_source_service_ = std::make_shared<AdSourceService>();
}

void HeaderBidLoader::Flow(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement) {
    super_class::Flow(ad_source, placement);
    if (ad_source->GetRequestType() != AdSource::RequestType::kS2S &&
        ad_source->GetRequestType() != AdSource::RequestType::kC2S) {
        return;
    }
    otlog_info << "";
}

void HeaderBidLoader::End() {
    super_class::End();
    otlog_info << "";
};


END_NAMESPACE_ONETEN_AD
