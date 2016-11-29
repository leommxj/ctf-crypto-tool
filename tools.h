#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QBitArray>



class Tools
{
public:
    static Tools* GetInstance();
    QString base32encode(const QString &input);
    QString base32decode(const QString &input);
private:
    Tools();
    static Tools* p_Instance;
    QString const base32map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ23456789";
};

#endif // TOOLS_H
