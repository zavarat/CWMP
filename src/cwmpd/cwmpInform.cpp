#include "cwmpCtx.h"
#include "cwmpInform.h"

Inform::Inform(const QDomNode &informNode, const ClientID &clientID) {
    // Just for initialization time we create an instance of ClientID
    _clientID = new ClientID(clientID);
    qDebug("%s, %d", __FUNCTION__, __LINE__);
    qDebug("%s, %d: old=%s, new=%s", __FUNCTION__, __LINE__,
            clientID.soapHdrIdToByteArray().constData(), _clientID->soapHdrIdToByteArray().constData());
    qDebug("%s, %d", __FUNCTION__, __LINE__);
    QDomNode node = informNode.firstChild();
    QByteArray name;
    while(!node.isNull()) {
        name = node.nodeName().toLatin1();
        QString nodeName = node.nodeName();
        qDebug("Name is <%s>", name.constData());

        if(QString("DeviceId") == nodeName) {
            parseDeviceId(node);
        } else if(QString("Event") == nodeName) {
        } else if(QString("MaxEnvelopes") == nodeName) {
        }

        node = node.nextSibling();
    }
}

Inform::~Inform() {
}

void Inform::parseDeviceId(const QDomNode &deviceIdNode) {
    QDomNode node = deviceIdNode.firstChild();
    QByteArray name;
    ClientID clientID(*_clientID);
    QDomElement element;
    while(!node.isNull()) {
        name = node.nodeName().toLatin1();
        element = node.toElement();
        if(QString("Manufacturer") == node.nodeName()) {
            clientID.setManufacturer(element.text());
        } else if(QString("OUI") == node.nodeName()) {
            clientID.setOui(element.text());
        } else if(QString("ProductClass") == node.nodeName()) {
            clientID.setProductClass(element.text());
        } else if(QString("SerialNumber") == node.nodeName()) {
            clientID.setSerialNo(element.text());
        }

        node = node.nextSibling();
    }

    // Now check if it's ongoing CWMP session. If not, create context for it.
    CWMPCtx::instance().addSession(clientID);

    // Now removing temporary init-time ClientID and replacing _clientID
    // pointer with the one from CWMPCtx
    delete _clientID;
    _clientID = CWMPCtx::instance().clientID(clientID);
}

