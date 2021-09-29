/*
** EPITECH PROJECT , 2021
** IWindow
** File description:
** simon
*/

#ifndef IWINDOW_HPP
#define IWINDOW_HPP

namespace GUI {
    class IWindow {
      public:
        virtual ~IWindow() = default;

        virtual void hideOptions() = 0;
    };
}

#endif // IWINDOW_HPP
