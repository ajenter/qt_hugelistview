#include "customdelegate.h"

#include <QAbstractListModel>
#include <QApplication>
#include <QHeaderView>
#include <QItemSelection>
#include <QScrollBar>
#include <QTableView>

class Model : public QAbstractListModel
{
public:
	using QAbstractListModel::QAbstractListModel;

protected:
	virtual int rowCount(const QModelIndex& parent) const override
	{
		if (parent.isValid()) return 0;
		return 100000;
	}

	virtual QVariant data(const QModelIndex& index, int role) const
	{
		switch (role)
		{
			case Qt::DisplayRole:
				return QString("This is item #%1").arg(index.row());

			default:
				return QVariant();
		}
	}
};

void updateRowHeights(QTableView& table)
{
	static QItemSelection sel;

	const QRect viewportRect = table.viewport()->rect();

	QModelIndex topRowIndex = table.indexAt(QPoint(viewportRect.x() + 5, viewportRect.y() + 5));
	QModelIndex bottomRowIndex = table.indexAt(QPoint(viewportRect.x() + 5, viewportRect.y() + viewportRect.height() - 5));
	//qDebug() << "top row: " << topRowIndex.row() << ", bottom row: " << bottomRowIndex.row();

	for (auto i = topRowIndex.row() - 1; i < bottomRowIndex.row() + 1; ++i)
	{
		auto index = table.model()->index(i, 0);
		if (!sel.contains(index))
		{
			table.resizeRowToContents(i);
			sel.select(index, index);
			//qDebug() << "Marked row #" << i << " as resized";
		}
	}
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Model model;

	QTableView table;
	table.resize(600, 800);
	table.setSelectionBehavior(QAbstractItemView::SelectRows);
	table.horizontalHeader()->setStretchLastSection(true);
	table.setItemDelegateForColumn(0, new CustomDelegate(&table));
	table.horizontalHeader()->hide();
	table.verticalHeader()->hide();
	table.setModel(&model);
	table.setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	table.show();

	updateRowHeights(table);

	table.connect(table.verticalScrollBar(), &QScrollBar::valueChanged, [&table](int) {
		updateRowHeights(table);
	});

	return app.exec();
}
