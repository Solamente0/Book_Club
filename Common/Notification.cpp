#include "Notification.h"

Notification::Notification()
    :seen(false),createdAt(QDateTime::currentDateTime()) {};

Notification::Notification(const QString &message)
    :message(message), seen(false), createdAt(QDateTime::currentDateTime()) {};

int Notification::getId() const{ return id;}
void Notification::setId(const int i) { id = i;}

QString Notification::getMessage() const { return message; }

bool Notification::isRead() const { return seen; }
void Notification::markAsRead() { seen = true; }

QDateTime Notification::getCreatedAt() const { return createdAt; }
void Notification::setCreatedAt(const QDateTime& date) { createdAt = date;}