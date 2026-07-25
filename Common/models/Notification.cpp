#include "Notification.h"

int Notification::idCounter = 1;

Notification::Notification()
    :seen(false),createdAt(QDateTime::currentDateTime()) {};

Notification::Notification(const QString &message)
    :id(idCounter++),message(message), seen(false), createdAt(QDateTime::currentDateTime()) {};

int Notification::getId() const{ return id;}
void Notification::setId(const int i) { id = i;}

QString Notification::getMessage() const { return message; }

bool Notification::isRead() const { return seen; }
void Notification::markAsRead() { seen = true; }

QDateTime Notification::getCreatedAt() const { return createdAt; }
void Notification::setCreatedAt(const QDateTime& date) { createdAt = date;}