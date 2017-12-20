#include <QString>
#include <QList>
#ifndef ITEM_H
#define ITEM_H

class Artist;
class Album;
class Track;
class Item {
public:
    Item();
    ~Item();
    Item *parent();
    virtual void setParent(Item *par);
    virtual void insertChild(Item * chl, int position = 0);
    Item *takeChild(int);
    Item *childAt(int) const;
    int indexOf(Item*) const;
    int childCount() const;
    virtual Artist* toArtist();
    virtual Album* toAlbum();
    virtual Track* toTrack();

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

protected:
    Item *m_parent=0;
    QList<Item*> m_children;
    QString m_name;
    QString m_description;
};

#endif // ITEM_H
