#include "TableModel.h"

int TableModel::rowCount(const QModelIndex& parent) const
{
	return this->srv.getStars().size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	if (row == this->srv.getStars().size())
		return QVariant();

	Star star = this->srv.getStars()[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(star.getName());
		//case 1:
		//	return QString::fromStdString(star.getConstelation());
		case 1:
			return QString::fromStdString(std::to_string(star.getRA()));
		case 2:
			return QString::fromStdString(std::to_string(star.getDec()));
		case 3:
			return QString::fromStdString(std::to_string(star.getDiameter()));

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
				return QString{ "Name" };
			//case 1:
			//	return QString{ "Constelation" };
			case 1:
				return QString{ "RA" };
			case 2:
				return QString{ "DEC" };
			case 3:
				return QString{ "Diameter" };
			default:
				break;
			}
		}
	}
	return QVariant();
}

void TableModel::beginAddRow()
{
	int row = this->srv.getAstronomers().size();
	this->beginInsertRows(QModelIndex(), row, row);
}

void TableModel::endAddRow()
{
	this->endInsertRows();
}
