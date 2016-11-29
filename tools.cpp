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
    qDebug("fuck%d",inputByte.size());
    int j=0;
    for(int i=0;i<input.size();i++){
        j=0;
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
        inputBit.setBit(i*5+j++,a[i]&(1<<(4-j)));
    }
    qDebug() << "QBitArray bits :" << inputBit;
    qDebug("shit");
    QByteArray temp;
    temp.resize(inputBit.size()/8);
    for(int i=0;i<inputBit.count();i++){
        temp[i/8]=(temp.at(i/8)|(inputBit.testBit(i)?1:0)<<(i%8));
    }
    result = result.fromUtf8(temp);
    return result;
}
