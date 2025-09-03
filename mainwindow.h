#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setMouseTracking(true);
        if (centralWidget()) {
            centralWidget()->setMouseTracking(true);
        }

        mainWidget = new QWidget(this);
        mainWidget->setMouseTracking(true);
        this->setCentralWidget(mainWidget);

        QVBoxLayout* leftLayout = new QVBoxLayout;

        lab1 = new QPushButton("launch lab1");
        lab2 = new QPushButton("launch lab2");
        lab3 = new QPushButton("launch lab3");

        changeButtonStyle(lab1);
        changeButtonStyle(lab2);
        changeButtonStyle(lab3);

        lab1->setMouseTracking(true);
        lab2->setMouseTracking(true);
        lab3->setMouseTracking(true);

        leftLayout->addStretch();
        leftLayout->addWidget(lab1);
        leftLayout->addWidget(lab2);
        leftLayout->addWidget(lab3);
        leftLayout->setSpacing(30);
        leftLayout->addStretch();

        QVBoxLayout* rightLayout = new QVBoxLayout;

        lab4 = new QPushButton("launch lab4");
        lab5 = new QPushButton("launch lab5");
        lab6 = new QPushButton("launch lab6");

        changeButtonStyle(lab4);
        changeButtonStyle(lab5);
        changeButtonStyle(lab6);

        lab4->setMouseTracking(true);
        lab5->setMouseTracking(true);
        lab6->setMouseTracking(true);

        rightLayout->addStretch();
        rightLayout->addWidget(lab4);
        rightLayout->addWidget(lab5);
        rightLayout->addWidget(lab6);
        rightLayout->setSpacing(30);
        rightLayout->addStretch();

        QHBoxLayout* mainLayout = new QHBoxLayout(mainWidget);

        mainLayout->addStretch();
        mainLayout->addLayout(leftLayout);
        mainLayout->addStretch();
        mainLayout->addLayout(rightLayout);
        mainLayout->addStretch();

        this->setupTimer();

        this->connectButtons();

        cursorPos = QPoint(width() / 2, height() / 2);
    }

    ~MainWindow();

private:
    void resizeEvent(QResizeEvent* event) override {
        scaledBg = bg.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        QMainWindow::resizeEvent(event);
    }

    void paintEvent(QPaintEvent* event) override{
        QPainter painter(this);

        if (!bg.isNull()) {
            painter.drawPixmap(0, 0, scaledBg);
        }

        if (!animatedGhost.isNull()) {
            painter.drawPixmap(ghostX, ghostY, animatedGhost);
        }

        if (!pointerFollowerImg.isNull()) {
            int x = cursorPos.x() - pointerFollowerImg.width();
            int y = cursorPos.y() - pointerFollowerImg.height();
            painter.drawPixmap(x, y, pointerFollowerImg);
        }

        QMainWindow::paintEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        cursorPos = event->pos();

        update();
    }

    void changeButtonStyle(QPushButton* button) {
        button->setStyleSheet(
            "QPushButton {"
            "   background-color: transparent;"
            "   color: rgba(255, 255, 255, 180);"
            "   border: 2px solid transparent;"
            "   border-radius: 12px;"
            "   padding: 8px 16px;"
            "   font-size: 18px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgba(255, 255, 255, 40);"
            "   border: 2px solid #9370DB;"
            "   color: #FFD700;"
            "}"
            "QPushButton:pressed {"
            "   background-color: rgba(255, 255, 255, 70);"
            "   border: 2px solid #DA70D6;"
            "   color: white;"
            "}"
            );

        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
        effect->setBlurRadius(8);
        effect->setOffset(2, 2);
        effect->setColor(Qt::black);

        button->setGraphicsEffect(effect);
    }

    void setupTimer() {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::setupAnimatedGhost);
        timer->start(16);
    }

    void connectButtons() {
        connect(lab1, &QPushButton::clicked, this, []() {
            QProcess::startDetached("pathToLab1.exe");
        });

        connect(lab2, &QPushButton::clicked, this, []() {
            QProcess::startDetached("pathToLab1.exe");
        });

        connect(lab3, &QPushButton::clicked, this, []() {
            QProcess::startDetached("pathToLab1.exe");
        });

        connect(lab4, &QPushButton::clicked, this, []() {
            QProcess::startDetached("pathToLab1.exe");
        });

        connect(lab5, &QPushButton::clicked, this, []() {
            QProcess::startDetached("pathToLab1.exe");
        });

        connect(lab6, &QPushButton::clicked, this, []() {
            QProcess::startDetached("pathToLab1.exe");
        });
    }

private slots:
    void setupAnimatedGhost() {
        ghostX += dx;
        ghostY += dy;

        if (ghostX < 0) {
            ghostX = 0;
            dx = -dx;
        }
        else if (ghostX + animatedGhost.width() > width()) {
            ghostX = width() - animatedGhost.width();
            dx = -dx;
        }

        if (ghostY < 0) {
            ghostY = 0;
            dy = -dy;
        }
        else if (ghostY + animatedGhost.height() > height()) {
            ghostY = height() - animatedGhost.height();
            dy = -dy;
        }

        update();
    }

private:
    int ghostX = 0;
    int ghostY = 100;
    int dx = 2;
    int dy = 1;

    QPushButton* lab1;
    QPushButton* lab2;
    QPushButton* lab3;
    QPushButton* lab4;
    QPushButton* lab5;
    QPushButton* lab6;

    QWidget* mainWidget;
    QPixmap bg = QPixmap(":/picturePrefix/picturesFold/castleP.png");
    QPixmap scaledBg;
    QPixmap pointerFollowerImg = QPixmap(":/picturePrefix/picturesFold/ghostNew.png");
    QPoint cursorPos;
    QPixmap animatedGhost = QPixmap(":/picturePrefix/picturesFold/ghostNew.png");
    QTimer* timer;
};
#endif // MAINWINDOW_H
