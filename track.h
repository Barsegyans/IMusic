
#ifndef TRACK_H
#define TRACK_H
#include <QTime>
#include "item.h"
#include<QDataStream>

class Artist;
class Album;

class Track:public Item
{
    QTime m_last;
    int m_rating;
public:
    Track();
    QString name() const;
    void setName(const QString &name);
    QTime last() const;
    void setLast(const QTime &last);
    int rating() const;
    void setRating(int rating);
    QString description() const;
    void setDescription(const QString &description);

    // Item interface
public:
    Track *toTrack();

    // Item interface
public:
    void setParent(Item *par);

};


QDataStream& operator <<(QDataStream&stream, const Track& Track);
QDataStream& operator >>(QDataStream &stream, Track &Track);




#endif // TRACK_H
