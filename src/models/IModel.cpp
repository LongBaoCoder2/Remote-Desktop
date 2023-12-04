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
