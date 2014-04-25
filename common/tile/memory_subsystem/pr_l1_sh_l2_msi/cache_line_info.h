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
   { return _sharer_type_vector[tile]; }
   void setSharerType(tile_id_t tile, Type type)
   { _sharer_type_vector[tile] = type; }

   SInt32 getRemoteUtil(tile_id_t core_id) const
   { return _remote_util_vector[core_id]; }
   void setRemoteUtil(tile_id_t core_id, SInt32 val)
   { _remote_util_vector[core_id] = val; }
   void incrRemoteUtil(tile_id_t core_id)
   { _remote_util_vector[core_id]++; }

   UInt64 getLat(tile_id_t core_id) const
   { return _lat_vector[core_id]; }
   void setLat(tile_id_t core_id, UInt64 val)
   { _lat_vector[core_id] =  val; }

   bool getSharerTypeList(vector<Type>& sharer_type_vector);
   bool getRemoteUtilList(vector<SInt32>& remote_util_vector);
   bool getLatList(vector<UInt64>& lat_vector);

private:
   DirectoryEntry* _directory_entry;
   MemComponent::Type _caching_component;

   vector<Type> _sharer_type_vector;
   vector<SInt32> _remote_util_vector;
   vector<UInt64> _lat_vector;
};

}
