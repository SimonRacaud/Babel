/*
** EPITECH PROJECT , 2021
** IMyContactList
** File description:
** simon
*/

#ifndef IMYCONTACTLIST_HPP
#define IMYCONTACTLIST_HPP

#include "IContact.hpp"

namespace GUI {
    class IMyContactList {
      public:
        virtual ~IMyContactList() = default;

        virtual void addContact(QString const &username) = 0;
        virtual void enableCallButtons() = 0;
        virtual void removeContact(IContact const &contact) = 0;
    };
}

#endif // IMYCONTACTLIST_HPP
