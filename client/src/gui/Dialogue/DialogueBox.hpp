/*
** EPITECH PROJECT , 2021
** DialogueBox
** File description:
** simon
*/

#ifndef DIALOGUEBOX_HPP
#define DIALOGUEBOX_HPP

#include <QMessageBox>

namespace GUI
{
    class DialogueBox : public QMessageBox {
      public:
        DialogueBox() = default;
        virtual ~DialogueBox() = default;

        static bool question(QString const &title, QString const &message);
        static void info(QString const &message);
        static void error(QString const &message);
    };
}

#endif // DIALOGUEBOX_HPP
