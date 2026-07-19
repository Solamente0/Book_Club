#include "mainwindow.h"
#include "login.h"
#include "home.h"
#include "register.h"
#include "Cart.h"
#include "cartwidget.h"
#include <QVBoxLayout>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include "bookdetailwindow.h"
#include "Book.h"
#include "User.h"
#include "genreselectionwidget.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    resize(700,700);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    move(
        screenGeometry.center().x() - width() / 2,
        screenGeometry.center().y() - height() / 2
        );

    userManager = new UserManager();

    stack = new QStackedWidget(this);
    mainCart = &currentUser.getCart();

    LoginPage = new login(userManager, this);
    HomePage = new home(this);
    RegisterPage = new Register(userManager, this);
    CartPage = new CartWidget(mainCart, this);
    GenreSelectionPage = new GenreSelectionWidget(this);

    stack->addWidget(LoginPage);
    stack->addWidget(HomePage);
    stack->addWidget(RegisterPage);
    stack->addWidget(CartPage);
    stack->addWidget(GenreSelectionPage);

    connect(LoginPage, &login::SignInSuccess, this, [this](User user) {
        currentUser = user;

        if (currentUser.isFirstLogin()) {
            stack->setCurrentWidget(GenreSelectionPage);
            return;
        }

        QVector<Book> allBooks;
        allBooks.append(Book("Fantasy Best", "Author A", genre::Fiction, 15.0));
        allBooks.append(Book("Mystery Case", "Author B", genre::Mystery, 12.0));
        allBooks.append(Book("World History", "Author C", genre::History, 20.0));
        allBooks.append(Book("Love Story", "Author D", genre::Romance, 10.0));

        QVector<Book> recommended;
        for (const Book &book : allBooks) {
            if (currentUser.getfavoriteGenres().contains(book.getGenre())) {
                recommended.append(book);
            }
        }

        HomePage->loadRecommendedBooks(recommended);
        HomePage->loadGenreBooks(allBooks);
        HomePage->loadFeaturedBooks(allBooks);
        HomePage->loadNewReleases(allBooks);
        HomePage->loadBestSellers(allBooks);
        HomePage->loadFreeBooks(allBooks);

        stack->setCurrentWidget(HomePage);
    });

    connect(LoginPage, &login::GoToSignUp, this, [this]() {
        stack->setCurrentWidget(RegisterPage);
    });

    connect(RegisterPage, &Register::goToLogin, this, [this]() {
        stack->setCurrentWidget(LoginPage);
    });

    connect(RegisterPage, &Register::SignUpSuccess, this, [this]() {
        stack->setCurrentWidget(LoginPage);
    });


    connect(GenreSelectionPage, &GenreSelectionWidget::genresSelected, this, [this](QVector<genre> genres) {
        currentUser.setFavoriteGenres(genres);
        currentUser.setFirstLogin(false);

        QVector<Book> allBooks;
        allBooks.append(Book("Fantasy Best", "Author A", genre::Fiction, 15.0));
        allBooks.append(Book("Mystery Case", "Author B", genre::Mystery, 12.0));
        allBooks.append(Book("World History", "Author C", genre::History, 20.0));
        allBooks.append(Book("Love Story", "Author D", genre::Romance, 10.0));

        QVector<Book> recommended;
        for (const Book &book : allBooks) {
            if (currentUser.getfavoriteGenres().contains(book.getGenre())) {
                recommended.append(book);
            }
        }

        HomePage->loadRecommendedBooks(recommended);
        HomePage->loadGenreBooks(allBooks);
        HomePage->loadFeaturedBooks(allBooks);
        HomePage->loadNewReleases(allBooks);
        HomePage->loadBestSellers(allBooks);
        HomePage->loadFreeBooks(allBooks);

        stack->setCurrentWidget(HomePage);
    });

    connect(HomePage, &home::cartRequested, this, [this]() {
        CartPage->updateUI();
        stack->setCurrentWidget(CartPage);
    });

    connect(CartPage, &CartWidget::backToHomeRequested, this, [this]() {
        stack->setCurrentWidget(HomePage);
    });

    connect(CartPage, &CartWidget::checkoutSuccessful, this, [this]() {
        QMessageBox::information(this, "Success", "Thank you for your purchase! Books added to your library.");
        stack->setCurrentWidget(HomePage);
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stack);

    BookDetailPage = new BookDetailWidget(mainCart, this);
    stack->addWidget(BookDetailPage);

    connect(HomePage, &home::bookClicked, this, [this](const Book &book) {
        BookDetailPage->loadBook(book);
        stack->setCurrentWidget(BookDetailPage);
    });

    connect(BookDetailPage, &BookDetailWidget::backToHomeRequested, this, [this]() {
        stack->setCurrentWidget(HomePage);
    });

    stack->setCurrentWidget(LoginPage);
    ForgotPasswordPage = new ForgotPasswordWidget(userManager, this);
    stack->addWidget(ForgotPasswordPage);

    connect(LoginPage, &login::ForgotPasswordRequested, this, [this]() {
        stack->setCurrentWidget(ForgotPasswordPage);
    });
    connect(ForgotPasswordPage, &ForgotPasswordWidget::backToLoginRequested, this, [this]() {
        stack->setCurrentWidget(LoginPage);
    });
}