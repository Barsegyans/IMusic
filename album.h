#pragma once
#include<QString>
#include<QPixmap>
#include <QList>
#include "track.h"
#ifndef ALBUM_H
#define ALBUM_H

class Artist;
class Album : public Item
{
    QString m_genre;
    QPixmap m_image;
    int m_year;
public:
    Album();

    void setName(const QString &name);
    void setYear(int year);
    void setImage(const QPixmap &image);
    void setDescription(const QString &description);
    void setGenre(const QString &genre);


    int getYear() const;
    QString getGenre() const;
    QString getDescription() const;
    QPixmap getImage() const;


    // Item interface
public:
    Album *toAlbum();

    // Item interface
public:
    void setParent(Item *par);
    void insertChild(Item *chl, int position=0);
};


QDataStream& operator <<(QDataStream&stream, const Album& album);
QDataStream& operator >>(QDataStream &stream, Album &album);


#endif // ALBUM_H
