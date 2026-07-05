#include "Admin.h"

Admin::Admin(const QString& username, const QString& password, const QString& securityAnswer)
    : Member(username, password, securityAnswer) {};

QString Admin::role() const{return "Admin";}