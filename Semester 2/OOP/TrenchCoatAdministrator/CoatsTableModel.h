#pragma once
#include <QAbstractTableModel>
#include <qbrush.h>
#include <qcolor.h>
#include "CoatService.h"

class CoatsTableModel : public QAbstractTableModel
{
private:
	CoatService& service;
public:
	CoatsTableModel(CoatService& service, QObject* parent = NULL) :service{ service }{}
	~CoatsTableModel(){}

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	//bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	//Qt::ItemFlags flags(const QModelIndex& index);

	void beginAddRow();
	void endAddRow();

	void beginRemoveRow();
	void endRemoveRow();
};

