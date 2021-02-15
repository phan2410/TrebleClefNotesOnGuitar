#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QBuffer>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaContent>
#include "musicnote.h"
#include <QTimer>
#include "anlogger.h"
#include "algorithm"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    QString currentNote;
    QPixmap currentNoteImage;
    const char * NoteImageFormat = nullptr;
    QMediaPlayer NoteSoundPlayer;
    QBuffer currentNoteSound;
    QStringList currentGuitarPositions;

    void playSoundAtPendingGuitarPositionsAndContinue();
};

#endif // MAINWINDOW_H
