//
//  oneten_ad_sdk_delegate.h
//  OneTenSDK
//
//  Created by li zhixuan on 2023/3/29.
//

#ifndef ONETEN_AD_SDK_AD_SDK_DELEGATE_H
#define ONETEN_AD_SDK_AD_SDK_DELEGATE_H

BEGIN_NAMESPACE_ONETEN_AD
class AdSDKDelegate {
    
public:
    void LoadSucceed();
    void ShowSucceed();
    void ClickSucceed();
    void CloseSucceed();
    void SetOCPrt(void* prt);
    
private:
    void* oc_prt_;
    
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SDK_DELEGATE_H */
