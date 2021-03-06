﻿#pragma once

#include <boost/serialization/singleton.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>

class ConfigureData : protected boost::serialization::singleton<ConfigureData>
{
public:

    static ConfigureData* GetInstancePtr()
    {
        ConfigureData* ptr = &ConfigureData::get_mutable_instance();
        return ptr;
    }

    bool Initialize(const std::string configure_file_path);
    bool LoadCofigureFile(const std::string configure_file_path);			// 설정파일을 읽는다.
    bool WriteConfigureFile();											// 설정파일을 쓴다.

    // 사용할 설정 데이터를 얻어온다
    template<typename _T>
    const _T GetConfigureData(std::string key, const _T default_value);

    // 사용할 설정 데이터를 셋팅한다.
    void SetConfigureData(std::string key, uint32_t value);
    void SetConfigureData(std::string key, std::string value);

    void OutConfigureData();

protected:
    ConfigureData(void);
    ~ConfigureData(void);
private:
    boost::property_tree::ptree			m_iniTree;
    std::string							m_configurePath;
};

template<typename _T>
const _T ConfigureData::GetConfigureData(std::string key, const _T default_value)
{
    return m_iniTree.get<_T>(key, default_value);
}

#define ST_CONFIG() ConfigureData::GetInstancePtr()
