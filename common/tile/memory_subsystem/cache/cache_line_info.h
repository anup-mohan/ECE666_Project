#pragma once

#include "fixed_types.h"
#include "cache.h"
#include "cache_utils.h"
#include "caching_protocol_type.h"

class CacheLineInfo
{
// This can be extended to include other information
// for different cache coherence protocols and cache types
public:
   CacheLineInfo(IntPtr tag = ~0, CacheState::Type cstate = CacheState::INVALID, UInt32 P_util_ctr=0);
   virtual ~CacheLineInfo();

   static CacheLineInfo* create(CachingProtocolType caching_protocol_type, SInt32 cache_level);

   virtual void invalidate();
   virtual void assign(CacheLineInfo* cache_line_info);

   bool isValid() const                        
   { return (_tag != ((IntPtr) ~0)); }
   IntPtr getTag() const                        
   { return _tag; }
   CacheState::Type getCState() const           
   { return _cstate; }
   UInt32 get_P_util_ctr()
   { return _P_util_ctr; }

   void setTag(IntPtr tag)                     
   { _tag = tag; }
   void setCState(CacheState::Type cstate)      
   { _cstate = cstate; }
   void Incr_P_util()
   { _P_util_ctr++; }
   UInt32 timestamp[64];

protected:
   IntPtr _tag;
   CacheState::Type _cstate;
   UInt32 _P_util_ctr;//CKB edit
};
