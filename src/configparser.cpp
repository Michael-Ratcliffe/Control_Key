#include "configparser.h"

ConfigParser::ConfigParser()
{

}

ConfigParser::ConfigParser(std::string filePath)
{
    Open(filePath);
}

void ConfigParser::Open(std::string filePath)
{
    Close();
    _ifile.open(filePath);
    if(!_ifile.is_open() && !filePath.empty())
    {
        std::cout << "Failed To Open File: " << filePath << std::endl;
        //throw std::exception();
        return;
    }

    else if(_ifile.is_open())
        std::cout << "Opened Config File: " << filePath << std::endl;
}

void ConfigParser::Close()
{
    if(_ifile.is_open())
    {
        _ResetFile();
        _ifile.close();
        std::cout << "Closed Config File" << std::endl;
    }
}

std::string ConfigParser::GetSection(std::string sectionName)
{
    _ResetFile();
    std::string section;
    bool parse = false;

    while(_ifile.good())
    {
        std::string line;
        std::getline(_ifile, line);
        if(line.front() != '#' && !line.empty())
        {
            if(parse)
            {
                if(line.front() == '[' || line.empty())
                {
                    parse = false;
                    break;
                }
                //std::cout << line << std::endl;
                section += line;
                section += "\n";
            }

            else if(line == sectionName)
                parse = true;
        }
    }
    return section;
}

std::string ConfigParser::GetAll()
{
    _ResetFile();
    std::string section;

    while(_ifile.good())
    {
        std::string line;
        std::getline(_ifile, line);

        if(line.front() != '#' && !line.empty())
        {
            section += line;
            section += "\n";
        }
    }
    return section;
}

void ConfigParser::_ResetFile()
{
    _ifile.clear();
    _ifile.seekg(0);
}

ConfigParser::~ConfigParser()
{
    Close();
}
