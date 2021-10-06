/*
** EPITECH PROJECT , 2021
** Worker
** File description:
** simon
*/

#include "NetworkWorker.hpp"

using namespace Network;

extern NetworkManager networkManager;

NetworkWorker::NetworkWorker()
{
}

void NetworkWorker::work()
{
    while (true) {
        std::cerr << "Is it call?" << std::endl;
        try {
            networkManager.streamAudio();
        } catch (std::exception const &e) {
            std::cerr << "An exception occured. " << e.what() << std::endl;
        }
        this->processClientCommunication();
        this->processServerCommunication();
    }
}

void NetworkWorker::processServerCommunication()
{
    TCPTramExtract<BUFFER_SIZE> data = networkManager.receiveFromServer();
    TramAction action = data.getAction();
    TramType type = data.getType();

    if (data.isCorrectTram() == false) {
         emit networkRequestFailed(QString(data.getStrError().c_str()));
    } else {
        if (action == TramAction::GET) {
            if (type == TramType::USER) {
                std::vector<UserRaw> users = data.getListOf<UserRaw>();
                if (users.size() != 1) {
                    emit networkRequestFailed("Network : get user - Bad user count.");
                } else {
                    emit userReceived(users[0]);
                }
            } else if (type == TramType::CONTACT) {
                std::vector<ContactRaw> contacts = data.getListOf<ContactRaw>();
                emit contactListReceived(contacts);
            }
        } else if (action == TramAction::POST) {
            if (type == TramType::USER) {
                std::vector<UserRaw> loggedUser = data.getListOf<UserRaw>();
                if (loggedUser.size() != 1) {
                    emit networkRequestFailed("Network : post user - Bad user count.");
                } else {
                    emit logged(loggedUser[0]);
                }
            } else if (type == TramType::CONTACT) {
                std::vector<ContactRaw> newContact = data.getListOf<ContactRaw>();
                if (newContact.size() != 1) {
                    emit networkRequestFailed("Network : post contact - Bad contact count.");
                } else {
                    emit contactAdded(newContact[0]);
                }
            }
        } else if (action == TramAction::DELETE) {
            if (type == TramType::CONTACT) {
                std::vector<ContactRaw> removedContact = data.getListOf<ContactRaw>();
                if (removedContact.size() != 1) {
                    emit networkRequestFailed("Network : delete contact - Bad contact count.");
                } else {
                    emit contactRemoved(removedContact[0]);
                }
            }
        }
    }
}

void NetworkWorker::processClientCommunication()
{
    auto [tram, user] = networkManager.receiveFromClient();

    if (tram.isCorrectTram() == false) {
        emit networkRequestFailed(QString(tram.getStrError().c_str()));
    } else {
        if (tram.getType() == TramType::USER) {
            std::vector<UserRaw> users = tram.getListOf<UserRaw>();
            emit callHandshakeReceived(users, user);
        }
    }
}