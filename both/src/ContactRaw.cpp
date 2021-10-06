/*
 * EPITECH PROJECT, 2021
 * src
 * File description:
 * ContactRaw.cpp - Created: 06/10/2021
 */

#include "ContactRaw.hpp"

std::ostream &operator<<(std::ostream &stream, const ContactRaw &contactRaw)
{
    stream << "ContactRaw:" << std::endl;
    stream << "\tusername: [" << contactRaw.username << "]" << std::endl;
    stream << "\tcontactName: [" << contactRaw.contactName << "]" << std::endl;
    return stream;
}