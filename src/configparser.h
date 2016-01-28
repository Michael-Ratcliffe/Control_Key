#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

class ConfigParser
{
public:
    ConfigParser();
    ConfigParser(std::string filePath);
    ~ConfigParser();
    void Open(std::string filePath);
    void Close();
    std::string GetSection(std::string sectionName);
    std::string GetAll();

    template<class C>
    void FillValue(C &value, std::string varName, std::string sectionName)
    {
        std::stringstream ss(GetSection(sectionName));
        std::string key;
        //Get first part of the config line
        //Example line, "someconfiguration 3" key would equal "someconfiguration"
        while(ss >> key)
        {
            if(key == varName)
            {
                ss >> value;
                std::cout << varName << " Is Set To " << value << std::endl;
            }
        }
        _ResetFile();
    }

    template<class Key, class Value>
    void FillMap(std::map<Key, Value> &map, std::string sectionName)
    {
        Key key;
        Value value;
        std::stringstream ss(GetSection(sectionName));

        while(ss >> key >> value)
        {
            std::cout << "Mapping <" << key <<"> To <" << value << ">" <<std::endl;
            map[key] = value;
        }
        _ResetFile();
    }

    template<class Key, class Value>
    void FillMap(std::map<Key, Value> &map)
    {
        Key key;
        Value value;
        std::stringstream ss(GetAll());

        while(ss >> key >> value)
        {
            std::cout << "Mapping <" << key <<"> To <" << value << ">" <<std::endl;
            map[key] = value;
        }
        _ResetFile();
    }

private:
    std::ifstream _ifile;
    void _ResetFile();
};

#endif
