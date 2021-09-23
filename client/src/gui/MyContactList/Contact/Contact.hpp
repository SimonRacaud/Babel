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
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QObject>

/**
 * Config
 */
#define CONTACT_BUTT_WIDTH 70
#define CONTACT_MAX_WIDTH 300

namespace GUI
{
    class Contact : public QObject {
        Q_OBJECT

      public:
        Contact(QVBoxLayout &parent, QString const &userName);
        virtual ~Contact();

        void enableCall();
        void disableCall();

      private slots:
        void slotCallContact() noexcept;
        void slotRemoveContact() noexcept;

      private:
        QWidget *_widthControl;
        QHBoxLayout *_layout;
        QLabel *_label;
        QPushButton *_buttonCall;
        QPushButton *_buttonRemove;
    };
}

#endif // CONTACT_HPP
