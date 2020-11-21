#include "customdelegate.h"

#include <QDebug>
#include <QPainter>
#include <QThread>

CustomDelegate::CustomDelegate(QObject* parent)
    : QItemDelegate(parent),
      _cachedItemHeights(1000) // make cache large enough to hold all items
{
}

void CustomDelegate::paint(QPainter* painter, const QStyleOptionViewItem& opt, const QModelIndex& index) const
{
	const auto rect = opt.rect.adjusted(0, 0, -2, -1);
	painter->setPen(opt.state & QStyle::State_HasFocus ? Qt::red : Qt::black);
	painter->drawRect(rect);

	QString text = index.model()->data(index, Qt::DisplayRole).toString();
	painter->drawText(rect, Qt::AlignLeft, text);
}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex& index) const
{
	//qDebug() << "size hint requested for index #" << index.row();

	int* cachedItemHeight;
	if (cachedItemHeight = _cachedItemHeights[index.row()])
	{
		//qDebug() << "  took value from cache";
		return QSize(0, *cachedItemHeight);
	}

	// make height depend somehow on index to emulate items with various heights
	int itemHeight = 1;
	//for (int i = 0; i < 10000; ++i)
	itemHeight = int((itemHeight % 5) + 20 * (1 + (rand() % 100) / 10.0));
	qDebug() << "  calculating item height for index #" << index.row() << ", itemHeight = " << itemHeight;

	// add to cached
	_cachedItemHeights.insert(index.row(), new int(itemHeight));

	return QSize(100, itemHeight);
}
