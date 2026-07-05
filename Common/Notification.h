#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QString>
#include <QDateTime>

class Notification
{
private:
    QString message;
    bool seen;
    QDateTime createdAt;
public:
    Notification();
    Notification(const QString& message);

    QString getMessage() const;

    bool isRead() const;
    void markAsRead();

    QDateTime getCreatedAt() const;
    void setCreatedAt(const QDateTime& date);

};


#endif