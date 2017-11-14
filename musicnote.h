#ifndef MUSICNOTE_H
#define MUSICNOTE_H

#include <QByteArray>
#include <QRegExp>
#include <QHash>
#include <QVector>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>

class MusicNote
{
public:
    MusicNote();
    static bool isNoteAvailable(const QString &NoteNotation);
    static const QString getRandomNote();
    static const QString getRamdomGuitarPosition();
    static const QStringList getGuitarPositionsOfNote(const QString &NoteNotation);
    static const QStringList getNotesOnGuitarFret(quint8 guitarFret);
    static const QStringList getNotesOnGuitarString(const QString &guitarString);
    static const QStringList getNotesOnGuitarString(quint8 guitarString);
    static const QString getNoteAtGuitarPosition(const QString &guitarPosition);
    static const QString getNoteAtGuitarPosition(const QString &guitarString, quint8 guitarFret);
    static const QString getNoteAtGuitarPosition(quint8 guitarString, quint8 guitarFret);
    static QByteArray *getImageDataOfTrebleClefNote(const QString &NoteNotation);
    static const QString getTrebleClefNoteImageDataFormat();
    static const QStringList getAvailableTrebleClefNotes();
    static const QString getGuitarNoteSoundDataFormat();
    static QByteArray *getSoundDataAtGuitarPosition(const QString &guitarPosition);
    static QByteArray *getSoundDataAtGuitarPosition(quint8 guitarString, quint8 guitarFret);
private:
    static const QString TrebleClefNoteImageDataFormat;
    static const QString GuitarNoteSoundDataFormat;
    static const QHash<QString,QByteArray*> &TrebleClefNoteImageByNoteNotation;
    static const QVector<QVector<QString>> &NoteNotationByGuitarPosition;
    static const QHash<QString,QByteArray*> &SoundByGuitarPosition;
};

#endif // MUSICNOTE_H
