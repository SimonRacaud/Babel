/*
** EPITECH PROJECT , 2021
** DialogueBox
** File description:
** simon
*/

#include "DialogueBox.hpp"
#include "gui/Window/Window.hpp"

using namespace GUI;

extern std::unique_ptr<GUI::Window> window;

bool DialogueBox::question(QString const &title, QString const &message)
{
    int response = QMessageBox::question(::window.get(), title, message, QMessageBox::Yes | QMessageBox::No);

    return response == QMessageBox::Yes;
}

void DialogueBox::info(QString const &message)
{
    DialogueBox::information(::window.get(), "Information", message);
}

void DialogueBox::error(QString const &message)
{
    DialogueBox::critical(::window.get(), "An error occurred", message);
}