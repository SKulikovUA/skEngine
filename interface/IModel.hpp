#pragma once
#include <string>

class IModel
{
public:
    virtual ~IModel() = default;

    virtual bool loadFromFile(const std::string& fileName) = 0;
    virtual void draw() = 0;
};