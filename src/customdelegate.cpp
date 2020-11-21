#include "customdelegate.h"

#include <QDebug>
#include <QPainter>
#include <QThread>

CustomDelegate::CustomDelegate(QObject* parent)
    : QItemDelegate(parent),
      _cachedItemHeights(10000) // make cache large enough to hold all items
{
}

void CustomDelegate::paint(QPainter* painter, const QStyleOptionViewItem& opt, const QModelIndex& index) const
{
	const auto rect = opt.rect.adjusted(0, 0, -2, -1);
	painter->drawRect(rect);

	QString text = index.model()->data(index, Qt::DisplayRole).toString();
	painter->drawText(rect, Qt::AlignLeft, text);
}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex& index) const
{
	qDebug() << "size hint requested for index #" << index.row();

	int* cachedItemHeight;
	if (cachedItemHeight = _cachedItemHeights[index.row()])
	{
		qDebug() << "  took value from cache";
		return QSize(0, *cachedItemHeight);
	}

	// sleep to emulate text layouting taking place
	QThread::msleep(1);

	// make height depend somehow on index to emulate items with various heights
	const int itemHeight = 20 * (1 + index.row() % 10);
	qDebug() << "  calculating item height for index #" << index.row() << ", itemHeight = " << itemHeight;

	// add to cached
	_cachedItemHeights.insert(index.row(), new int(itemHeight));

	return QSize(0, itemHeight);
}
