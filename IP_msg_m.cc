//
// Generated file, do not edit! Created by nedtool 5.6 from IP_msg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "IP_msg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(IP_msg)

IP_msg::IP_msg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->version = 0;
    this->length = 20;
    this->tos = 0;
    this->size = 20;
    this->Id = 0;
    this->flags = 1;
    this->offset = 0;
    this->ttl = 2;
    this->protocol = 0;
    this->checksum = 0;
}

IP_msg::IP_msg(const IP_msg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

IP_msg::~IP_msg()
{
}

IP_msg& IP_msg::operator=(const IP_msg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void IP_msg::copy(const IP_msg& other)
{
    this->version = other.version;
    this->length = other.length;
    this->tos = other.tos;
    this->size = other.size;
    this->Id = other.Id;
    this->flags = other.flags;
    this->offset = other.offset;
    this->ttl = other.ttl;
    this->protocol = other.protocol;
    this->checksum = other.checksum;
    this->ip_src = other.ip_src;
    this->ip_dest = other.ip_dest;
}

void IP_msg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->version);
    doParsimPacking(b,this->length);
    doParsimPacking(b,this->tos);
    doParsimPacking(b,this->size);
    doParsimPacking(b,this->Id);
    doParsimPacking(b,this->flags);
    doParsimPacking(b,this->offset);
    doParsimPacking(b,this->ttl);
    doParsimPacking(b,this->protocol);
    doParsimPacking(b,this->checksum);
    doParsimPacking(b,this->ip_src);
    doParsimPacking(b,this->ip_dest);
}

void IP_msg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->version);
    doParsimUnpacking(b,this->length);
    doParsimUnpacking(b,this->tos);
    doParsimUnpacking(b,this->size);
    doParsimUnpacking(b,this->Id);
    doParsimUnpacking(b,this->flags);
    doParsimUnpacking(b,this->offset);
    doParsimUnpacking(b,this->ttl);
    doParsimUnpacking(b,this->protocol);
    doParsimUnpacking(b,this->checksum);
    doParsimUnpacking(b,this->ip_src);
    doParsimUnpacking(b,this->ip_dest);
}

int IP_msg::getVersion() const
{
    return this->version;
}

void IP_msg::setVersion(int version)
{
    this->version = version;
}

int IP_msg::getLength() const
{
    return this->length;
}

void IP_msg::setLength(int length)
{
    this->length = length;
}

int IP_msg::getTos() const
{
    return this->tos;
}

void IP_msg::setTos(int tos)
{
    this->tos = tos;
}

int IP_msg::getSize() const
{
    return this->size;
}

void IP_msg::setSize(int size)
{
    this->size = size;
}

int IP_msg::getId() const
{
    return this->Id;
}

void IP_msg::setId(int Id)
{
    this->Id = Id;
}

int IP_msg::getFlags() const
{
    return this->flags;
}

void IP_msg::setFlags(int flags)
{
    this->flags = flags;
}

int IP_msg::getOffset() const
{
    return this->offset;
}

void IP_msg::setOffset(int offset)
{
    this->offset = offset;
}

int IP_msg::getTtl() const
{
    return this->ttl;
}

void IP_msg::setTtl(int ttl)
{
    this->ttl = ttl;
}

int IP_msg::getProtocol() const
{
    return this->protocol;
}

void IP_msg::setProtocol(int protocol)
{
    this->protocol = protocol;
}

int IP_msg::getChecksum() const
{
    return this->checksum;
}

void IP_msg::setChecksum(int checksum)
{
    this->checksum = checksum;
}

const char * IP_msg::getIp_src() const
{
    return this->ip_src.c_str();
}

void IP_msg::setIp_src(const char * ip_src)
{
    this->ip_src = ip_src;
}

const char * IP_msg::getIp_dest() const
{
    return this->ip_dest.c_str();
}

void IP_msg::setIp_dest(const char * ip_dest)
{
    this->ip_dest = ip_dest;
}

class IP_msgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    IP_msgDescriptor();
    virtual ~IP_msgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(IP_msgDescriptor)

IP_msgDescriptor::IP_msgDescriptor() : omnetpp::cClassDescriptor("IP_msg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

IP_msgDescriptor::~IP_msgDescriptor()
{
    delete[] propertynames;
}

bool IP_msgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IP_msg *>(obj)!=nullptr;
}

const char **IP_msgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *IP_msgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int IP_msgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 12+basedesc->getFieldCount() : 12;
}

unsigned int IP_msgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<12) ? fieldTypeFlags[field] : 0;
}

const char *IP_msgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "version",
        "length",
        "tos",
        "size",
        "Id",
        "flags",
        "offset",
        "ttl",
        "protocol",
        "checksum",
        "ip_src",
        "ip_dest",
    };
    return (field>=0 && field<12) ? fieldNames[field] : nullptr;
}

int IP_msgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "length")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "tos")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+3;
    if (fieldName[0]=='I' && strcmp(fieldName, "Id")==0) return base+4;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+5;
    if (fieldName[0]=='o' && strcmp(fieldName, "offset")==0) return base+6;
    if (fieldName[0]=='t' && strcmp(fieldName, "ttl")==0) return base+7;
    if (fieldName[0]=='p' && strcmp(fieldName, "protocol")==0) return base+8;
    if (fieldName[0]=='c' && strcmp(fieldName, "checksum")==0) return base+9;
    if (fieldName[0]=='i' && strcmp(fieldName, "ip_src")==0) return base+10;
    if (fieldName[0]=='i' && strcmp(fieldName, "ip_dest")==0) return base+11;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *IP_msgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "string",
        "string",
    };
    return (field>=0 && field<12) ? fieldTypeStrings[field] : nullptr;
}

const char **IP_msgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *IP_msgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int IP_msgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    IP_msg *pp = (IP_msg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *IP_msgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    IP_msg *pp = (IP_msg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IP_msgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    IP_msg *pp = (IP_msg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getVersion());
        case 1: return long2string(pp->getLength());
        case 2: return long2string(pp->getTos());
        case 3: return long2string(pp->getSize());
        case 4: return long2string(pp->getId());
        case 5: return long2string(pp->getFlags());
        case 6: return long2string(pp->getOffset());
        case 7: return long2string(pp->getTtl());
        case 8: return long2string(pp->getProtocol());
        case 9: return long2string(pp->getChecksum());
        case 10: return oppstring2string(pp->getIp_src());
        case 11: return oppstring2string(pp->getIp_dest());
        default: return "";
    }
}

bool IP_msgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    IP_msg *pp = (IP_msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setVersion(string2long(value)); return true;
        case 1: pp->setLength(string2long(value)); return true;
        case 2: pp->setTos(string2long(value)); return true;
        case 3: pp->setSize(string2long(value)); return true;
        case 4: pp->setId(string2long(value)); return true;
        case 5: pp->setFlags(string2long(value)); return true;
        case 6: pp->setOffset(string2long(value)); return true;
        case 7: pp->setTtl(string2long(value)); return true;
        case 8: pp->setProtocol(string2long(value)); return true;
        case 9: pp->setChecksum(string2long(value)); return true;
        case 10: pp->setIp_src((value)); return true;
        case 11: pp->setIp_dest((value)); return true;
        default: return false;
    }
}

const char *IP_msgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *IP_msgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    IP_msg *pp = (IP_msg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


