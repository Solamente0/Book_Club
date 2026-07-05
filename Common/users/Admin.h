#ifndef ADMIN_H
#define ADMIN_H

#include "Member.h"

class Admin : public Member
{
public:
    Admin(const QString& username, const QString& password, const QString& securityAnswer);
    QString role() const override;
};

#endif