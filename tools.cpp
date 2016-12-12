#include "tools.h"
#include <QDebug>
Tools::Tools()
{

}
Tools* Tools::p_Instance = NULL;
Tools* Tools::GetInstance(){
    if(Tools::p_Instance==nullptr){
        p_Instance = new Tools();
    }
    return p_Instance;
}
QString Tools::base32encode(const QString &input){
    QByteArray inputByte(input.toUtf8());
    QBitArray inputBit(inputByte.size()*8);
    for(int i=0;i<inputByte.size();i++){
        for(int j=0;j<8;j++){
            inputBit.setBit(i*8+7-j,inputByte.at(i)&(1<<j));
        }
    }
    QString result;
    int temp=0,j=0;
    for(int i=0;i<inputBit.count();){
        j=4;
        if(i<inputBit.count()&&inputBit.testBit(i++))
            temp+=(1<<j);
        j--;
        if(i<inputBit.count()&&inputBit.testBit(i++))
            temp+=(1<<j);
        j--;
        if(i<inputBit.count()&&inputBit.testBit(i++))
            temp+=(1<<j);
        j--;
        if(i<inputBit.count()&&inputBit.testBit(i++))
            temp+=(1<<j);
        j--;
        if(i<inputBit.count()&&inputBit.testBit(i++))
            temp+=(1<<j);
        result.append(base32map.at(temp));
        temp=0;
    }
    return result;
}
QString Tools::base32decode(const QString &input){
    QByteArray inputByte(input.toLatin1());
    QBitArray inputBit(inputByte.size()*5+5);
    QVector<int> a;
    a.resize(inputByte.size());
    for(int i=0;i<inputByte.size();i++){
        a[i]=base32map.indexOf(input.at(i));
    }
    QString result;
    int j=0;
    for(int i=0;i<input.size();i++){
        j=0;
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
    }
    QByteArray temp("");
    temp.resize(inputBit.size()/8+1);
    temp.fill('\x00');
    for(int i=0;i<inputBit.count();i++){
        temp[i/8]=(temp.at(i/8)|(inputBit.testBit(i)?0x80:0)>>(i%8));
    }
    result = result.fromUtf8(temp);
    return result;
}
QString Tools::caesarDecode(const QString &fuckyou, int n){
    QString result;
    QString input = QString(fuckyou);
    for(QString::iterator it = input.begin();it!=input.end();it++){
        if(it->isLower()){
            QChar temp =QChar::fromLatin1(it->toLatin1()+n);
            if(temp.isLower()){
                result.append(temp);
            }else{
                result.append(QChar::fromLatin1(temp.toLatin1()-26));
            }
        }else if(it->isUpper()){
            QChar temp =QChar::fromLatin1(it->toLatin1()+n);
            if(temp.isUpper()){
                result.append(temp);
            }else{
                result.append(QChar::fromLatin1(temp.toLatin1()-26));
            }
        }
        else{
            result.append(QChar(it->unicode()));
        }
    }
    return result;
}
QString Tools::baconDecodeAB1(const QString &input){
    QString result;
    QString temp = input;
    temp = temp.replace(QRegExp("[Aa]"),"0");
    temp = temp.replace(QRegExp("[Bb]"),"1");
    int i=0,s=0;
    for(int n=0;n<temp.length();n++){
        if(i>=5){
            result.append(baconA.at(s));
            i=0;s=0;
        }
        if(temp.at(n)=="1")
        s+=16>>i;
        i++;
    }
    if(i==5){
        result.append(baconA.at(s));
    }
    return result;
}
QString Tools::baconDecodeAB2(const QString &input){
    QString result;
    QString temp = input;
    temp = temp.replace(QRegExp("[Aa]"),"0");
    temp = temp.replace(QRegExp("[Bb]"),"1");
    int i=0,s=0;
    for(int n=0;n<temp.length();n++){
        if(i>=5){
            result.append(baconB.at(s));
            if(s==8)result.append("/J");
            else if(s==19)result.append("/V");
            i=0;s=0;
        }
        if(temp.at(n)=="1")
        s+=16>>i;
        i++;
    }
    if(i==5){
        result.append(baconB.at(s));
        if(s==8)result.append("/J");
        else if(s==19)result.append("/V");
    }
    return result;
}
