#include "AccountOverviewTableModel.h"

void AccountOverviewTableModel::clear() {
    beginResetModel();
    overviews_.clear();
    endResetModel();
}

void AccountOverviewTableModel::addAccount( const AccountPtr& account ) {
    AccountOverview overview;
    overview.balance = formatCents( account->balance() );
    overview.name = account->name();
    overview.account = account;

    beginInsertRows( QModelIndex(), overviews_.size(), overviews_.size() );
    overviews_.push_back( overview );
    endInsertRows();
}

AccountPtr AccountOverviewTableModel::account( const QModelIndex& index ) const {
    if( index.model() != this ) {
        throw std::runtime_error( "AccountOverviewTableModel::account called with wrong index" );
    }
    return overviews_[index.row()].account;
}

int AccountOverviewTableModel::rowCount( const QModelIndex& parent ) const {
    return overviews_.size();
}

int AccountOverviewTableModel::columnCount( const QModelIndex& parent ) const {
    return 2;
}

QVariant AccountOverviewTableModel::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ) {
        return QVariant();
    }

    if( role == Qt::DisplayRole ) {
        switch( index.column() ) {
            case 0:
                return overviews_[index.row()].name;
                break;
            case 1:
                return overviews_[index.row()].balance;
                break;
        }
    }

    if( role == Qt::TextAlignmentRole ) {
        switch( index.column() ) {
            case 0:
                return Qt::AlignLeft | Qt::AlignVCenter;
                break;
            case 1:
                return Qt::AlignRight | Qt::AlignVCenter;
                break;
        }
    }
    return QVariant();
}

QVariant AccountOverviewTableModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QAbstractTableModel::headerData( section, orientation, role );
    }

    if( orientation == Qt::Horizontal ) {
        switch( section ) {
            case 0:
                return "Name";
                break;
            case 1:
                return "Kontostand";
                break;
        }
    }

    if( orientation == Qt::Vertical ) {
        return section + 1;
    }

    return QAbstractTableModel::headerData( section, orientation, role );
}