#pragma once

#include "IModel.hpp"
#include "User.hpp"
#include <vector>
#include <memory>

class Admin : public IModel
{
private:
    std::string Password;
    std::vector<std::shared_ptr<User>> ListUserAccess;

public:
    Admin(std::string IP, std::string Password, std::string IPAddress = "")
        : IModel(IP, IPAddress), Password(Password)
    {
    }

    // Not allow copying
    Admin(const Admin &) = delete;

    virtual ~Admin(){};

    virtual Owned GetTypeOwned() const override;

    void SetPassword(std::string);

    std::string GetPassword() const;

    std::shared_ptr<User> GetUser(int index) const;

    std::shared_ptr<User> GetUser(const std::string &IPAddress) const;

    bool AppendUser(std::shared_ptr<User> user);

    bool RemoveUser(int index);

    bool RemoveUser(const std::string &IPAddress);
};
