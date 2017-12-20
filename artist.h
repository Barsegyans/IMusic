#pragma once
#include <QString>
#include <QPixmap>
#include <QList>
#include "album.h"
#ifndef ARTIST_H
#define ARTIST_H



class Artist :public Item
{
    QString m_country;
    QPixmap m_image;
public:
    Artist();
    QString name() const;
    void setName(const QString &name);
    QString country() const;
    void setCountry(const QString &country);
    QString description() const;
    void setDescription(const QString &description);
    QPixmap image() const;
    void setImage(const QPixmap &image);
    // Item interface
public:
    Artist *toArtist();

    // Item interface
public:
    void insertChild(Item *chl, int position=0);
};


QDataStream& operator <<(QDataStream&stream, const Artist& artist);

QDataStream& operator >>(QDataStream &stream, Artist &artist);


#endif // ARTIST_H
