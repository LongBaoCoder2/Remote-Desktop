#pragma once

#include "IModel.hpp"
#include "User.hpp"
#include <vector>
#include <memory>

class Admin : public IModel
{
private:
    std::vector<std::shared_ptr<User>> ListUserAccess;

public:
    Admin(std::string IP, std::string IPAddress = "");

    virtual ~Admin() {};

    virtual Owned GetTypeOwned() const override;

    std::shared_ptr<User> GetUserByIndex(int index);

    std::shared_ptr<User> GetUserByIP(const std::string& IPAddress);

    bool AppendUser(std::shared_ptr<User> user);

    bool RemoveUser(int index);

    bool RemoveUser(const std::string& IPAddress);
};
