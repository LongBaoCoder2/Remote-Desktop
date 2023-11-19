#include "User.hpp"

// bool User::checkValidation()
// {
//     return IModel::checkValidation();
// }

Owned User::GetTypeOwned() const
{
    return Owned::USER;
}