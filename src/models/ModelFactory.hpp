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
// Factory setup
class ModelCreatorBase {
public:
    ModelCreatorBase() {}
    virtual ~ModelCreatorBase() {}
    virtual std::unique_ptr<IModel> Create(std::string ID) = 0;
};

template< class T >
class ModelCreator : public ModelCreatorBase {
public:
    ModelCreator() {}
    virtual ~ModelCreator() {}
    virtual std::unique_ptr<IModel> Create(std::string ID) { return std::make_unique<T>(ID); }
};

class ModelFactory
{
public:
    ModelFactory()
    {
        Register<Owned::ADMIN, Admin>();
        Register<Owned::USER, User>();
    }

    std::unique_ptr<IModel> Create(Owned type, std::string ID)
    {
        TSwitchToModel::iterator it = m_switchToModel.find(type);
        if (it == m_switchToModel.end()) return nullptr;
        return it->second->Create(ID);
    }

private:
    template< Owned type, typename T >
    void Register()
    {
        Register(type, std::make_unique<ModelCreator<T>>());
    }

private:
    void Register(Owned type, std::unique_ptr<ModelCreatorBase>&& creator)
    {
        m_switchToModel[type] = std::move(creator);
    }

    typedef std::map<Owned, std::unique_ptr<ModelCreatorBase> > TSwitchToModel;
    TSwitchToModel m_switchToModel;
};

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
