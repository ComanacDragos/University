#pragma once
#include <QAbstractTableModel>
#include "Service.h"

class TableModel : public QAbstractTableModel
{
private:
	Service& srv;

public:
	TableModel(Service& srv, QObject* parent=NULL):srv{srv}{}

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void beginAddRow();
	void endAddRow();
};

