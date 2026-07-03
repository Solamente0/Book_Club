#ifndef USER_H
#define USER_H

#include <QVector>
#include <QMap>

#include "Book.h"
#include "Member.h"
#include "Cart.h"

class User: public Member
{
private:
    QVector<genre> favoriteGenres;
    QVector<Book> purchasedBooks;
    QVector<Book> savedBooks;
    Cart cart;
    QMap<int, int> lastReadPages;
    bool firstLogin;
public:
    User();
    User(QString username, QString hashedPassword, QString securityAnswer);
    QString role() const override;

    QVector<genre> getfavoriteGenres() const;
    void setFavoriteGenres(const QVector<genre> &genres);
    void addFavoriteGenre(const genre &Genre);
    QVector<Book> getpurchasedBooks() const;
    void addPurchasedBook(const Book &book);
    bool hasPurchasedBook(int bookId) const;
    QVector<Book> getSavedBooks() const;
    void addSavedBook(const Book &book);
    void removeSavedBook(int bookId);
    bool hasSavedBook(int bookId) const;
    Cart& getCart();
    int getlastReadPage(int bookId) const;
    void setLastReadPage(int bookId, int page);

    bool isFirstLogin() const;
    void setFirstLogin(bool first);

};

#endif