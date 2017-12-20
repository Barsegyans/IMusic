#include "track.h"

QString Track::name() const
{
    return m_name;
}

void Track::setName(const QString &name)
{
    m_name = name;
}

QTime Track::last() const
{
    return m_last;
}

void Track::setLast(const QTime &last)
{
    m_last = last;
}

int Track::rating() const
{
    return m_rating;
}

void Track::setRating(int rating)
{
    m_rating = rating;
}

QString Track::description() const
{
    return m_description;
}

void Track::setDescription(const QString &description)
{
    m_description = description;
}



Track *Track::toTrack()
{
    return this;
}

void Track::setParent(Item *par)
{
    if(par==0)
        m_parent=0;
    else
        if(par->toAlbum()!=0)
            m_parent=par;
}


Track::Track()
{

}
QDataStream& operator<< (QDataStream &stream, const Track &song)
{
    stream << song.name()
           << song.last()
           << song.rating()
           << song.description();
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Track &song)
{


    QString name;
    QTime last;
    QString description;
    int rating;

    stream >> name
           >> last
           >> rating
           >> description;
    song.setName(name);
    song.setLast(last);
    song.setRating(rating);
    song.setDescription(description);

    return stream;
}
