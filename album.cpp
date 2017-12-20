#include "album.h"

int Album::getYear() const
{
    return m_year;
}


void Album::setYear(int year)
{
    m_year = year;
}


void Album::setName(const QString &name)
{
    m_name = name;
}

void Album::setGenre(const QString &genre)
{
    m_genre = genre;
}

QString Album::getGenre() const
{
    return m_genre;
}

QString Album::getDescription() const
{
    return m_description;
}

void Album::setDescription(const QString &description)
{
    m_description = description;
}

QPixmap Album::getImage() const
{
    return m_image;
}

Album *Album::toAlbum()
{
    return this;
}

void Album::setParent(Item *par)
{
    if(par==0)
        m_parent=0;
    else
        if(par->toArtist()!=0)
            m_parent=par;
}

void Album::insertChild(Item *chl, int position)
{
    if(chl->toTrack()!=NULL){
        m_children.insert(position,chl);
        chl->setParent(this);
    }
}

void Album::setImage(const QPixmap &image)
{
    m_image = image;
}



Album::Album()
{

}

QDataStream& operator<< (QDataStream &stream, const Album &album)
{
    stream << album.name()
           << album.getImage()
           << album.getGenre()
           << album.getYear()
           << album.getDescription();
    stream << album.childCount();
    for(int i=0; i < album.childCount(); i++)
    {
        Track *Track = album.childAt(i)->toTrack();
        if (Track) stream << *Track;
    }
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Album &album)
{

    QString name;
    QPixmap cover;
    QString genre;
    int year;
    QString description;
    int Track_count;
    Track *sng;

    stream >> name
           >> cover
           >> genre
           >> year
           >> description;
    album.setName(name);
    album.setImage(cover);
    album.setGenre(genre);
    album.setYear(year);
    album.setDescription(description);

    stream >> Track_count;
    for (int i =0; i<Track_count; i++)
    {
        sng = new Track();
        stream >> *sng;
        album.insertChild(sng, i);
    }
    return stream;
}
