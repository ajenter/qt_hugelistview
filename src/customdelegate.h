#pragma once
#include <QItemDelegate>
#include <QCache>

class CustomDelegate : public QItemDelegate
{
	Q_OBJECT

public:
   explicit CustomDelegate(QObject* parent);

protected:
	void paint(QPainter* painter, const QStyleOptionViewItem&, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const override;

private:
    mutable QCache<int, int> _cachedItemHeights;
};
