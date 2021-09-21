/*
** EPITECH PROJECT , 2021
** Window
** File description:
** simon
*/

#ifndef BABEL_WINDOW_HPP
#define BABEL_WINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QMdiArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "gui/MyContactList/MyContactList.hpp"
#include "gui/AddContact/AddContact.hpp"
#include "gui/Account/Account.hpp"

namespace GUI
{
    class Window : public QMainWindow {
      public:
        Window();
        virtual ~Window() = default;

      private:
    };
} // namespace GUI

#endif // BABEL_WINDOW_HPP
