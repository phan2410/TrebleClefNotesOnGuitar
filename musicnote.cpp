#include "musicnote.h"

MusicNote::MusicNote()
{

}

bool MusicNote::isNoteAvailable(const QString &NoteNotation)
{
    return TrebleClefNoteImageByNoteNotation.contains(NoteNotation);
}

const QString MusicNote::getRandomNote()
{
    return TrebleClefNoteImageByNoteNotation.keys().at(qrand()%(TrebleClefNoteImageByNoteNotation.size()));
}

const QString MusicNote::getRamdomGuitarPosition()
{
    return NoteNotationByGuitarPosition.at(qrand()%6).at(0) + QStringLiteral("+") + QString::number(qrand()%13);
}

const QStringList MusicNote::getGuitarPositionsOfNote(const QString &NoteNotation)
{
    QStringList tmpReturn;
    if (TrebleClefNoteImageByNoteNotation.contains(NoteNotation))
    {
        int firstIndex;
        for (quint8 i = 0; i <= 5; ++i)
        {
            firstIndex = -1;
            const QVector<QString> &tmpNotesOnAGuitarString = NoteNotationByGuitarPosition.at(i);
            switch (NoteNotation.size()) {
            case 2:
            {
                firstIndex = tmpNotesOnAGuitarString.indexOf(NoteNotation,0);
                break;
            }
            case 3:
            {
                QString currentNote;
                for (quint8 j = 1; j < tmpNotesOnAGuitarString.size(); ++j)
                {
                    currentNote = tmpNotesOnAGuitarString.at(j);
                    if (currentNote.size() > 3 && currentNote.contains(NoteNotation))
                    {
                        firstIndex = j;
                        break;
                    }
                }
                break;
            }
            default:
                break;
            }
            if (firstIndex > -1)
            {
                tmpReturn.append(tmpNotesOnAGuitarString.at(0) + QStringLiteral("+") + QString::number(firstIndex,10));
            }
        }
    }
    return tmpReturn;
}

const QStringList MusicNote::getNotesOnGuitarFret(quint8 guitarFret)
{
    QStringList tmpReturn;
    if (guitarFret < 13)
    {
        tmpReturn.append(QStringLiteral());
        for (quint8 i = 0; i <= 5; ++i)
        {
            tmpReturn.append(NoteNotationByGuitarPosition.at(i).at(guitarFret));
        }
    }
    return tmpReturn;
}

const QStringList MusicNote::getNotesOnGuitarString(const QString &guitarString)
{
    if (TrebleClefNoteImageByNoteNotation.contains(guitarString))
    {
        for (quint8 i = 0; i <= 5; ++i)
        {
            if (guitarString == NoteNotationByGuitarPosition.at(i).at(0))
            {
                return QStringList::fromVector(NoteNotationByGuitarPosition.at(i));
            }
        }
    }
    return QStringList();
}

const QStringList MusicNote::getNotesOnGuitarString(quint8 guitarString)
{
    if (guitarString > 1 && guitarString < 6)
        return QStringList::fromVector(NoteNotationByGuitarPosition.at(guitarString-1));
    return QStringList();
}

const QString MusicNote::getNoteAtGuitarPosition(const QString &guitarPosition)
{
    QStringList tmpPos = guitarPosition.split('+',QString::SkipEmptyParts);
    if (tmpPos.size() == 2)
    {
        if (QRegExp(QStringLiteral("\\d*")).exactMatch(tmpPos.at(1)))
            return getNoteAtGuitarPosition(tmpPos.at(0),tmpPos.at(1).toInt());
    }
    return QStringLiteral();
}

const QString MusicNote::getNoteAtGuitarPosition(const QString &guitarString, quint8 guitarFret)
{
    if (TrebleClefNoteImageByNoteNotation.contains(guitarString) && guitarFret < 13)
    {
        for (quint8 i = 0; i <= 5; ++i)
        {
            if (guitarString == NoteNotationByGuitarPosition.at(i).at(0))
            {
                return NoteNotationByGuitarPosition.at(i).at(guitarFret);
            }
        }
    }
    return QStringLiteral();
}

const QString MusicNote::getNoteAtGuitarPosition(quint8 guitarString, quint8 guitarFret)
{
    if (guitarString > 1 && guitarString < 6 && guitarFret < 13)
        return NoteNotationByGuitarPosition.at(guitarString-1).at(guitarFret);
    return QStringLiteral();
}

