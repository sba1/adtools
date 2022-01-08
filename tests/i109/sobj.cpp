 #include "sobj.h"
    
const MetaObject Object::staticMetaObject {
    1234,
    'b'
};
    
MetaObject *Object::connectImpl(const Object *sender, void **signal, const MetaObject *senderMetaObject)
{
    return const_cast<MetaObject *>(senderMetaObject);
}
