/*
** EPITECH PROJECT , 2021
** Controller
** File description:
** simon
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QThread>

class Controller : public QObject {
    Q_OBJECT
    QThread workerThread;
  public:
    Controller();
    virtual ~Controller();

  public slots:
    // todo ?

  signals:
    void operate();
};

#endif // CONTROLLER_HPP