QByteArray *MusicNote::getImageDataOfTrebleClefNote(const QString &NoteNotation)
{
    if (TrebleClefNoteImageByNoteNotation.contains(NoteNotation))
        return TrebleClefNoteImageByNoteNotation.value(NoteNotation);
    return nullptr;
}

const QString MusicNote::getTrebleClefNoteImageDataFormat()
{
    return TrebleClefNoteImageDataFormat;
}

const QStringList MusicNote::getAvailableTrebleClefNotes()
{
    return TrebleClefNoteImageByNoteNotation.keys();
}

const QString MusicNote::getGuitarNoteSoundDataFormat()
{
    return GuitarNoteSoundDataFormat;
}

QByteArray *MusicNote::getSoundDataAtGuitarPosition(const QString &guitarPosition)
{
    if (SoundByGuitarPosition.contains(guitarPosition))
        return SoundByGuitarPosition.value(guitarPosition);
    return nullptr;
}

QByteArray *MusicNote::getSoundDataAtGuitarPosition(quint8 guitarString, quint8 guitarFret)
{
    if (guitarString > 1 && guitarString < 6 && guitarFret < 13)
        return getSoundDataAtGuitarPosition(NoteNotationByGuitarPosition.at(guitarString-1).at(0)
                                            + QStringLiteral("+")
                                            + QString::number(guitarFret,10));
    return nullptr;
}

const QString MusicNote::TrebleClefNoteImageDataFormat = QStringLiteral("PNG");
const QString MusicNote::GuitarNoteSoundDataFormat = QStringLiteral("WAV");

const QHash<QString,QByteArray*> &MusicNote::TrebleClefNoteImageByNoteNotation = [](){
    QHash<QString,QByteArray*> lambdaReturn;
    QDirIterator aMusicNoteImage(QDir::currentPath(),
                                 QStringList() << QStringLiteral("*.") + TrebleClefNoteImageDataFormat,
                                 QDir::Files,
                                 QDirIterator::Subdirectories);
    QFileInfo tmpFileInfo;
    while (aMusicNoteImage.hasNext())
    {
        tmpFileInfo = QFileInfo(aMusicNoteImage.next());
        QFile tmpFile(tmpFileInfo.absoluteFilePath());
        if (tmpFile.open(QIODevice::ReadOnly))
        {
            lambdaReturn.insert(tmpFileInfo.baseName(),new QByteArray(tmpFile.readAll()));
            tmpFile.close();
        }
    }
    return lambdaReturn;
}();

const QVector<QVector<QString>> &MusicNote::NoteNotationByGuitarPosition
= QVector<QVector<QString>>({
                                QVector<QString>({"E3","F3","F3#=G3b","G3","G3#=A3b","A3","A3#=B3b","B3","C4","C4#=D4b","D4","D4#=E4b","E4"}),
                                QVector<QString>({"A3","A3#=B3b","B3","C4","C4#=D4b","D4","D4#=E4b","E4","F4","F4#=G4b","G4","G4#=A4b","A4"}),
                                QVector<QString>({"D4","D4#=E4b","E4","F4","F4#=G4b","G4","G4#=A4b","A4","A4#=B4b","B4","C5","C5#=D5b","D5"}),
                                QVector<QString>({"G4","G4#=A4b","A4","A4#=B4b","B4","C5","C5#=D5b","D5","D5#=E5b","E5","F5","F5#=G5b","G5"}),
                                QVector<QString>({"B4","C5","C5#=D5b","D5","D5#=E5b","E5","F5","F5#=G5b","G5","G5#=A5b","A5","A5#=B5b","B5"}),
                                QVector<QString>({"E5","F5","F5#=G5b","G5","G5#=A5b","A5","A5#=B5b","B5","C6","C6#=D6b","D6","D6#=E6b","E6"})
                            });

const QHash<QString,QByteArray*> &MusicNote::SoundByGuitarPosition = [](){
    QHash<QString,QByteArray*> lambdaReturn;
    QDirIterator aMusicNoteSound(QDir::currentPath(),
                                 QStringList() << QStringLiteral("*.") + GuitarNoteSoundDataFormat,
                                 QDir::Files,
                                 QDirIterator::Subdirectories);
    QFileInfo tmpFileInfo;
    while (aMusicNoteSound.hasNext())
    {
        tmpFileInfo = QFileInfo(aMusicNoteSound.next());
        QFile tmpFile(tmpFileInfo.absoluteFilePath());
        if (tmpFile.open(QIODevice::ReadOnly))
        {
            lambdaReturn.insert(tmpFileInfo.baseName(),new QByteArray(tmpFile.readAll()));
            tmpFile.close();
        }
    }
    return lambdaReturn;
}();
