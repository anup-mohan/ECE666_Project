#pragma once

#include "mem_component.h"
#include "fixed_types.h"
#include "../shmem_msg.h"

namespace PrL1ShL2MSI
{

class ShmemMsg : public ::ShmemMsg
{
public:
   enum Type
   {
      INVALID_MSG_TYPE = 0,
      MIN_MSG_TYPE,
      EX_REQ = MIN_MSG_TYPE,
      SH_REQ,
      INV_REQ,
      FLUSH_REQ,
      WB_REQ,
      EX_REP,
      SH_REP,
      UPGRADE_REP,
      INV_REP,
      FLUSH_REP,
      WB_REP,
      WORD_XFER_REP,
      EMPTY_REP,
      // Dram requests
      DRAM_FETCH_REQ,
      DRAM_STORE_REQ,
      DRAM_FETCH_REP,
      // Nullify req
      NULLIFY_REQ,
      MAX_MSG_TYPE = NULLIFY_REQ,
      NUM_MSG_TYPES = MAX_MSG_TYPE - MIN_MSG_TYPE + 1
   }; 

   ShmemMsg();
   ShmemMsg(Type msg_type
            , MemComponent::Type sender_mem_component
            , MemComponent::Type receiver_mem_component
            , tile_id_t requester
            , bool reply_expected
            , IntPtr address
            , bool modeled
            );
   ShmemMsg(Type msg_type
            , MemComponent::Type sender_mem_component
            , MemComponent::Type receiver_mem_component
            , tile_id_t requester
            , bool reply_expected
            , IntPtr address
            , Byte* data_buf
            , UInt32 data_length
            , bool modeled
            );
   ShmemMsg(Type msg_type
            , MemComponent::Type sender_mem_component
            , MemComponent::Type receiver_mem_component
            , tile_id_t requester
            , bool reply_expected
            , IntPtr address
            , bool modeled
            , UInt64 least_lat
            );
   ShmemMsg(Type msg_type
            , Core::lock_signal_t lock_signal
            , MemComponent::Type sender_mem_component
            , MemComponent::Type receiver_mem_component
            , tile_id_t requester
            , bool reply_expected
            , IntPtr address
            , UInt32 offset
            , Byte* data_buf
            , UInt32 data_length
            , bool modeled
            , UInt64 least_lat
            );
   ShmemMsg(Type msg_type
            , MemComponent::Type sender_mem_component
            , MemComponent::Type receiver_mem_component
            , tile_id_t requester
            , bool reply_expected
            , IntPtr address
            , bool modeled
            , UInt32 pvt_util
            );
   ShmemMsg(Type msg_type
            , MemComponent::Type sender_mem_component
            , MemComponent::Type receiver_mem_component
            , tile_id_t requester
            , bool reply_expected
            , IntPtr address
            , Byte* data_buf
            , UInt32 data_length
            , bool modeled
            , UInt32 pvt_util
            );
   ShmemMsg(const ShmemMsg* shmem_msg);
   ~ShmemMsg();

   void clone(const ShmemMsg* shmem_msg);
   static ShmemMsg* getShmemMsg(Byte* msg_buf);
   Byte* makeMsgBuf();
   UInt32 getMsgLen();

   // Modeled Parameters
   UInt32 getModeledLength();

   Type getType() const                               { return _msg_type; }
   MemComponent::Type getSenderMemComponent() const   { return _sender_mem_component; }
   MemComponent::Type getReceiverMemComponent() const { return _receiver_mem_component; }
   tile_id_t getRequester() const                     { return _requester; }
   bool isReplyExpected() const                       { return _reply_expected; }
   IntPtr getAddress() const                          { return _address; }
   UInt32 getOffset() const                           { return _offset; }
   Byte* getDataBuf() const                           { return _data_buf; }
   UInt32 getDataLength() const                       { return _data_length; }
   bool isModeled() const                             { return _modeled; }
   UInt64 getLeastLat() const                         { return _least_lat; }
   UInt32 getPvtUtil() const                          { return _pvt_util; }
   Core::lock_signal_t getLockSignal() const          { return _lock_signal; }

   void setMsgType(Type msg_type)                     { _msg_type = msg_type; }
   void setDataBuf(Byte* data_buf)                    { _data_buf = data_buf; }

   static string getName(Type type);

private:   
   Type _msg_type;
   Core::lock_signal_t _lock_signal;
   MemComponent::Type _sender_mem_component;
   MemComponent::Type _receiver_mem_component;
   tile_id_t _requester;
   bool _reply_expected;
   IntPtr _address;
   UInt32 _offset;
   Byte* _data_buf;
   UInt32 _data_length;
   bool _modeled;
   UInt32 _pvt_util;
   UInt64 _least_lat;
   
   static const UInt32 _num_msg_type_bits = 4;
};

}
