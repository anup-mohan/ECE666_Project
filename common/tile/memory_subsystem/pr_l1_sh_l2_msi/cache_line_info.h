#pragma once

#include "../cache/cache_line_info.h"
#include "cache_level.h"
#include "directory_entry.h"

namespace PrL1ShL2MSI
{

CacheLineInfo* createCacheLineInfo(SInt32 cache_level);

typedef CacheLineInfo PrL1CacheLineInfo;

class ShL2CacheLineInfo : public CacheLineInfo
{
public:
   enum Type
   {
      PRIVATE_SHARER = 0,
      REMOTE_SHARER
   };

   ShL2CacheLineInfo(IntPtr tag = ~0, DirectoryEntry* directory_entry = NULL);
   ~ShL2CacheLineInfo();

   void assign(CacheLineInfo* cache_line_info);
   
   DirectoryEntry* getDirectoryEntry() const
   { return _directory_entry; }
   void setDirectoryEntry(DirectoryEntry* entry)
   { _directory_entry = entry; }
   MemComponent::Type getCachingComponent() const
   { return _caching_component; }
   void setCachingComponent(MemComponent::Type caching_component)
   { _caching_component = caching_component; }

   Type getSharerType(tile_id_t tile) const
   { return _sharer_type[tile]; }
   void setSharerType(tile_id_t tile, Type type)
   { _sharer_type[tile] = type; }

   SInt32 getRemoteUtil(tile_id_t core_id) const
   { return _remote_util[core_id]; }
   void setRemoteUtil(tile_id_t core_id, SInt32 val)
   { _remote_util[core_id] = val; }
   void incrRemoteUtil(tile_id_t core_id)
   { _remote_util[core_id]++; }

private:
   DirectoryEntry* _directory_entry;
   MemComponent::Type _caching_component;

   vector<Type> _sharer_type;
   vector<SInt32> _remote_util;
   vector<UInt64> _lat;
};

}
