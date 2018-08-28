#ifndef OBJECT_LIST_MODEL_HPP
#define OBJECT_LIST_MODEL_HPP

#include "object_list_model.h"

template<class T>
ObjectListModel<T>::ObjectListModel(QObject* parent):
    QAbstractListModel(parent)
{}

template<class T>
const QList<T*>& ObjectListModel<T>::items() const
{
    return m_items;
}

template<class T>
int ObjectListModel<T>::count() const
{
    return m_items.count();
}

template<class T>
T* ObjectListModel<T>::takeAt(int index)
{
    if (index < 0 || index > m_items.size()) return nullptr;

    T* item = nullptr;
    this->beginRemoveRows(QModelIndex(), index, index);
    item = m_items.takeAt(index);
    this->endRemoveRows();
}

template<class T>
void ObjectListModel<T>::setItems(const QList<T*>& items)
{
    this->beginResetModel();

    m_items = items;

    this->endResetModel();
}


template<class T>
void ObjectListModel<T>::prepend(T* item)
{
    this->insert(0, item);
}

template<class T>
void ObjectListModel<T>::insert(int index, T* item)
{
    if (index < 0 || index > m_items.size()) return;

    this->beginInsertRows(QModelIndex(), index, index);

    m_items.insert(index, item);

    this->endInsertRows();
}

template<class T>
void ObjectListModel<T>::append(T* item)
{
    this->insert(m_items.size(), item);
}

template<class T>
void ObjectListModel<T>::removeAt(int index)
{
    if (index < 0 || index >= m_items.size()) return;

    this->beginRemoveRows(QModelIndex(), index, index);

    m_items.removeAt(index);

    this->endRemoveRows();
}

template<class T>
void ObjectListModel<T>::remove(T* item)
{
    this->removeAt(m_items.indexOf(item));
}

template<class T>
void ObjectListModel<T>::clear()
{
    this->beginResetModel();

    m_items.clear();

    this->endResetModel();
}

template<class T>
int ObjectListModel<T>::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return m_items.count();
}

template<class T>
QVariant ObjectListModel<T>::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.size()) return QVariant();

    if (role == Qt::DisplayRole) return QVariant::fromValue(m_items.at(index.row()));

    return QVariant();
}

#endif // OBJECT_LIST_MODEL_HPP
