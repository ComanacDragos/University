#include "CoatsTableModel.h"

int CoatsTableModel::rowCount(const QModelIndex& parent) const
{
	return this->service.getUserRepositoryLength();
}

int CoatsTableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant CoatsTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	if (row == this->service.getUserRepositoryLength())
		return QVariant();

	TrenchCoat coat = this->service.getUserCoats()[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(coat.getName());
		case 1:
			return QString::fromStdString(coat.getSize());
		case 2:
			return QString::fromStdString(std::to_string(coat.getPrice()));
		case 3:
			return QString::fromStdString(coat.getPhotographSource());

		default:
			break;
		}
	}
	/*
	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 1)
		{
			return QBrush{ QColor{0, 250, 154} };
		}
	}
	*/
	return QVariant();
}

QVariant CoatsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Name" };
			case 1:
				return QString{ "Size" };
			case 2:
				return QString{ "Price" };
			case 3:
				return QString{ "Photograph source" };
			case 4:
				return QString{ "Picture" };
			default:
				break;
			}
		}
	}
	if (role == Qt::BackgroundRole)
	{
		return QBrush{ Qt::black };
	}
	return QVariant();
}

/*
bool CoatsTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{

	if (!index.isValid() || role != Qt::EditRole)
		return false;
	
	int coatIndex = index.row();

	if (coatIndex == this->service.getRepositoryLength())
	{
		this->beginInsertRows(QModelIndex{}, coatIndex, coatIndex);
		switch (index.column)
		{
		case 0:

		}
	}

	emit dataChanged(index, index);
}

Qt::ItemFlags CoatsTableModel::flags(const QModelIndex& index)
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
*/
void CoatsTableModel::beginAddRow()
{
	int repositoryLength = this->service.getUserRepositoryLength();
	this->beginInsertRows(QModelIndex(), repositoryLength, repositoryLength);
}

void CoatsTableModel::endAddRow()
{
	this->endInsertRows();
}

void CoatsTableModel::beginRemoveRow()
{
	int rows = this->rowCount() - 1;
	if (rows == -1)
		return;
	this->beginRemoveRows(QModelIndex(), rows, rows);
}

void CoatsTableModel::endRemoveRow()
{
	//int rows = this->rowCount() - 1;
	//if (rows == -1)
	//	return;
	this->endRemoveRows();	
}
