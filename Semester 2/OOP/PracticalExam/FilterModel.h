#pragma once
#include <QSortFilterProxyModel>
#include "Service.h"
class FilterModel:public QSortFilterProxyModel
{
private:
	Service& srv;
	std::string constelation;
public:
	FilterModel(Service& srv, const std::string constelation, QObject* parent = nullptr) :srv{ srv }, constelation{constelation},QSortFilterProxyModel{parent}
	{

	}
	void beginAddRow()
	{
		int row = this->srv.getAstronomers().size();
		this->beginInsertRows(QModelIndex(), row, row);
	}
	void endAddRow()
	{
		this->endInsertRows();
	}

protected:
	bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override
	{
		std::string name = sourceModel()->index(sourceRow, 0, sourceParent).data().toString().toStdString();
		if (this->constelation == this->srv.getStar(name).getConstelation())
			return true;
		return false;
	}

	bool lessThan(const QModelIndex& left, const QModelIndex& right) const
	{
		return true;
	}


};

