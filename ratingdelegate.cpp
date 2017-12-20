#include "ratingdelegate.h"
#include "artist.h"
#include <QModelIndex>
#include <QPainter>
#include<QDebug>

RatingDelegate::RatingDelegate()
{

}

QSize RatingDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    return QSize(100,20);
}
void RatingDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    int rating = 0;
    int top, left;
    QBrush b_in(Qt::yellow);
    QBrush b_out(Qt::NoBrush);
    if(index.isValid() == false)
    {
        return;
    }
    if(index.parent().isValid() == false)
    {
        return;
    }
    top = option.rect.top();
    left = option.rect.left();
    painter->setPen(QPen(Qt::black, 1));
    Item *item = static_cast<Item *>(index.internalPointer());

    if(index.column() == 2)
    {
        if(!item->toTrack()){
            return;
        }
        rating = index.data().toInt();
        if(rating > 5) rating = 5;
        if(rating < 0) rating = 0;
        for(int counter = 0; counter < 5; counter++)
        {
            if(rating > 0 && counter < rating)
                painter->setBrush(b_in);
            else
                painter->setBrush(b_out);
            painter->drawEllipse(QPoint(left + 10, top + 10), 8, 8);
            left += 20;
        }
    }
}
QWidget * RatingDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
    if(!index.parent().isValid())
    {
        return  QStyledItemDelegate::createEditor(parent, option, index);
    }
    Item *item = static_cast<Item *>(index.internalPointer());
    if(!item->parent()->toAlbum()){
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
    if(!item->toTrack()){
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
    RatingWidget *editor = new RatingWidget(parent);
    connect(editor, SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
    return editor;
}
void RatingDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    Item *item;
    int rating;
    if(!index.isValid())
    {
        QStyledItemDelegate::setEditorData(editor, index);
        return;
    }
    if(!index.parent().isValid())
    {
        QStyledItemDelegate::setEditorData(editor, index);
        return;
    }
    item = static_cast<Item *>(index.internalPointer());
    if(!item->toTrack()){
        QStyledItemDelegate::setEditorData(editor, index);
        return;
    }
    if(index.column() == 2)
    {
        rating = index.data().toInt();
        RatingWidget *Editor = qobject_cast<RatingWidget *>(editor);

        connect(editor, SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
        Editor->setRate(rating);
    }
    else
        QStyledItemDelegate::setEditorData(editor, index);
}
void RatingDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Item *item;
    int rating;
    if(!index.isValid())
    {
        QStyledItemDelegate::setModelData(editor, model, index);
        return;
    }
    if(!index.parent().isValid())
    {
        QStyledItemDelegate::setModelData(editor, model, index);
        return;
    }
    item = static_cast<Item *>(index.internalPointer());
    if(!item->parent()->toAlbum()){
        QStyledItemDelegate::setModelData(editor, model, index);
        return;
    }
    if(!item->toTrack()){
        QStyledItemDelegate::setModelData(editor, model, index);
        return;
    }
    if(index.column() == 2)
    {
        RatingWidget *Editor = qobject_cast<RatingWidget *>(editor);
        connect(editor, SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
        item->toTrack()->setRating(Editor->rate());
    }
    else
    QStyledItemDelegate::setModelData(editor, model, index);
}
void RatingDelegate::commitAndCloseEditor()
{
    RatingWidget *editor = qobject_cast<RatingWidget *>(sender());

    connect(editor, SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
    emit commitData(editor);
    emit closeEditor(editor);
}
