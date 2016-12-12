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
    QString base16encode(const QString &input);
    QString caesarDecode(const QString &fuckyou,int n);
    QString baconDecodeAB1(const QString &input);
    QString baconDecodeAB2(const QString &input);
private:
    Tools();
    static Tools* p_Instance;
    QString const base32map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ23456789";
    QString const baconA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString const baconB = "ABCDEFGHIKLMNOPQRSTUWXYZ";
};

#endif // TOOLS_H
