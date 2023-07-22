any_think_sdk_path=$(pwd)

function replace_log_print_level {
    echo "replace_log_print_level start"
    atloger_path=$any_think_sdk_path/AnyThinkSDK/Internal/Log/ATAdLogger.m
        echo "current_path:" $atloger_path
    if [ -f "$atloger_path" ]; then
        echo "ATAdLogger.m file found!"
    else 
        echo "$atloger_path"
        echo -e "\033[31mATAdLogger.m file not found!check path, run shell under path:./AnyThinkSDK\033[0m"
        exit -1
    fi

    old_log_print_level="static const ATLogType logType = ATLogTypeExternal | ATLogTypeTemporary | ATLogTypeInternal | ATLogTypeProcess;"
    new_log_print_level="static const ATLogType logType = ATLogTypeExternal | ATLogTypeTemporary;"
    sed -i '' "s/$old_log_print_level/$new_log_print_level/g" $atloger_path
}

function replace_topon_debug_macro {
    echo "replace_topon_debug_macro start"
    project_path=$any_think_sdk_path/AnyThinkSDK.xcodeproj/project.pbxproj
    if [ -f "$project_path" ]; then
        echo "project.pbxproj file found!"
    else 
        echo "$project_path"
        echo -e "\033[31mproject.pbxproj file not found!\033[0m"
        exit -1
    fi

    old_topon_debug_macro="\"TOPONDEBUG=1\","
    new_topon_debug_macro=""
    sed -i '' "s/$old_topon_debug_macro/$new_topon_debug_macro/g" $project_path
}

function main() {
    replace_log_print_level
    replace_topon_debug_macro
}

main
