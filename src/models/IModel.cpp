#pragma once
#include "IModel.hpp"

void IModel::SetID(std::string ID)
{
    this->ID = ID;
}

std::string IModel::GetID() const
{
    return this->ID;
}

void IModel::SetIPAddress(std::string IPAddress)
{
    this->IPAddress = IPAddress;
}

std::string IModel::GetIPAddress() const
{
    return this->IPAddress;
}

// bool IModel::checkValidation()
// {
//     const size_t size = this->ID.size();
//     if (size > CONFIG_STRING::MAX_LENGTH || size < CONFIG_STRING::MIN_LENGTH)
//         return false;

//     if (this->ID.empty() || !std::isalpha(static_cast<unsigned char>(this->ID.front())))
//         return false;

//     return true;
// }