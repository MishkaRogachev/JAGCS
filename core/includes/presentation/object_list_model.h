#ifndef OBJECT_LIST_MODEL_H
#define OBJECT_LIST_MODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <type_traits>

#include <QPointer>

template<class T> class ObjectListModel: public QAbstractListModel
{
public:
    explicit ObjectListModel(QObject* parent = nullptr);

    const QList<T*>& items() const;
    int count() const;

    T* takeAt(int index);

    void setItems(const QList<T*>& items);

    void prepend(T* item);
    void insert(int index, T* item);
    void append(T* item);

    void removeAt(int index);
    void remove(T* item);
    void clear();

private:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    QList<T*> m_items;

    Q_DISABLE_COPY(ObjectListModel)
};

#include "object_list_model.hpp"

#endif // OBJECT_LIST_MODEL_H
