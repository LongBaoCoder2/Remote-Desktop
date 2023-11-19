#pragma once
#include "IModel.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include <memory>
#include <map>

namespace CONFIG_STRING
{
    const int MIN_LENGTH = 4;
    const int MAX_LENGTH = 10;
};

// Model creator based on Factory Design Pattern
class ModelFactory
{

public:
    // static std::unique_ptr<IModel> CreateModel(const Owned &);
    static std::unique_ptr<Admin> CreateAdmin(std::string ID, std::string Password, std::string IPAddress);

    static std::shared_ptr<User> CreateUser(std::string ID, std::string IPAddress);
};

std::unique_ptr<Admin> ModelFactory::CreateAdmin(std::string ID,
                                                 std::string Password,
                                                 std::string IPAddress = "")
{
    return std::make_unique<Admin>(ID, IPAddress, Password);
}

std::shared_ptr<User> ModelFactory::CreateUser(std::string ID,
                                               std::string IPAddress = "")
{
    return std::make_shared<User>(ID, IPAddress);
}

// Class to check validation ID when login
class CheckValidation
{
public:
    static bool checkValidationUser(std::string ID) noexcept
    {
        if (ID.size() < CONFIG_STRING::MIN_LENGTH || ID.size() > CONFIG_STRING::MAX_LENGTH)
            return false;

        if (!std::isalpha(static_cast<unsigned char>(ID.front()))) // paranoia: avoid crashing with empty username
            return false;

        return true;
    }

    static bool checkValidationAdmin(std::string ID, std::string Password) noexcept
    {
        if (ID.compare("admin") == 0 && Password.compare("admin") == 0)
            return true;
        return false;
    }
};
