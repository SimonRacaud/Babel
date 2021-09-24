/*
** EPITECH PROJECT , 2021
** ICallManager
** File description:
** simon
*/

#ifndef ICALLMANAGER_HPP
#define ICALLMANAGER_HPP

namespace GUI {
    class ICallManager {
      public:
        virtual ~ICallManager() = default;

        virtual void setCallMembers(std::vector<QString> const &usernames) = 0;
        virtual void removeMember(QString const &username) = 0;
        virtual void addMember(QString const &username) = 0;
        virtual void clearMemberList() = 0;
    };
}

#endif // ICALLMANAGER_HPP
