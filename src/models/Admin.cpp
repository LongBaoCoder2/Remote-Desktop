#include "Admin.hpp"

void Admin::SetPassword(std::string Password)
{
    this->Password = Password;
}

std::string Admin::GetPassword() const
{
    return this->Password;
}

// bool Admin::checkValidation() const
// {
//     if (this->GetID().compare("admin") || this->GetPassword().compare("admin"))
//         return true;
//     return false;
// }

Owned Admin::GetTypeOwned() const
{
    return Owned::ADMIN;
}

std::shared_ptr<User> Admin::GetUser(int index) const
{
    if (index >= ListUserAccess.size())
        return nullptr;

    return ListUserAccess[index];
}

std::shared_ptr<User> Admin::GetUser(const std::string &IPAddress) const
{
    for (const auto &user : ListUserAccess)
    {
        if ((*user).GetIPAddress() == IPAddress)
            return user;
    }

    return nullptr;
}

bool Admin::AppendUser(std::shared_ptr<User> user)
{
    try
    {
        ListUserAccess.push_back(std::move(user));
        return true;
    }
    catch (std::exception &e)
    {
        return false;
    }
}

bool Admin::RemoveUser(int index)
{
    if (index >= ListUserAccess.size())
        return false;

    ListUserAccess.erase(ListUserAccess.begin() + index);
    return true;
}

bool Admin::RemoveUser(const std::string &IPAddress)
{
    size_t index = 0;
    for (const auto &user : ListUserAccess)
    {
        if ((*user).GetIPAddress() == IPAddress)
            break;

        index++;
    }
    if (index >= ListUserAccess.size())
        return false;

    ListUserAccess.erase(ListUserAccess.begin() + index);
    return true;
}