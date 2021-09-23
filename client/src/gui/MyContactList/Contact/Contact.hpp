/*
** EPITECH PROJECT , 2021
** Contact
** File description:
** simon
*/

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "ICallManager.hpp"

/**
 * Config
 */
#define CONTACT_BUTT_WIDTH 70
#define CONTACT_MAX_WIDTH  300

namespace GUI
{
    class Contact : public QObject {
        Q_OBJECT

      public:
        Contact(QVBoxLayout &parent, QString const &userName,
            ICallManager &callManager);
        virtual ~Contact();

        void enableCall();
        void disableCall();

      private slots:
        void slotCallContact() noexcept;
        void slotRemoveContact() noexcept;

      private:
        ICallManager &_callManager;

        QWidget *_widthControl;
        QHBoxLayout *_layout;
        QLabel *_label;
        QPushButton *_buttonCall;
        QPushButton *_buttonRemove;
    };
} // namespace GUI

#endif // CONTACT_HPP
