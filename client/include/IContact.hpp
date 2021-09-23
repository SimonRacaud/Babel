/*
** EPITECH PROJECT , 2021
** IContact
** File description:
** simon
*/

#ifndef ICONTACT_HPP
#define ICONTACT_HPP

namespace GUI {
    class IContact {
      public:
        virtual ~IContact() = default;

        virtual void enableCall() = 0;
        virtual void disableCall() = 0;
    };
}

#endif // ICONTACT_HPP
