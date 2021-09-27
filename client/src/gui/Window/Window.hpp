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
#include <QObject>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "gui/MyContactList/MyContactList.hpp"
#include "gui/AddContact/AddContact.hpp"
#include "gui/Account/Account.hpp"
#include "gui/CallManager/CallManager.hpp"
#include "gui/Options/Options.hpp"
#include "IWindow.hpp"
#include "IODevices.hpp"

namespace GUI
{
    class Window : public QMainWindow, public IWindow {
        Q_OBJECT

      public:
        Window(QApplication &app);
        virtual ~Window() = default;

        void hideOptions();
      private slots:
        void showOptions();

      private:
        QApplication &_app;
        Options *_winOption;
        MyContactList *_contactBox;
        AddContact *_addContactBox;
        Account *_account;
        CallManager *_callManager;

        PortAudioCaps::IODevices _ioDevices;
    };
} // namespace GUI

#endif // BABEL_WINDOW_HPP
