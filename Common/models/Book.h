#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QVector>
#include <QDateTime>

#include "Review.h"

enum class genre {
    Fiction,
    Non_fiction,
    Academic,
    Drama,
    Mystery,
    Crime,
    Romance,
    History,
    Science_fiction,
    Scary
};

class Book
{
private:
    int Id;
    QString Title;
    QString Author;
    QString PublisherUsername;
    genre Genre;
    QString Description;
    double Price;
    double Discount;
    QString imagePath;
    QString pdfPath;
    bool isActive;
    QDateTime publishDate;
    int salesCount;
    double averageRating;
    QVector<Review> Reviews;

public:
    Book(const QString& title,
         const QString& author,
         QString pubUsername,
         genre Genre,
         QString descrip,
         double Price,
         double Discount
        );

    ~Book() = default;

    int getId() const;
    QString getTitle() const;
    QString getAuthor() const;
    QString getPublisherUsername() const;
    QString getDiscription() const;
    genre getGenre() const;
    double getPrice() const;
    double getDiscount() const;
    bool getisActive() const;
    QString getImagePath() const;
    QString getPdfPath() const;
    QDateTime getPublishDate() const;
    int getSalesCount() const;
    double getAverageRating() const;
    double getFinalPrice() const;

    void setId(const int id);
    void setTitle(const QString& newTitle);
    void setAuthor(const QString& newAuthor);
    void setGenre(genre newGenre);
    void setPrice(double newPrice);
    void setDiscount(double newDiscount);
    void setPublisherUsername(const QString &newUsername);
    void setDescription(const QString &description);
    void setImagePath(const QString &newpath);
    void setPdfPath(const QString &newpath);
    void setisActive(bool newisActive);
    void setPublishDate(const QDateTime &date);
    void setSalesCount(int count);

    void addReview(const Review& review);
    double calculateAverageRating() const;
};

#endif