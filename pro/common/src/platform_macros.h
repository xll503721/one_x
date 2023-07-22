#pragma once


enum class OneTenPlatformType {
    kOneTenPlatformTypeiOS,
    kOneTenPlatformTypeMac,
    kOneTenPlatformTypeAndroid,
};

bool isPlatform(OneTenPlatformType type) {
    bool is_platform = false;
    switch (type) {
#ifdef OS_IOS
        case OneTenPlatformType::kOneTenPlatformTypeiOS: {
            is_platform = true;
        }
            break;
#endif
#ifdef OS_MAX
        case OneTenPlatformType::kOneTenPlatformTypeMac: {

            is_platform = true;
        }
            break;
#endif
#ifdef OS_ANDROID
        case OneTenPlatformType::kOneTenPlatformTypeAndroid: {
            is_platform = true;
        }
            break;
#endif
            
        default:
            break;
    }
    return is_platform;
}

OneTenPlatformType platform() {
#ifdef OS_IOS
    return OneTenPlatformType::kOneTenPlatformTypeiOS;
#endif
#ifdef OS_MAX
    return OneTenPlatformType::kOneTenPlatformTypeMac;
#endif
#ifdef OS_ANDROID
    return OneTenPlatformType::kOneTenPlatformTypeAndroid;
#endif
}
