#include "xlsxdocument.h"

#include <QCoreApplication>
#include <QFile>
#include <QHash>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

bool LoadJsonFile(QString path, QJsonDocument& jsonDoc)
{
    QFile loadFile(path);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open json file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    jsonDoc = QJsonDocument::fromJson(saveData);
    if (jsonDoc.isNull()) {
        qWarning("Json file is wrong.");
        return false;
    }

    return true;
}

bool LoadLocale(QString path, QHash<QString, QString>& map)
{
    QJsonDocument jsonDoc;
    if (!LoadJsonFile(path, jsonDoc)) {
        return false;
    }

    QJsonObject jsonObject = jsonDoc.object();
    for (auto i = jsonObject.begin(); i != jsonObject.end(); ++i) {
        map.insert(i.value().toString(), i.key());
    }
    return true;
}

struct sheet {
    int row;
    QString name;
    sheet(QString nm = "", int r = 2)
        : name(nm)
        , row(r)
    {
    }
};

enum sheetTitle {
    Type = 1,
    Name = 2,
    Time = 3
};

void WriteXlsx(QString path, const QJsonArray& array, QHash<QString, QString>& localeMap)
{
    QHash<QString, QString> typeMap;
    typeMap.insert(QStringLiteral("武器"), QStringLiteral("Weapon"));
    typeMap.insert(QStringLiteral("角色"), QStringLiteral("Character"));

    QHash<QString, sheet> sheetMap;
    sheetMap.insert("100", sheet("Beginners' Wish"));
    sheetMap.insert("200", sheet("Standard"));
    sheetMap.insert("301", sheet("Character Event"));
    sheetMap.insert("302", sheet("Weapon Event"));

    QXlsx::Document doc(path);

    for (const auto& item : array) {
        auto time = item[QStringLiteral("time")].toString();
        auto name = item[QStringLiteral("name")].toString();
        auto uigf_gacha_type = item[QStringLiteral("uigf_gacha_type")].toString();
        auto item_type = item[QStringLiteral("item_type")].toString();

        doc.selectSheet(sheetMap[uigf_gacha_type].name);
        doc.write(sheetMap[uigf_gacha_type].row, Type, typeMap[item_type]);
        doc.write(sheetMap[uigf_gacha_type].row, Name, localeMap[name]);
        doc.write(sheetMap[uigf_gacha_type].row, Time, time);
        ++sheetMap[uigf_gacha_type].row;
    }
    doc.save();
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    if (argc != 4) {
        qWarning() << "input args wrong with number: " << argc;
        return -1;
    }

    QJsonDocument jsonDoc;
    if (!LoadJsonFile(argv[1], jsonDoc)) {
        qWarning("history json file is wrong.");
        return -1;
    }

    QHash<QString, QString> localeMap;
    if (!LoadLocale(argv[2], localeMap)) {
        qWarning("locale json file is wrong.");
        return -1;
    }

    WriteXlsx(argv[3], jsonDoc[QStringLiteral("list")].toArray(), localeMap);

    return 0;
}