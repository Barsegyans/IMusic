#include "item.h"
#include<QDebug>
Item::Item()
{

}

Item::~Item()
{
    int num=m_children.length();
    for(int i=0;i<num;i++){
        //qDebug()<<"Here";
        m_children.at(0)->setParent(0);
        delete m_children.takeAt(0);
    }

    if(m_parent!=0){
        m_parent->takeChild(m_parent->indexOf(this));
    }
    setParent(0);
}

Item *Item::parent()
{
    return m_parent;
}

void Item::setParent(Item *par)
{
    m_parent=par;
}

void Item::insertChild(Item *chl, int position)
{
    m_children.insert(position,chl);
    chl->setParent(this);
}

int Item::indexOf(Item *itm) const
{
    return m_children.indexOf(itm);
}

int Item::childCount() const
{
    return m_children.length();
}

Artist *Item::toArtist()
{
    return NULL;
}

Album *Item::toAlbum()
{
    return NULL;
}

Track *Item::toTrack()
{
    return NULL;
}

QString Item::name() const
{
    return m_name;
}

void Item::setName(const QString &name)
{
    m_name = name;
}

QString Item::description() const
{
    return m_description;
}

void Item::setDescription(const QString &description)
{
    m_description = description;
}


Item *Item::takeChild(int n)
{
    return m_children.takeAt(n);
}

Item *Item::childAt(int n) const
{
    return m_children.at(n);
}
