#pragma once
#include "IModel.hpp"
#include <memory>

class User : public IModel
{
public:
    User(std::string ID, std::string IPAddress)
        : IModel(ID, IPAddress) {}
    User(const User &user) = delete;
    virtual ~User(){};

    virtual Owned GetTypeOwned() const override;
};
