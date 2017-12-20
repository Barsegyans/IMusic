#include "artist.h"
#include "album.h"
QString Artist::name() const
{
    return m_name;
}

void Artist::setName(const QString &name)
{
    m_name = name;
}

QString Artist::country() const
{
    return m_country;
}

void Artist::setCountry(const QString &country)
{
    m_country = country;
}

QString Artist::description() const
{
    return m_description;
}

void Artist::setDescription(const QString &description)
{
    m_description = description;
}

QPixmap Artist::image() const
{
    return m_image;
}

void Artist::setImage(const QPixmap &image)
{
    m_image = image;
}



Artist* Artist::toArtist() //const
{
    return this;
}

void Artist::insertChild(Item *chl, int position)
{
    if(chl->toAlbum()!=NULL){
        m_children.insert(position,chl);
        chl->setParent(this);
    }
}

Artist::Artist()
{

}
QDataStream& operator<< (QDataStream &stream, const Artist &artist)
{
    stream << artist.name()
           << artist.image()
           << artist.country()
           << artist.description();
    stream << artist.childCount();
    for(int i=0; i < artist.childCount(); i++)
    {
        Album const* album = artist.childAt(i)->toAlbum();
        if (album) stream << *album;
    }
    return stream;
}


QDataStream &operator >>(QDataStream &stream, Artist &artist)
{
    QString name;
    QPixmap image;
    QString description;
    QString country;
    int album_count;
    Album *alb;

    stream >> name
           >> image
           >> country
           >> description;
    artist.setName(name);
    artist.setCountry(country);
    artist.setImage(image);
    artist.setDescription(description);

    stream >> album_count;
    for (int i =0; i<album_count; i++)
    {
        alb = new Album();
        stream >> *alb;
        artist.insertChild(alb,i);
    }
    return stream;
}

