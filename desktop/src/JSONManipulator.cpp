//
// Created by Command_maker on 19/08/2023.
//

#include "JSONManipulator.h"

#include <QFile>
#include <QJsonDocument>

using namespace std::filesystem;

JSONManipulator::JSONManipulator(const QString &path) {
    QString val;
    QFile config_file(path);
    if (!config_file.exists()) return;
    config_file.open(QIODevice::ReadWrite | QIODevice::Text);
    val = config_file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    m_root = doc.object();
}


void JSONManipulator::set(const QString &key, const QVariant &value) {
    QStringList pathComponents = key.split('.');

    QVector<QJsonObject> valuesUpToPath = {m_root};

    //Ensure the path up to the last value exists,
    for (int i = 0; i < pathComponents.size() - 1; i++) {
        QString const &currentKey = pathComponents[i];

        if (!valuesUpToPath.last().contains(currentKey)) {
            valuesUpToPath.last()[currentKey] = QJsonObject();
        }

        valuesUpToPath.push_back(valuesUpToPath.last()[currentKey].toObject());
    }

    //Set the last item's key = value
    valuesUpToPath.last()[pathComponents.last()] = QJsonValue::fromVariant(value);

    //Now merge all the items back into one
    QJsonObject result = valuesUpToPath.takeLast();

    while (valuesUpToPath.size() > 0) {
        QJsonObject parent = valuesUpToPath.takeLast();
        parent[pathComponents[valuesUpToPath.size()]] = result;
        result = parent;
    }

    m_root = result;
}

QVariant JSONManipulator::get(const QString &key, const QVariant &defaultValue) const {
    QVariant result = defaultValue;

    QStringList pathComponents = key.split('.');
    QJsonObject parentObject = m_root;

    while (pathComponents.size() > 0) {
        QString const &currentKey = pathComponents.takeFirst();

        if (parentObject.contains(currentKey)) {
            if (pathComponents.size() == 0) {
                result = parentObject.value(currentKey);
            } else {
                parentObject = parentObject.value(currentKey).toObject();
            }
        } else break;
    }

    return result;
}

bool JSONManipulator::has(const QString &key) const {
    QStringList paths = key.split('.');
    QJsonObject obj = m_root;

    while (paths.size() > 0) {
        const QString &currentKey = paths.takeFirst();

        if (obj.contains(currentKey)) {
            if (paths.size() == 0) {
                return true;
            } else {
                obj = obj.value(currentKey).toObject();
            }
        } else break;
    }

    return false;
}

std::string JSONManipulator::get_json() const {
    return QJsonDocument(m_root).toJson(QJsonDocument::Compact).toStdString();
}