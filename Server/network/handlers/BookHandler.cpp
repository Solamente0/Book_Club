#include "BookHandler.h"
#include "../ClientHandler.h"
#include "../../managers/BookManager.h"
#include "../../managers/PurchaseManager.h"
#include "../../managers/FileManager.h"
#include "../../repositories/BookRepository.h"


QJsonObject BookHandler::handleGetAllBooks()
{
    QVector<Book> books = BookRepository::instance().findAllActive();
    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetBooksByGenre(const QJsonObject &data)
{
    genre g = stringToGenre(data["genre"].toString());
    QVector<Book> books = BookRepository::instance().findByGenre(g);

    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetBooksByPublisher(const QJsonObject &data, ClientHandler *client)
{
    if (!isLoggedIn(client))
        return unauthorized();

    QVector<Book> books = BookRepository::instance().findByPublisher(client->currentUser()->getId());

    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleSearchBooks(const QJsonObject &data)
{
    QString keyword = data["keyword"].toString();
    QVector<Book> books = BookRepository::instance().search(keyword);

    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetBookDetails(const QJsonObject &data)
{
    int bookId = data["book_id"].toInt();
    Book book = BookRepository::instance().findById(bookId);

    if (book.getId() == 0)
        return notFound("book not founded");

    return success(bookToJson(book));
}

QJsonObject BookHandler::handleAddBook(const QJsonObject &data, ClientHandler *client)
{
    if (!isPublisher(client))
        return unauthorized();

    Book book;
    book.setTitle(data["title"].toString());
    book.setAuthor(data["author"].toString());
    book.setGenre(stringToGenre(data["genre"].toString()));
    book.setDescription(data["description"].toString());
    book.setPrice(data["price"].toDouble());
    book.setDiscount(data["discount"].toDouble());
    

    if (!BookManager::instance().addBook(client->currentUser()->getId(), client->currentUser()->getUsername(),book))
        return failure("Error adding book");

    return success(bookToJson(book));
}

QJsonObject BookHandler::handleEditBook(const QJsonObject &data, ClientHandler *client)
{
    if (!isPublisher(client))
        return unauthorized();

    Book book = BookRepository::instance().findById(data["id"].toInt());

    if (book.getId() == 0)
        return notFound("book not founed");

    book.setTitle(data["title"].toString());
    book.setAuthor(data["author"].toString());
    book.setGenre(stringToGenre(data["genre"].toString()));
    book.setDescription(data["description"].toString());
    book.setPrice(data["price"].toDouble());
    book.setDiscount(data["discount"].toDouble());

    if (!BookRepository::instance().update(book))
        return failure("Error in book editing");

    return success();
}

QJsonObject BookHandler::handleInActiveBook(const QJsonObject &data, ClientHandler *client) 
{
    if (!isPublisher(client))
        return unauthorized();

    if (!BookManager::instance().inactiveBook(data["book_id"].toInt()))
        return failure("Error inActive book");

    return success();
}

QJsonObject BookHandler::handleRestoreBook(const QJsonObject &data, ClientHandler *client)
{
    if (!isPublisher(client))
        return unauthorized();

    if (!BookManager::instance().activeBook(data["book_id"].toInt()))
        return failure("Error returning book");

    return success();
}

QJsonObject BookHandler::handleApplyDiscount(const QJsonObject &data, ClientHandler *client)
{
    if (!isPublisher(client))
        return unauthorized();

    if (!BookManager::instance().applyDiscount(data["book_id"].toInt(), data["discount"].toDouble()))
        return failure("Error in applying discount");

    return success();
}

QJsonObject BookHandler::handleAddReview(const QJsonObject &data, ClientHandler *client)
{
    if (!isLoggedIn(client))
        return unauthorized();

    int bookId = data["book_id"].toInt();

    if (!PurchaseRepository::instance().hasPurchased(client->currentUser()->getId(), bookId))
        return failure("You must purchase the book first.");

    Review review(
        client->currentUser()->getId(),
        data["stars"].toInt(),
        data["comment"].toString()
    );

    if (!BookManager::instance().addReview(bookId, review))
        return failure("Error in review registration");

    return success();
}

QJsonObject BookHandler::handleEditReview(const QJsonObject &data, ClientHandler *client)
{
    if (!isLoggedIn(client))
        return unauthorized();

    int bookId = data["book_id"].toInt();
    Review review(
        client->currentUser()->getId(),
        data["stars"].toInt(),
        data["comment"].toString()
    );
    review.Edit(data["stars"].toInt(), data["comment"].toString());

    if (!BookRepository::instance().updateReview(bookId, review))
        return failure("Error editing review");

    return success();
}

QJsonObject BookHandler::handleDeleteReview(const QJsonObject &data, ClientHandler *client)
{
    if (!isLoggedIn(client) && client->currentUser()->role() != "User")
        return unauthorized();

    if (!BookRepository::instance().removeReview(
            data["book_id"].toInt(),
            client->currentUser()->getId()))
        return failure("Error deleting review");

    return success();
}

QJsonObject BookHandler::handleGetReviews(const QJsonObject &data)
{
    int bookId = data["book_id"].toInt();
    QVector<Review> reviews = BookRepository::instance().findReviews(bookId);

    QJsonArray arr;
    for (const Review &r : reviews)
        arr.append(reviewToJson(r));

    QJsonObject result;
    result["reviews"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetTopSellingBooks()
{
    QVector<Book> books = BookManager::instance().getTopSellingBooks();
    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetLeastSellingBooks()
{
    QVector<Book> books = BookManager::instance().getLeastSellingBooks();
    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetNewestBooks()
{
    QVector<Book> books = BookManager::instance().getNewestBooks();
    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetMostRatedBooks()
{
    QVector<Book> books = BookManager::instance().getMostRatedBooks();
    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetFreeBooks()
{
    QVector<Book> books = BookManager::instance().getFreeBooks();
    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handleGetRecommendedBooks(ClientHandler *client)
{
    if (!isLoggedIn(client))
        return unauthorized();

    User *user = dynamic_cast<User*>(client->currentUser().get());
    if (!user)
        return failure("Only users can receive recommended books.");

    QVector<Book> books = BookManager::instance().getRecommendedBooks(user->getfavoriteGenres());
    QJsonArray arr;
    for (const Book &b : books)
        arr.append(bookToJson(b));

    QJsonObject result;
    result["books"] = arr;
    return success(result);
}

QJsonObject BookHandler::handle(RequestType type, const QJsonObject &data, ClientHandler *client)
{
    switch (type) {
    case RequestType::GetAllBooks:
        return handleGetAllBooks();
    case RequestType::GetBooksByGenre:
        return handleGetBooksByGenre(data);
    case RequestType::GetBooksByPublisher:
        return handleGetBooksByPublisher(data, client);
    case RequestType::SearchBooks:
        return handleSearchBooks(data);
    case RequestType::GetBookDetails:
        return handleGetBookDetails(data);
    case RequestType::AddBook:
        return handleAddBook(data, client);
    case RequestType::EditBook:
        return handleEditBook(data, client);
    case RequestType::InActiveBook:
        return handleInActiveBook(data, client);
    case RequestType::RestoreBook:
        return handleRestoreBook(data, client);
    case RequestType::ApplyDiscount:
        return handleApplyDiscount(data, client);
    case RequestType::AddReview:
        return handleAddReview(data, client);
    case RequestType::EditReview:
        return handleEditReview(data, client);
    case RequestType::DeleteReview:
        return handleDeleteReview(data, client);
    case RequestType::GetReviews:
        return handleGetReviews(data);
    case RequestType::GetTopSellingBooks:
        return handleGetTopSellingBooks();
    case RequestType::GetLeastSellingBooks:
        return handleGetLeastSellingBooks();
    case RequestType::GetNewestBooks:
        return handleGetNewestBooks();
    case RequestType::GetMostRatedBooks:
        return handleGetMostRatedBooks();
    case RequestType::GetFreeBooks:
        return handleGetFreeBooks();
    case RequestType::GetRecommendedBooks:
        return handleGetRecommendedBooks(client);
    default:
        return failure("Unknown book request");
    }
}