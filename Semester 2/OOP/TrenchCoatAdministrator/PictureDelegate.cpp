#include "PictureDelegate.h"

PictureDelegate::PictureDelegate(QWidget* parent)
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QString coat = index.model()->data(index, Qt::EditRole).toString();

	if (index.column() != 4)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}
	if (index.row() % 2 == 0)
	{
		QPixmap pixMap("Coat1.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else
	{
		QPixmap pixMap("Coat2.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == 4)
	{
		return QSize(75, 100);
	}

	return QStyledItemDelegate::sizeHint(option, index);

}
