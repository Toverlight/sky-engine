#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional> // 用于 std::function

class TypeInfo;
class PropertyInfo;

// 全局反射注册表
extern std::map<std::string, TypeInfo*> GReflectionRegistry;

// 注册TypeInfo的函数
void RegisterType(TypeInfo* type_info);

// 属性信息抽象类
class PropertyInfo {
public:
    std::string PropertyName;
    std::string TypeName;

    PropertyInfo(const std::string& property_name, const std::string& type_name)
        : PropertyName(property_name), TypeName(type_name) {}


    virtual void* GetValuePtr(void* object_ptr) const = 0;
    virtual void SetValuePtr(void* object_ptr, const void* value_ptr) const = 0;

    virtual PropertyInfo* Clone() const = 0;    
    virtual ~PropertyInfo() = default;
};

// 可反射的类的元数据
class TypeInfo {
public:
    std::string TypeName;
    std::vector<PropertyInfo*> Properties;
    std::function<void*()> CreateInstanceFn;

    TypeInfo(const std::string& type_name, std::function<void*()> create_instance)
        : TypeName(type_name), CreateInstanceFn(create_instance) {
            RegisterType(this); // 构造时自动注册到全局反射注册表
        }
    
    ~TypeInfo() {
        for (auto prop : Properties) {
            delete prop; // 确保释放属性信息
        }
        Properties.clear();
    }

    void AddProperty(PropertyInfo* property_info) {
        Properties.push_back(property_info);
    }

    PropertyInfo* GetProperty(const std::string& property_name) const {
        for (auto prop : Properties) {
            if (prop->PropertyName == property_name) {
                return prop;
            }
        }
        return nullptr; // 如果没有找到，返回nullptr
    }

    void* CreateInstance() const {
        if (CreateInstanceFn) {
            return CreateInstanceFn();
        }
        return nullptr; // 如果没有提供创建实例的函数，返回nullptr
    }

};