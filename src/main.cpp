#include "customdelegate.h"

#include <QApplication>
#include <QAbstractListModel>
#include <QListView>

class Model : public QAbstractListModel
{
public:
   using QAbstractListModel::QAbstractListModel;

protected:
    virtual int rowCount(const QModelIndex& parent) const override {
        if (parent.isValid()) return 0;
        return 5000;
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

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

    Model model;

	QListView listView;
	listView.setLayoutMode(QListView::Batched);
	listView.setBatchSize(10);
	listView.setItemDelegate(new CustomDelegate(&listView));
	listView.setModel(&model);

    listView.show();

    // NOTE: it takes several seconds this the list is loaded!!!
    // debug logs show that sizeHint for ALL items is requested upon startup

	return app.exec();
}
