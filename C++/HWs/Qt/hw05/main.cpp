#include <QApplication>
#include <QLabel>
#include <QDir>
#include <QFileInfoList>
#include <QPixmap>
#include <QTimer>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QStyle>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * folder with frames is expected on <working_directory>/frames
 * When run from Qt Creator IDE <working_directory> is
 * value of key="RunConfiguration.WorkingDirectory.default in hw05.pro.user
 * When run from binary file (hw05)
 * drwxrwxr-x frames
 * -rwxrwxr-x hw05
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // directory of frames
    const fs::path framesPath = fs::current_path() /= "frames";
    std::cout << "Frames path is " << framesPath << '\n';
    QDir imageDir(framesPath);

    //filter
    QStringList filters = {"*.jpg", "*.jpeg", "*.png"};
    QFileInfoList database = imageDir.entryInfoList(filters);

    QLabel label;
    label.setWindowFlags(Qt::FramelessWindowHint);
    label.setScaledContents(true);

    QTimer timer;
    int currentIndex = 0;
    int interval = 1000;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        if (currentIndex >= database.size()) {
            timer.stop();
            return;
        }
        QString framePath = database[currentIndex].absoluteFilePath();
        QPixmap frame(framePath);
        label.setPixmap(frame);
        label.adjustSize();
        currentIndex++;
    });

    // define all buttons + spinBox
    QPushButton *playButton = new QPushButton("Play");
    QPushButton *upButton = new QPushButton("Move Up");
    QPushButton *downButton = new QPushButton("Move Down");
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *removeButton = new QPushButton("Remove");
    QLabel *spinBoxLabel = new QLabel("Set speed:");
    QSpinBox *spinBox = new QSpinBox();

    // parameters
    playButton->setFixedWidth(playButton->fontMetrics().boundingRect(playButton->text()).width() + 10);
    upButton->setFixedWidth(upButton->fontMetrics().boundingRect(upButton->text()).width() + 10);
    downButton->setFixedWidth(downButton->fontMetrics().boundingRect(downButton->text()).width() + 10);
    addButton->setFixedWidth(addButton->fontMetrics().boundingRect(addButton->text()).width() + 10);
    removeButton->setFixedWidth(removeButton->fontMetrics().boundingRect(removeButton->text()).width() + 10);

    // range from 0 to 500 is optional, my opinion ...
    // changing number down you can speed up animation
    spinBox->setRange(0, 500);
    spinBox->setValue(interval);

    // function for playing again
    QObject::connect(playButton, &QPushButton::clicked, [&]() {
        timer.start(interval);
        currentIndex = 0;
    });

    // function for moving actual frame up
    QObject::connect(upButton, &QPushButton::clicked, [&]() {
        if (currentIndex > 0) {
            database.move(currentIndex, currentIndex - 1);
            timer.start(interval);
            currentIndex--;
        }
    });

    // function for moving actual frame down
    QObject::connect(downButton, &QPushButton::clicked, [&]() {
        if (currentIndex < database.size() - 1) {
            database.move(currentIndex, currentIndex + 1);
            timer.start(interval);
            currentIndex++;
        }
    });

    // function for adding more frames
    QObject::connect(addButton, &QPushButton::clicked, [&]() {
        QString imagePath = QFileDialog::getOpenFileName(nullptr, "Select an image to add", QDir::homePath(),
                                                         "Images (*.png *.jpg *.jpeg)");
        if (!imagePath.isEmpty()) {
            QFileInfo newFileInfo(imagePath);
            database.append(newFileInfo);
            timer.start(interval);
            currentIndex = 0;
        }
    });

    // function for removing frames
    QObject::connect(removeButton, &QPushButton::clicked, [&]() {
        if (currentIndex < database.size() - 1) {
            database.removeAt(currentIndex);
            timer.start(interval);
            currentIndex = 0;
        }
    });

    QObject::connect(spinBox, &QSpinBox::valueChanged, [&](int value) {
        interval = value;
        if (timer.isActive()) {
            timer.stop();
            timer.start(interval);
        }
    });

    // set all controls button (+ label for spinBox)
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(playButton);
    controlsLayout->addWidget(upButton);
    controlsLayout->addWidget(downButton);
    controlsLayout->addWidget(addButton);
    controlsLayout->addWidget(removeButton);
    controlsLayout->addWidget(spinBoxLabel);
    controlsLayout->addWidget(spinBox);

    // set layout for controls and labels
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(&label);
    mainLayout->addLayout(controlsLayout);

    // main layout
    QWidget *mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);

    // show main window
    mainWidget->show();

    // start animation
    timer.start(interval);

    return app.exec();
}




