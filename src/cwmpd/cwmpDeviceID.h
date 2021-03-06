#ifndef CWMPDEVICEID_H
#define CWMPDEVICEID_H

#include <QtDBus/QDBusArgument>
#include <QString>

class CWMPDeviceID
{
public:
    CWMPDeviceID();
    ~CWMPDeviceID();

    const QString &manufacturer() const { return _manufacturer; }
    void setManufacturer(QString manufacturer) { _manufacturer = manufacturer; }

    const QString &oui() const { return _oui; }
    void setOui(QString oui) { _oui = oui; }

    const QString &productClass() const { return _productClass; }
    void setProductClass(QString productClass) { _productClass = productClass; }

    const QString serialNumber() const { return _serialNumber; }
    void setSerialNumber(QString serialNumber) { _serialNumber = serialNumber; }

private:
    QString _manufacturer;
    QString _oui;
    QString _productClass;
    QString _serialNumber;
};

QDBusArgument &operator <<(QDBusArgument &, const CWMPDeviceID &);
const QDBusArgument &operator >>(const QDBusArgument &, CWMPDeviceID &);


#endif // CWMPDEVICEID_H
