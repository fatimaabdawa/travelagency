#ifndef ARDUINO_H
#define ARDUINO_H
#include<QtSerialPort/QtSerialPort>
#include<QtSerialPort/QSerialPortInfo>


class arduino
{
public:
    arduino();
    int connect_arduino();//connect pc to arduino
    int close_arduino();//close cnx
    int write_to_arduino(QByteArray);//send data to arduino
    QByteArray read_from_arduino();//receive data from arduino
    QSerialPort* getserial();//accessor
    QString getarduino_port_name();
 private:
    QSerialPort * serial;
    static const quint16 arduino_uno_vendor_id=9025;
     static const quint16 arduino_uno_producy_id=67;
     QString arduino_port_name;
     bool arduino_is_available;
     QByteArray data;


};

#endif // ARDUINO_H
