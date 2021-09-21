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

namespace GUI
{
    class Window : public QMainWindow {
      public:
        Window();
        virtual ~Window() = default;

      private:
        QPushButton *_test;
    };
} // namespace GUI

#endif // BABEL_WINDOW_HPP
