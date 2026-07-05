#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QString>
#include <QDateTime>

class Notification
{
private:
    int id;
    QString message;
    bool seen;
    QDateTime createdAt;
public:
    Notification();
    Notification(const QString& message);

    int getId() const;
    void setId(const int i);

    QString getMessage() const;

    bool isRead() const;
    void markAsRead();

    QDateTime getCreatedAt() const;
    void setCreatedAt(const QDateTime& date);

};


#endif