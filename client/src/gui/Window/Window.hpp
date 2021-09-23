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
#include "gui/CallManager/CallManager.hpp"
#include "gui/Options/Options.hpp"

namespace GUI
{
    class Window : public QMainWindow {
      public:
        Window();
        virtual ~Window() = default;

        void showOptions();

      private:
        Options *_winOption;
        MyContactList *_contactBox;
        AddContact *_addContactBox;
        Account *_account;
        CallManager *_callManager;
    };
} // namespace GUI

#endif // BABEL_WINDOW_HPP
