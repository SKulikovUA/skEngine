#pragma once

#include "../interface/IModel.hpp"

class Model: public IModel
{
public:
    Model();

    virtual bool loadFromFile(const std::string& fileName) override final;
    virtual void draw() override final;

    virtual ~Model()
    {
    }
};