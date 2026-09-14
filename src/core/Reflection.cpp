#include "Reflection.h"
#include <map>

std::map<std::string, TypeInfo*> GReflectionRegistry;

void RegisterType(TypeInfo* type_info) {
    if (GReflectionRegistry.find(type_info->TypeName) == GReflectionRegistry.end()) {
        GReflectionRegistry[type_info->TypeName] = type_info;
    } else {
        // 如果类型已经注册，可以选择覆盖或忽略
        // 这里选择忽略
    }
}

TypeInfo* GetTypeInfo(const std::string& type_name) {
    auto it = GReflectionRegistry.find(type_name);
    if (it != GReflectionRegistry.end()) {
        return it->second;
    }
    return nullptr; // 如果没有找到，返回nullptr
}