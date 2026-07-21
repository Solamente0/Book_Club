#include "PublisherManager.h"

PublisherManager::PublisherManager() {}

bool PublisherManager::usernameExists(const QString &username) const
{
    for (const Publisher &p : registeredPublishers) {
        if (p.getUsername() == username) {
            return true;
        }
    }
    return false;
}

bool PublisherManager::registerPublisher(const Publisher &newPublisher)
{
    if (usernameExists(newPublisher.getUsername())) {
        return false;
    }
    registeredPublishers.append(newPublisher);
    return true;
}

bool PublisherManager::authenticate(const QString &username, const QString &password, Publisher &foundPublisher)
{
    for (const Publisher &p : registeredPublishers) {
        if (p.getUsername() == username && p.getPassword() == password) {
            foundPublisher = p;
            return true;
        }
    }
    return false;
}

bool PublisherManager::updatePublisher(const Publisher &updatedPublisher)
{
    for (int i = 0; i < registeredPublishers.size(); ++i) {
        if (registeredPublishers[i].getId() == updatedPublisher.getId()) {
            registeredPublishers[i] = updatedPublisher;
            return true;
        }
    }
    return false;
}

bool PublisherManager::getSecurityAnswer(const QString &username, QString &answerOut)
{
    for (const Publisher &p : registeredPublishers) {
        if (p.getUsername() == username) {
            answerOut = p.getSecurityAnswer();
            return true;
        }
    }
    return false;
}

bool PublisherManager::resetPassword(const QString &username, const QString &securityAnswer, const QString &newPassword)
{
    for (int i = 0; i < registeredPublishers.size(); ++i) {
        if (registeredPublishers[i].getUsername() == username &&
            registeredPublishers[i].getSecurityAnswer() == securityAnswer) {
            registeredPublishers[i].setPassword(newPassword);
            return true;
        }
    }
    return false;
}

bool PublisherManager::isUsernameTakenByAnother(const QString &username, int excludeId) const
{
    for (const Publisher &p : registeredPublishers) {
        if (p.getUsername() == username && p.getId() != excludeId) {
            return true;
        }
    }
    return false;
}