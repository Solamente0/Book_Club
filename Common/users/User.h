#ifndef USER_H
#define USER_H

#include <QVector>
#include <QMap>

#include "../models/Book.h"
#include "Member.h"
#include "../models/Cart.h"
#include "../models/Shelf.h"

class User: public Member
{
private:
    QVector<genre> favoriteGenres;
    QVector<Book> purchasedBooks;
    QVector<Book> savedBooks;
    Cart cart;
    QMap<int, int> lastReadPages;
    QVector<Shelf> shelves;
    bool firstLogin;
public:
    User();
    User(const QString& username, const QString& hashedPassword, const QString& securityAnswer);
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
    QVector<Shelf> getShelves() const;
    void addShelf(const Shelf &shelf);
    void removeShelf(const QString &shelfName);
    void renameShelf(const QString &oldName, const QString &newName);
    Shelf* findShelf(const QString &name); 

    bool isFirstLogin() const;
    void setFirstLogin(bool first);

};

#endif