/*
** EPITECH PROJECT , 2021
** Controller
** File description:
** simon
*/

#include "Controller.hpp"

Controller::Controller()
{
//    Worker *worker = new Worker;
//
//    worker->moveToThread(&workerThread);
//    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
//    connect(this, &Controller::operate, worker, &Worker::work);

    //connect(worker, &Worker::contactAdded, this, &Controller::handleResults);
    //connect(worker, &Worker::contactRemoved, this, &Controller::handleResults);
    //connect(worker, &Worker::logged, this, &Controller::handleResults);
    //connect(worker, &Worker::callVoiceConnect, this, &Controller::handleResults);
    //connect(worker, &Worker::networkRequestFailed, this, &Controller::handleResults);
    workerThread.start();
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}