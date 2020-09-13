#include "json.h"

Json::Json():QJsonObject ()
{

}

void Json::setJsonByteArray(QByteArray byteArray)
{
    this->byteArray = byteArray;
}

QByteArray Json::getJsonByteArray()
{
    if (this->isEmpty()) {
            return "";
    }
    QJsonDocument document;
    document.setObject(*this);
    return document.toJson(QJsonDocument::Compact);
}

QString Json::getJsonString()
{
    if (this->isEmpty()) {
            return "";
    }
    QJsonDocument document;
    document.setObject(*this);
    QString str(document.toJson(QJsonDocument::Compact));
    return str;
}

QString Json::getValueFromJson(QStringList &ls)
{
    if(ls.isEmpty()){
         return "";
    }
    QString value;
    QJsonParseError jsonError;
    //qDebug() << "json" << byteArray;
    //获取json文档对象
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);

    //校验是否转换正确
    if (!doucment.isNull() && jsonError.error == QJsonParseError::NoError) {

        //获取json对象
        QJsonObject jsonObj = doucment.object();
        //临时对象，用于存储每次遍历后的结果
        QJsonObject obj;

        //判断第一个是不是最后一个节点
        if (jsonObj.contains(ls[0])) {
            if (jsonObj[ls[0]].isObject()) {
                obj = jsonObj;
            }
            else {
                //如果只有一个节点直接返回
                return jsonObj.value(ls[0]).toString();
            }
        }

        //遍历获取节点
        foreach (auto var,ls)
        {
            if (obj[var].isObject()) {
                obj = obj[var].toObject();
            }
            //获取值
            value = obj.value(var).toString();
        }
    }
   return value;
}
