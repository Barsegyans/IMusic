#include "musicmodel.h"
#include "albumdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include<QDebug>

MusicModel::MusicModel()
{
    m_root = new Item();
    int i=1;
        Artist *art=new Artist;
        Album *alb=new Album;
        Track *tr1=new Track;
        Track *tr2=new Track;
        art->setName(" Artist "+i);
        alb->setName("Album");
        art->setCountry(" Country "+i);
        art->setDescription(" Example of actor");
        alb->setParent(art);
        alb->setDescription(" Example of album");
        alb->setYear(i);
        alb->setGenre(" music");
        tr1->setName(" Track1 "+i);
        tr1->setDescription(" Example of track1");
        tr2->setName(" Track2 "+i);
        tr2->setDescription(" Example of track2");
        tr1->setParent(alb);
        tr2->setParent(alb);
        tr1->setRating(5);
        tr2->setRating(1);
        alb->insertChild(tr1);
        alb->insertChild(tr2);
        art->insertChild(alb);
        m_root->insertChild(art);

}



QModelIndex MusicModel::index(int row, int column, const QModelIndex &parent) const
{
    Item *parentItem = m_root;

    if(parent.isValid())
    {
        parentItem = static_cast<Item *>(parent.internalPointer());
    }
    if(parentItem->childCount() > row)
        if(parentItem->childAt(row))
        {
            return createIndex(row, column, parentItem->childAt(row));
        }
    return QModelIndex();
}

QModelIndex MusicModel::parent(const QModelIndex &child) const
{
    if(!child.isValid()) return QModelIndex();
    else
    {
        Item *child_item = static_cast<Item*>(child.internalPointer());
        if(child_item == m_root) return QModelIndex();
        if(child_item->parent() == m_root) return QModelIndex();
        if(!child_item->parent()) return QModelIndex();
        else
        {
            Item *parent = child_item->parent();
            if(!parent->parent()) return QModelIndex();
            else
            {
                Item *grandparent = parent->parent();
                return createIndex(grandparent->indexOf(parent),0,parent);
            }
        }
    }
}

QVariant MusicModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QObject::tr("Name");
        case 1:
            return QObject::tr("Last");
        case 2:
            return QObject::tr("Rating");
        case 3:
            return QObject::tr("Description");
        }
    }
    return QVariant();
}

int MusicModel::columnCount(const QModelIndex &parent) const
{

       return 4;

}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        Item *item;
        item = static_cast<Item *>(parent.internalPointer());
        return item->childCount();
    }
    return m_root->childCount();
}

QVariant MusicModel::MusicModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(index.isValid())
        {
            int coloumn = index.column();
            Item *item = static_cast<Item*>(index.internalPointer());
            if(item)
            {
                switch (coloumn)
                {
                case 0:
                    return item->name();
                    break;
                case 1:
                    if(item->toTrack()) return item->toTrack()->last();
                    break;
                case 2:
                    if(item->toTrack()) return item->toTrack()->rating();
                    break;
                case 3:
                    return item->description();
                    break;

                }

            }
            else return QVariant();

        }
        else return QVariant();
    }
    if (role == Qt::EditRole)
    {
        if(index.isValid())
        {
            int coloumn = index.column();
            Item *item = static_cast<Item*>(index.internalPointer());
            if(item)
            {
                switch (coloumn)
                {
                case 0:
                    return item->name();
                    break;
                case 1:
                    if(item->toTrack()) return item->toTrack()->last();
                    break;
                case 2:
                    if(item->toTrack()) return item->toTrack()->rating();
                    break;
                case 3:
                     item->description();
                    break;

                }

            }
            else return QVariant();

        }
        else return QVariant();
    }
    return QVariant();
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid())
    {
        if(role != Qt::EditRole && role != Qt::DisplayRole)
            return false;
        int coloumn = index.column();
        int row = index.row();
        Item * item = static_cast<Item *>(index.internalPointer());
        if (item)
        {
            switch (coloumn)
            {
                case 0:
                    item->setName(value.toString());
                    break;
                case 1:
                    if (item->toTrack()){
                        QTime duration = QTime::fromString( value.toString(), Qt::ISODate );
                        item->toTrack()->setLast(duration);
                    }else if(item->toAlbum()){
                        item->toAlbum()->setGenre(value.toString());
                    }else if(item->toArtist()){
                        item->toArtist()->setCountry(value.toString());
                    }
                    break;
                case 2:
                    if (item->toTrack()){
                        item->toTrack()->setRating(value.toInt());
                    }
                    else if(item->toAlbum()){
                        item->toAlbum()->setYear(value.toInt());
                    }
                    break;
                case 3:
                    item->setDescription(value.toString());
                    break;
                case 4:
                if (item->toArtist()){
                    item->toArtist()->setImage(value.value<QPixmap>());
                }
                else if(item->toAlbum()){
                    item->toAlbum()->setImage(value.value<QPixmap>());
                }

            }
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;

}

bool MusicModel::insertRow(int row, const QModelIndex &parent)
{
    Item *p_item;
    if(parent.isValid()) p_item = static_cast<Item *>(parent.internalPointer());
    else p_item = m_root;
    Item* item;
    if(p_item==m_root) item = new Artist();
    if(p_item->toArtist()) item = new Album();
    if(p_item->toAlbum()) item = new Track();
    beginInsertRows(parent, row, row);
    p_item->insertChild(item, row);
    endInsertRows();
    return true;



}

bool MusicModel::removeRow(int row, const QModelIndex &parent)
{
    Item *p_item;
    if(parent.isValid()) p_item = static_cast<Item *>(parent.internalPointer());
    else p_item = m_root;
    if(p_item)
    {
        beginRemoveRows(parent, row, row);
        p_item->takeChild(row);
        endRemoveRows();
        return true;
    }
    else return false;

}

QDataStream& operator<< (QDataStream &stream, Item &root)
{

    stream << root.childCount();
    for(int i=0; i < root.childCount(); i++)
    {
        Artist const* artist = root.childAt(i)->toArtist();
        if (artist) stream << *artist;
    }
    return stream;
}

QDataStream& operator>> (QDataStream &stream, Item &root)
{

    int artist_count;
    Artist *art;
    stream >> artist_count;
    for (int i =0; i<artist_count; i++)
    {
        art = new Artist();
        stream >> *art;
        root.insertChild(art,i);
    }
    return stream;
}

