#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    NoteImageFormat(MusicNote::getTrebleClefNoteImageDataFormat().toLocal8Bit().data())
{
    ui->setupUi(this);

    NoteSoundPlayer.setVolume(100);
    NoteSoundPlayer.setMedia(NULL,&currentNoteSound);
    QObject::connect(&NoteSoundPlayer, &QMediaPlayer::stateChanged, this, [&](QMediaPlayer::State state){
        if (state == QMediaPlayer::StoppedState)
        {
            playSoundAtPendingGuitarPositionsAndContinue();
        }
    });

    timer.setParent(this);
    timer.setInterval(2700);
    timer.setSingleShot(true);
    QObject::connect(&timer, &QTimer::timeout, this, [&](){
        currentNote = MusicNote::getRandomNote();
        currentNoteImage.loadFromData(*MusicNote::getImageDataOfTrebleClefNote(currentNote),NoteImageFormat);
        currentGuitarPositions = MusicNote::getGuitarPositionsOfNote(currentNote);
        std::reverse(currentGuitarPositions.begin(), currentGuitarPositions.end());
        ui->labelMusicNote->setPixmap(currentNoteImage);
        ui->labelMusicNote->update();
        ui->labelScientificName->setText(currentNote);
        ui->labelScientificName->update();
        ui->labelGuitarPosition->setText(currentGuitarPositions.join('\n'));
        ui->labelGuitarPosition->update();
        playSoundAtPendingGuitarPositionsAndContinue();
    });

    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete NoteImageFormat;
}

void MainWindow::playSoundAtPendingGuitarPositionsAndContinue()
{
    if (currentGuitarPositions.size())
    {
        currentNoteSound.close();
        currentNoteSound.setBuffer(MusicNote::getSoundDataAtGuitarPosition(currentGuitarPositions.takeFirst()));
        currentNoteSound.open(QIODevice::ReadOnly);
        NoteSoundPlayer.play();
    }
    else
    {
        timer.start();
    }
}
