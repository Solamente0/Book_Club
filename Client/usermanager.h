#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QVector>
#include <QString>
#include "User.h"

class UserManager
{
private:
    QVector<User> registeredUsers;

public:
    UserManager();

    bool registerUser(const User &newUser);
    bool usernameExists(const QString &username) const;
    bool authenticate(const QString &username, const QString &password, User &foundUser);
    bool getSecurityAnswer(const QString &username, QString &answerOut);
    bool resetPassword(const QString &username, const QString &securityAnswer, const QString &newPassword);
    bool isUsernameTakenByAnotherUser(const QString &username, int excludeUserId) const;
    bool updateUser(const User &updatedUser);
};

#endif // USERMANAGER_H