#include "Admin.hpp"

Admin::Admin(std::string IP, std::string IPAddress)
    : IModel(IP, IPAddress)
{
}

Owned Admin::GetTypeOwned() const
{
    return Owned::ADMIN;
}

std::shared_ptr<User> Admin::GetUserByIndex(int index)
{
    return std::move(ListUserAccess[index]);
}

std::shared_ptr<User> Admin::GetUserByIP(const std::string& IPAddress)
{
    for (const auto& user : ListUserAccess)
    {
        if ((*user).GetIPAddress() == IPAddress)
            return std::move(user);
    }

    return nullptr;
}

bool Admin::AppendUser(std::shared_ptr<User> user)
{
    ListUserAccess.push_back(std::move(user));
    return true;
}

bool Admin::RemoveUser(int index)
{
    if (index >= ListUserAccess.size())
        return false;

    ListUserAccess.erase(ListUserAccess.begin() + index);
    return true;
}

bool Admin::RemoveUser(const std::string& IPAddress)
{
    size_t index = 0;
    for (const auto& user : ListUserAccess)
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