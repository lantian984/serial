#ifndef JSON_H
#define JSON_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QByteArray>

class Json : public QJsonObject
{
private:
    QByteArray byteArray;
public:
    Json();


public:
    void setJsonByteArray(QByteArray byteArray);
    QByteArray getJsonByteArray();
    QString getJsonString();

    QString getValueFromJson(QStringList &ls);
};

#endif // JSON_H
