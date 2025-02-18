#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include <vector>
#include <qdebug.h>

using namespace std;

class TableModel : public QAbstractTableModel {
    std::vector<Magazin> magazine;
public:
    TableModel(const std::vector<Magazin>& magazine) : magazine{ magazine } {
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return magazine.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            Magazin p = magazine[index.row()];
            if (index.column() == 0) {
                return QString::fromStdString(p.get_name());
            }
            else if (index.column() == 1) {
                return QString::fromStdString(p.get_producer());
            }
            else if (index.column() == 2) {
                return QString::fromStdString(p.get_type());
            }
            else if (index.column() == 3) {
                return QString::number(p.get_price());
            }
        }

        return QVariant{};
    }

    void setMagazine(const vector<Magazin>& magazine) {
        this->magazine = magazine;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(rowCount() - 1, columnCount() - 1);
        emit dataChanged(topLeft, bottomR);
        emit layoutChanged(); // Emit a signal to update the layout
    }
};
