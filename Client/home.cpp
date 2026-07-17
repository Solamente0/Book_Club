#include "home.h"
#include <QStyleOption>
#include <QPainter>
#include <QPixmap>

home::home(QWidget *parent) : QWidget(parent) {
    // ۱. اعمال گرادینت مورب و ملایم صفحه رجیستر روی هوم‌پیج
    this->setObjectName("homePage");
    this->setStyleSheet(
        "QWidget#homePage {"
        "   background-color: #FCFCFC;"
        "}"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ==========================================
    // ۲. نوار هدر بالا (شفاف روی گرادینت)
    // ==========================================
    headerWidget = new QWidget(this);
    headerWidget->setMinimumHeight(75);
    headerWidget->setMaximumHeight(75);
    headerWidget->setStyleSheet("background-color: rgba(210, 235, 255, 170);  border-bottom: 1px solid rgba(0,0,0,15);");

    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(25, 0, 25, 0);
    headerLayout->setSpacing(15);

    // لوگو با رنگ صورتی ملایم جدید شما
    lblLogo = new QLabel(headerWidget);
    lblLogo->setText("<span style='color:#f68787;'>B👓k Club</span>");
    lblLogo->setFont(QFont("Segoe UI", 22, QFont::Bold));
    headerLayout->addWidget(lblLogo);

    headerLayout->addStretch(1);

    // باکس جستجو با فریم مشکی ظریف و متن صورتی ملایم جدید شما
    leSearch = new QLineEdit(headerWidget);
    leSearch->setPlaceholderText("search...");
    leSearch->setFixedWidth(240);
    leSearch->setMinimumHeight(36);
    leSearch->setStyleSheet(
        "QLineEdit {"
        "   border: 1px solid #000000;"
        "   border-radius: 18px;"
        "   padding-left: 15px;"
        "   padding-right: 15px;"
        "   color: #f68787;"
        "   background-color: rgba(255, 255, 255, 180);"
        "}"
        );
    headerLayout->addWidget(leSearch);

    headerLayout->addStretch(1);

    // آیکون‌های هدر
    btnNotification = new QPushButton("🔔", headerWidget);
    btnNotification->setCursor(Qt::PointingHandCursor);
    btnNotification->setStyleSheet("background: transparent; border: none; font-size: 19px; color: #000000;");
    headerLayout->addWidget(btnNotification);

    btnCart = new QPushButton("🛒", headerWidget);
    btnCart->setCursor(Qt::PointingHandCursor);
    btnCart->setStyleSheet("background: transparent; border: none; font-size: 19px; color: #000000;");
    headerLayout->addWidget(btnCart);

    btnProfile = new QPushButton("👤", headerWidget);
    btnProfile->setCursor(Qt::PointingHandCursor);
    btnProfile->setStyleSheet("background: transparent; border: none; font-size: 21px; color: #FF69B4;");
    headerLayout->addWidget(btnProfile);

    mainLayout->addWidget(headerWidget);

    // ==========================================
    // ۳. منطقه اسکرول‌شونده برای بخش‌های اصلی
    // ==========================================
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; }"
        "QScrollArea > QWidget > QWidget { background: transparent; }"
        );

    scrollWidget = new QWidget(scrollArea);
    scrollWidget->setStyleSheet("background-color: transparent;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(20, 20, 20, 20);
    scrollLayout->setSpacing(25);

    // ------------------------------------------
    // الف) بخش ژانرها (Genres)
    // ------------------------------------------
    genresFrame = new QFrame(scrollWidget);
    genresFrame->setStyleSheet("background-color: rgba(253, 246, 238, 180); border-radius: 20px;");
    QVBoxLayout *genresLayout = new QVBoxLayout(genresFrame);
    genresLayout->setContentsMargins(20, 18, 20, 18);

    QHBoxLayout *genresHeader = new QHBoxLayout();
    QLabel *lblGenresTitle = new QLabel("Genres", genresFrame);
    lblGenresTitle->setFont(QFont("Segoe UI", 14, QFont::Bold));
    lblGenresTitle->setStyleSheet("color: #706357; background: transparent;");
    QPushButton *btnGenresSeeAll = new QPushButton("See all", genresFrame);
    btnGenresSeeAll->setStyleSheet("color: #000000; background: transparent; border: none; font-weight: bold; font-size: 12px;");
    btnGenresSeeAll->setCursor(Qt::PointingHandCursor);
    genresHeader->addWidget(lblGenresTitle);
    genresHeader->addStretch();
    genresHeader->addWidget(btnGenresSeeAll);
    genresLayout->addLayout(genresHeader);

    QHBoxLayout *genresItemsLayout = new QHBoxLayout();
    genresItemsLayout->setSpacing(15);
    genresItemsLayout->addWidget(createBookWidget(":/images/fantasy.jpg", "Fantasy Best", genresFrame));
    genresItemsLayout->addWidget(createBookWidget(":/images/novel.jpg", "The Novel", genresFrame));
    genresItemsLayout->addWidget(createBookWidget(":/images/romance.jpg", "Love Story", genresFrame));
    genresItemsLayout->addWidget(createBookWidget(":/images/history.jpg", "World History", genresFrame));
    genresItemsLayout->addWidget(createBookWidget(":/images/mystery.jpg", "Mystery Case", genresFrame));
    genresLayout->addLayout(genresItemsLayout);

    scrollLayout->addWidget(genresFrame);

    // ------------------------------------------
    // ب) بخش ویژه (Featured Books)
    // ------------------------------------------
    featuredFrame = new QFrame(scrollWidget);
    featuredFrame->setStyleSheet("background-color: rgba(210, 235, 255, 170); border-radius: 20px;");
    QVBoxLayout *featuredLayout = new QVBoxLayout(featuredFrame);
    featuredLayout->setContentsMargins(20, 18, 20, 18);

    QHBoxLayout *featuredHeader = new QHBoxLayout();
    QLabel *lblFeaturedTitle = new QLabel("Featured Books", featuredFrame);
    lblFeaturedTitle->setFont(QFont("Segoe UI", 14, QFont::Bold));
    lblFeaturedTitle->setStyleSheet("color: #2E4D63; background: transparent;");
    QPushButton *btnFeaturedSeeAll = new QPushButton("See all", featuredFrame);
    btnFeaturedSeeAll->setStyleSheet("color: #000000; background: transparent; border: none; font-weight: bold; font-size: 12px;");
    btnFeaturedSeeAll->setCursor(Qt::PointingHandCursor);
    featuredHeader->addWidget(lblFeaturedTitle);
    featuredHeader->addStretch();
    featuredHeader->addWidget(btnFeaturedSeeAll);
    featuredLayout->addLayout(featuredHeader);

    QHBoxLayout *featuredItemsLayout = new QHBoxLayout();
    featuredItemsLayout->setSpacing(15);
    featuredItemsLayout->addWidget(createBookWidget(":/images/feat1.jpg", "Book Title 1", featuredFrame));
    featuredItemsLayout->addWidget(createBookWidget(":/images/feat2.jpg", "Book Title 2", featuredFrame));
    featuredItemsLayout->addWidget(createBookWidget(":/images/feat3.jpg", "Book Title 3", featuredFrame));
    featuredItemsLayout->addWidget(createBookWidget(":/images/feat4.jpg", "Book Title 4", featuredFrame));
    featuredItemsLayout->addWidget(createBookWidget(":/images/feat5.jpg", "Book Title 5", featuredFrame));
    featuredLayout->addLayout(featuredItemsLayout);

    scrollLayout->addWidget(featuredFrame);

    // ------------------------------------------
    // ج) بخش پیشنهادی (Recommended for u)
    // ------------------------------------------
    recommendedFrame = new QFrame(scrollWidget);
    recommendedFrame->setStyleSheet("background-color: #f4dbde; border-radius: 20px;");
    QVBoxLayout *recommendedLayout = new QVBoxLayout(recommendedFrame);
    recommendedLayout->setContentsMargins(20, 18, 20, 18);

    QHBoxLayout *recommendedHeader = new QHBoxLayout();
    QLabel *lblRecommendedTitle = new QLabel("Recommended for u", recommendedFrame);
    lblRecommendedTitle->setFont(QFont("Segoe UI", 14, QFont::Bold));
    lblRecommendedTitle->setStyleSheet("color: #803040; background: transparent;");
    QPushButton *btnRecommendedSeeAll = new QPushButton("See all", recommendedFrame);
    btnRecommendedSeeAll->setStyleSheet("color: #000000; background: transparent; border: none; font-weight: bold; font-size: 12px;");
    btnRecommendedSeeAll->setCursor(Qt::PointingHandCursor);
    recommendedHeader->addWidget(lblRecommendedTitle);
    recommendedHeader->addStretch();
    recommendedHeader->addWidget(btnRecommendedSeeAll);
    recommendedLayout->addLayout(recommendedHeader);

    QHBoxLayout *recommendedItemsLayout = new QHBoxLayout();
    recommendedItemsLayout->setSpacing(15);
    recommendedItemsLayout->addWidget(createBookWidget(":/images/rec1.jpg", "Recommended 1", recommendedFrame));
    recommendedItemsLayout->addWidget(createBookWidget(":/images/rec2.jpg", "Recommended 2", recommendedFrame));
    recommendedItemsLayout->addWidget(createBookWidget(":/images/rec3.jpg", "Recommended 3", recommendedFrame));
    recommendedItemsLayout->addWidget(createBookWidget(":/images/rec4.jpg", "Recommended 4", recommendedFrame));
    recommendedItemsLayout->addWidget(createBookWidget(":/images/rec5.jpg", "Recommended 5", recommendedFrame));
    recommendedLayout->addLayout(recommendedItemsLayout);

    scrollLayout->addWidget(recommendedFrame);

    // ------------------------------------------
    // د) بخش جدیدترین‌ها (New Releases)
    // ------------------------------------------
    newReleasesFrame = new QFrame(scrollWidget);
    newReleasesFrame->setStyleSheet("background-color: rgba(255, 192, 159, 195); border-radius: 20px;");
    QVBoxLayout *newReleasesLayout = new QVBoxLayout(newReleasesFrame);
    newReleasesLayout->setContentsMargins(20, 18, 20, 18);

    QHBoxLayout *newReleasesHeader = new QHBoxLayout();
    QLabel *lblNewReleasesTitle = new QLabel("New Releases", newReleasesFrame);
    lblNewReleasesTitle->setFont(QFont("Segoe UI", 14, QFont::Bold));
    lblNewReleasesTitle->setStyleSheet("color: #A04E20; background: transparent;");
    QPushButton *btnNewReleasesSeeAll = new QPushButton("See all", newReleasesFrame);
    btnNewReleasesSeeAll->setStyleSheet("color: #000000; background: transparent; border: none; font-weight: bold; font-size: 12px;");
    btnNewReleasesSeeAll->setCursor(Qt::PointingHandCursor);
    newReleasesHeader->addWidget(lblNewReleasesTitle);
    newReleasesHeader->addStretch();
    newReleasesHeader->addWidget(btnNewReleasesSeeAll);
    newReleasesLayout->addLayout(newReleasesHeader);

    QHBoxLayout *newReleasesItemsLayout = new QHBoxLayout();
    newReleasesItemsLayout->setSpacing(15);
    newReleasesItemsLayout->addWidget(createBookWidget(":/images/new1.jpg", "New Release 1", newReleasesFrame));
    newReleasesItemsLayout->addWidget(createBookWidget(":/images/new2.jpg", "New Release 2", newReleasesFrame));
    newReleasesItemsLayout->addWidget(createBookWidget(":/images/new3.jpg", "New Release 3", newReleasesFrame));
    newReleasesItemsLayout->addWidget(createBookWidget(":/images/new4.jpg", "New Release 4", newReleasesFrame));
    newReleasesItemsLayout->addWidget(createBookWidget(":/images/new5.jpg", "New Release 5", newReleasesFrame));
    newReleasesLayout->addLayout(newReleasesItemsLayout);

    scrollLayout->addWidget(newReleasesFrame);

    // ------------------------------------------
    // هـ) بخش پرفروش‌ها (Best Sellers) - [تکرار استایل و رنگ آبی ملایم شما]
    // ------------------------------------------
    bestSellersFrame = new QFrame(scrollWidget);
    bestSellersFrame->setStyleSheet("background-color: rgba(210, 235, 255, 170); border-radius: 20px;");
    QVBoxLayout *bestSellersLayout = new QVBoxLayout(bestSellersFrame);
    bestSellersLayout->setContentsMargins(20, 18, 20, 18);

    QHBoxLayout *bestSellersHeader = new QHBoxLayout();
    QLabel *lblBestSellersTitle = new QLabel("Best Sellers", bestSellersFrame);
    lblBestSellersTitle->setFont(QFont("Segoe UI", 14, QFont::Bold));
    lblBestSellersTitle->setStyleSheet("color: #2E4D63; background: transparent;");
    QPushButton *btnBestSellersSeeAll = new QPushButton("See all", bestSellersFrame);
    btnBestSellersSeeAll->setStyleSheet("color: #000000; background: transparent; border: none; font-weight: bold; font-size: 12px;");
    btnBestSellersSeeAll->setCursor(Qt::PointingHandCursor);
    bestSellersHeader->addWidget(lblBestSellersTitle);
    bestSellersHeader->addStretch();
    bestSellersHeader->addWidget(btnBestSellersSeeAll);
    bestSellersLayout->addLayout(bestSellersHeader);

    QHBoxLayout *bestSellersItemsLayout = new QHBoxLayout();
    bestSellersItemsLayout->setSpacing(15);
    bestSellersItemsLayout->addWidget(createBookWidget(":/images/best1.jpg", "Best Seller 1", bestSellersFrame));
    bestSellersItemsLayout->addWidget(createBookWidget(":/images/best2.jpg", "Best Seller 2", bestSellersFrame));
    bestSellersItemsLayout->addWidget(createBookWidget(":/images/best3.jpg", "Best Seller 3", bestSellersFrame));
    bestSellersItemsLayout->addWidget(createBookWidget(":/images/best4.jpg", "Best Seller 4", bestSellersFrame));
    bestSellersItemsLayout->addWidget(createBookWidget(":/images/best5.jpg", "Best Seller 5", bestSellersFrame));
    bestSellersLayout->addLayout(bestSellersItemsLayout);

    scrollLayout->addWidget(bestSellersFrame);

    // ------------------------------------------
    // و) بخش کتاب‌های رایگان (Free Books) - [تکرار استایل و رنگ صورتی چرک شما]
    // ------------------------------------------
    freeBooksFrame = new QFrame(scrollWidget);
    freeBooksFrame->setStyleSheet("background-color: #f4dbde; border-radius: 20px;");
    QVBoxLayout *freeBooksLayout = new QVBoxLayout(freeBooksFrame);
    freeBooksLayout->setContentsMargins(20, 18, 20, 18);

    QHBoxLayout *freeBooksHeader = new QHBoxLayout();
    QLabel *lblFreeBooksTitle = new QLabel("Free Books", freeBooksFrame);
    lblFreeBooksTitle->setFont(QFont("Segoe UI", 14, QFont::Bold));
    lblFreeBooksTitle->setStyleSheet("color: #803040; background: transparent;");
    QPushButton *btnFreeBooksSeeAll = new QPushButton("See all", freeBooksFrame);
    btnFreeBooksSeeAll->setStyleSheet("color: #000000; background: transparent; border: none; font-weight: bold; font-size: 12px;");
    btnFreeBooksSeeAll->setCursor(Qt::PointingHandCursor);
    freeBooksHeader->addWidget(lblFreeBooksTitle);
    freeBooksHeader->addStretch();
    freeBooksHeader->addWidget(btnFreeBooksSeeAll);
    freeBooksLayout->addLayout(freeBooksHeader);

    QHBoxLayout *freeBooksItemsLayout = new QHBoxLayout();
    freeBooksItemsLayout->setSpacing(15);
    freeBooksItemsLayout->addWidget(createBookWidget(":/images/free1.jpg", "Free Book 1", freeBooksFrame));
    freeBooksItemsLayout->addWidget(createBookWidget(":/images/free2.jpg", "Free Book 2", freeBooksFrame));
    freeBooksItemsLayout->addWidget(createBookWidget(":/images/free3.jpg", "Free Book 3", freeBooksFrame));
    freeBooksItemsLayout->addWidget(createBookWidget(":/images/free4.jpg", "Free Book 4", freeBooksFrame));
    freeBooksItemsLayout->addWidget(createBookWidget(":/images/free5.jpg", "Free Book 5", freeBooksFrame));
    freeBooksLayout->addLayout(freeBooksItemsLayout);

    scrollLayout->addWidget(freeBooksFrame);

    // نهایی‌سازی اسکرول
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    // inside home.cpp (در انتهای سازنده کلاس هوم)
    connect(btnCart, &QPushButton::clicked, this, &home::cartRequested);
}

// متد ساخت فریم کتاب با قابلیت تغییر ابعاد هوشمند و واکنش‌گرا (همان سایز و استایل شما)
QWidget *home::createBookWidget(const QString &imagePath,
                                const QString &title,
                                QWidget *parent)
{
    QFrame *card = new QFrame(parent);

    // همان ابعاد پویای تعریف شده توسط خودت (بین ۱۱۰ تا ۱۴۰)
    card->setMinimumSize(110, 155);
    card->setMaximumSize(140, 180);

    // فعال کردن سیاست تغییر سایز افقی پویا
    card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // استایل شیشه‌ای ملایم فریم‌های خالی کاملاً مطابق با سلیقه شما
    card->setStyleSheet(
        "background-color: rgba(255, 255, 255, 110);"
        "border-radius: 12px;"
        "border: 1px solid rgba(0, 0, 0, 20);"
        );

    return card;
}

void home::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

home::~home() = default;