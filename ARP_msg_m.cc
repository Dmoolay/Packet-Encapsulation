//
// Generated file, do not edit! Created by nedtool 5.6 from ARP_msg.msg.
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
#include "ARP_msg_m.h"

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

Register_Class(ARP_msg)

ARP_msg::ARP_msg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->H_type = 1;
    this->P_type = 1;
    this->H_add_len = 6;
    this->P_add_len = 4;
    this->opcode = 0;
}

ARP_msg::ARP_msg(const ARP_msg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

ARP_msg::~ARP_msg()
{
}

ARP_msg& ARP_msg::operator=(const ARP_msg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void ARP_msg::copy(const ARP_msg& other)
{
    this->H_type = other.H_type;
    this->P_type = other.P_type;
    this->H_add_len = other.H_add_len;
    this->P_add_len = other.P_add_len;
    this->opcode = other.opcode;
    this->mac_src = other.mac_src;
    this->ip_src = other.ip_src;
    this->mac_dest = other.mac_dest;
    this->ip_dest = other.ip_dest;
}

void ARP_msg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->H_type);
    doParsimPacking(b,this->P_type);
    doParsimPacking(b,this->H_add_len);
    doParsimPacking(b,this->P_add_len);
    doParsimPacking(b,this->opcode);
    doParsimPacking(b,this->mac_src);
    doParsimPacking(b,this->ip_src);
    doParsimPacking(b,this->mac_dest);
    doParsimPacking(b,this->ip_dest);
}

void ARP_msg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->H_type);
    doParsimUnpacking(b,this->P_type);
    doParsimUnpacking(b,this->H_add_len);
    doParsimUnpacking(b,this->P_add_len);
    doParsimUnpacking(b,this->opcode);
    doParsimUnpacking(b,this->mac_src);
    doParsimUnpacking(b,this->ip_src);
    doParsimUnpacking(b,this->mac_dest);
    doParsimUnpacking(b,this->ip_dest);
}

int ARP_msg::getH_type() const
{
    return this->H_type;
}

void ARP_msg::setH_type(int H_type)
{
    this->H_type = H_type;
}

int ARP_msg::getP_type() const
{
    return this->P_type;
}

void ARP_msg::setP_type(int P_type)
{
    this->P_type = P_type;
}

int ARP_msg::getH_add_len() const
{
    return this->H_add_len;
}

void ARP_msg::setH_add_len(int H_add_len)
{
    this->H_add_len = H_add_len;
}

int ARP_msg::getP_add_len() const
{
    return this->P_add_len;
}

void ARP_msg::setP_add_len(int P_add_len)
{
    this->P_add_len = P_add_len;
}

int ARP_msg::getOpcode() const
{
    return this->opcode;
}

void ARP_msg::setOpcode(int opcode)
{
    this->opcode = opcode;
}

const char * ARP_msg::getMac_src() const
{
    return this->mac_src.c_str();
}

void ARP_msg::setMac_src(const char * mac_src)
{
    this->mac_src = mac_src;
}

const char * ARP_msg::getIp_src() const
{
    return this->ip_src.c_str();
}

void ARP_msg::setIp_src(const char * ip_src)
{
    this->ip_src = ip_src;
}

const char * ARP_msg::getMac_dest() const
{
    return this->mac_dest.c_str();
}

void ARP_msg::setMac_dest(const char * mac_dest)
{
    this->mac_dest = mac_dest;
}

const char * ARP_msg::getIp_dest() const
{
    return this->ip_dest.c_str();
}

void ARP_msg::setIp_dest(const char * ip_dest)
{
    this->ip_dest = ip_dest;
}

class ARP_msgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ARP_msgDescriptor();
    virtual ~ARP_msgDescriptor();

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

Register_ClassDescriptor(ARP_msgDescriptor)

ARP_msgDescriptor::ARP_msgDescriptor() : omnetpp::cClassDescriptor("ARP_msg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

ARP_msgDescriptor::~ARP_msgDescriptor()
{
    delete[] propertynames;
}

bool ARP_msgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ARP_msg *>(obj)!=nullptr;
}

const char **ARP_msgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ARP_msgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ARP_msgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int ARP_msgDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *ARP_msgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "H_type",
        "P_type",
        "H_add_len",
        "P_add_len",
        "opcode",
        "mac_src",
        "ip_src",
        "mac_dest",
        "ip_dest",
    };
    return (field>=0 && field<9) ? fieldNames[field] : nullptr;
}

int ARP_msgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='H' && strcmp(fieldName, "H_type")==0) return base+0;
    if (fieldName[0]=='P' && strcmp(fieldName, "P_type")==0) return base+1;
    if (fieldName[0]=='H' && strcmp(fieldName, "H_add_len")==0) return base+2;
    if (fieldName[0]=='P' && strcmp(fieldName, "P_add_len")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "opcode")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "mac_src")==0) return base+5;
    if (fieldName[0]=='i' && strcmp(fieldName, "ip_src")==0) return base+6;
    if (fieldName[0]=='m' && strcmp(fieldName, "mac_dest")==0) return base+7;
    if (fieldName[0]=='i' && strcmp(fieldName, "ip_dest")==0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ARP_msgDescriptor::getFieldTypeString(int field) const
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
        "string",
        "string",
        "string",
        "string",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : nullptr;
}

const char **ARP_msgDescriptor::getFieldPropertyNames(int field) const
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

const char *ARP_msgDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ARP_msgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ARP_msg *pp = (ARP_msg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ARP_msgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ARP_msg *pp = (ARP_msg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ARP_msgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ARP_msg *pp = (ARP_msg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getH_type());
        case 1: return long2string(pp->getP_type());
        case 2: return long2string(pp->getH_add_len());
        case 3: return long2string(pp->getP_add_len());
        case 4: return long2string(pp->getOpcode());
        case 5: return oppstring2string(pp->getMac_src());
        case 6: return oppstring2string(pp->getIp_src());
        case 7: return oppstring2string(pp->getMac_dest());
        case 8: return oppstring2string(pp->getIp_dest());
        default: return "";
    }
}

bool ARP_msgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ARP_msg *pp = (ARP_msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setH_type(string2long(value)); return true;
        case 1: pp->setP_type(string2long(value)); return true;
        case 2: pp->setH_add_len(string2long(value)); return true;
        case 3: pp->setP_add_len(string2long(value)); return true;
        case 4: pp->setOpcode(string2long(value)); return true;
        case 5: pp->setMac_src((value)); return true;
        case 6: pp->setIp_src((value)); return true;
        case 7: pp->setMac_dest((value)); return true;
        case 8: pp->setIp_dest((value)); return true;
        default: return false;
    }
}

const char *ARP_msgDescriptor::getFieldStructName(int field) const
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

void *ARP_msgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ARP_msg *pp = (ARP_msg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


