#include "TableModel.h"

int TableModel::rowCount(const QModelIndex& parent) const
{
	return this->srv.getIdeeas().size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	if (row == this->srv.getIdeeas().size())
		return QVariant();

	Idea idea = this->srv.getSortedIdeeas()[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(idea.getDesc());
		case 1:
			return QString::fromStdString(idea.getStatus());
		case 2:
			return QString::fromStdString(idea.getCreator());
		case 3:
			return QString::fromStdString(std::to_string(idea.getAct()));

		default:
			break;
		}
		
	}
	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Description" };
			case 1:
				return QString{ "Status" };
			case 2:
				return QString{ "Creator" };
			case 3:
				return QString{ "Act" };
			case 4:
				return QString{ "Picture" };
			default:
				break;
			}
		}
	}
	return QVariant();

}

void TableModel::beginAddRow()
{
	int row = this->srv.getIdeeas().size();
	this->beginInsertRows(QModelIndex(),row,row);
}

void TableModel::endAddRow()
{
	this->endInsertRows();
}
