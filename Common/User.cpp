#include "User.h"

User::User():Member(), firstLogin(true){}

User::User(const QString& username, const QString& password, const QString& securityAnswer)
    : Member(username, password, securityAnswer), firstLogin(true) {}

QString User::role() const{ return "User";}

QVector<genre> User::getfavoriteGenres() const {return favoriteGenres;}
void User::setFavoriteGenres(const QVector<genre> &genres) { favoriteGenres = genres; }
void User::addFavoriteGenre(const genre &Genre)
{
    if (!favoriteGenres.contains(Genre) && favoriteGenres.size() < 3)
        favoriteGenres.append(Genre);
}

QVector<Book> User::getpurchasedBooks() const {return purchasedBooks;}
void User::addPurchasedBook(const Book &book) {
    if (!hasPurchasedBook(book.getId()))
        purchasedBooks.append(book);
}

bool User::hasPurchasedBook(int bookId) const{
    for (const Book &b : purchasedBooks)
        if (b.getId() == bookId)
            return true;
    return false;
}

QVector<Book> User::getSavedBooks() const{ return savedBooks;}
void User::addSavedBook(const Book &book) {
    if (!hasSavedBook(book.getId()))
        savedBooks.append(book);
}

void User::removeSavedBook(int bookId) {
    for (int i = 0; i < savedBooks.size(); i++) {
        if (savedBooks[i].getId() == bookId) {
            savedBooks.removeAt(i);
            break;
        }
    }
}

bool User::hasSavedBook(int bookId) const{
    for (const Book &b : savedBooks)
        if (b.getId() == bookId) 
            return true;
    return false;
}

Cart& User::getCart() { return cart; }

int User::getlastReadPage(int bookId) const
{
    return lastReadPages.value(bookId, 0);
}
void User::setLastReadPage(int bookId, int page)
{
    lastReadPages[bookId] = page;
}

QVector<Shelf> User::getShelves() const{ return shelves;}

void User::addShelf(const Shelf &shelf) {
    if (!findShelf(shelf.getName()))
        shelves.append(shelf);
}

void User::removeShelf(const QString &shelfName) {
    for (int i = 0; i < shelves.size(); ++i) {
        if (shelves[i].getName() == shelfName) {
            shelves.removeAt(i);
            break;
        }
    }
}

void User::renameShelf(const QString &oldName, const QString &newName) {
    Shelf *shelf = findShelf(oldName);
    if (shelf)
        shelf->setName(newName);
}

Shelf* User::findShelf(const QString &name) {
    for (Shelf &s : shelves)
        if (s.getName() == name)
            return &s;
    return nullptr;
}

bool User::isFirstLogin() const { return firstLogin; }
void User::setFirstLogin(bool first) { firstLogin = first;}