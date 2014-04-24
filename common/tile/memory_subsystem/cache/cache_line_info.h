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
   CacheLineInfo(IntPtr tag = ~0, CacheState::Type cstate = CacheState::INVALID, SInt32 pvt_util = 0, UInt64 lat = 0);
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

   void setTag(IntPtr tag)                     
   { _tag = tag; }
   void setCState(CacheState::Type cstate)      
   { _cstate = cstate; }

   SInt32 getPvtUtil() const
   { return _pvt_util; }
   void setPvtUtil(SInt32 val)
   { _pvt_util = val; }
   UInt64 getLat() const
   { return _lat; }
   void setLat(UInt64 timestamp)
   { _lat = timestamp; }

   void incrPvtUtil()
   { _pvt_util++; }

protected:
   IntPtr _tag;
   CacheState::Type _cstate;
   SInt32 _pvt_util;	// private utilization counter
   UInt64 _lat;		// last access timestamp
};
