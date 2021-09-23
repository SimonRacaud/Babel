/*
** EPITECH PROJECT , 2021
** AddContact
** File description:
** simon
*/

#include "AddContact.hpp"

using namespace GUI;

AddContact::AddContact() : QGroupBox("Add Contact")
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QWidget *widthControl = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    _apply = new QPushButton("Apply");
    _input = new QLineEdit;

    // Link
    this->setLayout(mainLayout);
    mainLayout->addWidget(widthControl);
    widthControl->setLayout(layout);
    layout->addWidget(_input);
    layout->addWidget(_apply);
    // Config
    mainLayout->setAlignment(Qt::AlignLeft);
    widthControl->setMaximumWidth(ADD_CONTACT_MAX_WIDTH);
    _input->setPlaceholderText("username");
    /**
     * TODO:
     * Apply button event => empty input + add new contact
     */
}