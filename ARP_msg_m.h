//
// Generated file, do not edit! Created by nedtool 5.6 from ARP_msg.msg.
//

#ifndef __ARP_MSG_M_H
#define __ARP_MSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>ARP_msg.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * message ARP_msg extends cPacket
 * {
 *     int H_type = 1;
 *     int P_type = 1;
 *     int H_add_len = 6;
 *     int P_add_len = 4;
 *     int opcode;
 *     string mac_src;
 *     string ip_src;
 *     string mac_dest;
 *     string ip_dest;
 * }
 * </pre>
 */
class ARP_msg : public ::omnetpp::cPacket
{
  protected:
    int H_type;
    int P_type;
    int H_add_len;
    int P_add_len;
    int opcode;
    ::omnetpp::opp_string mac_src;
    ::omnetpp::opp_string ip_src;
    ::omnetpp::opp_string mac_dest;
    ::omnetpp::opp_string ip_dest;

  private:
    void copy(const ARP_msg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ARP_msg&);

  public:
    ARP_msg(const char *name=nullptr, short kind=0);
    ARP_msg(const ARP_msg& other);
    virtual ~ARP_msg();
    ARP_msg& operator=(const ARP_msg& other);
    virtual ARP_msg *dup() const override {return new ARP_msg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getH_type() const;
    virtual void setH_type(int H_type);
    virtual int getP_type() const;
    virtual void setP_type(int P_type);
    virtual int getH_add_len() const;
    virtual void setH_add_len(int H_add_len);
    virtual int getP_add_len() const;
    virtual void setP_add_len(int P_add_len);
    virtual int getOpcode() const;
    virtual void setOpcode(int opcode);
    virtual const char * getMac_src() const;
    virtual void setMac_src(const char * mac_src);
    virtual const char * getIp_src() const;
    virtual void setIp_src(const char * ip_src);
    virtual const char * getMac_dest() const;
    virtual void setMac_dest(const char * mac_dest);
    virtual const char * getIp_dest() const;
    virtual void setIp_dest(const char * ip_dest);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ARP_msg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ARP_msg& obj) {obj.parsimUnpack(b);}


#endif // ifndef __ARP_MSG_M_H
