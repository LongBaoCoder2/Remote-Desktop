#pragma once
#include <string>
#include <cstdint>

// Specify type of User
#ifndef OWNED
#define OWNED
enum class Owned : uint8_t
{
    ADMIN = 0,
    USER,
#define CLIENT ADMIN 
#define SERVER USER 
};
#endif

// Interface Model: User vs Admin
class IModel
{
public:
    // Default Constructor with parameter ID and IPAddress
    IModel(std::string ID, std::string IPAddress = "")
        : ID(ID), IPAddress(IPAddress) {}


    virtual ~IModel() {};

    // Setter and Getter ID
    void SetID(std::string);
    std::string GetID() const;

    // Setter and Getter IPAddress
    void SetIPAddress(std::string);
    std::string GetIPAddress() const;

    // virtual bool checkValidation() = 0;
    // Get Owned: Server or Client
    virtual Owned GetTypeOwned() const = 0;

protected:
    // ID Model - username
    std::string ID;
    std::string IPAddress;
};
