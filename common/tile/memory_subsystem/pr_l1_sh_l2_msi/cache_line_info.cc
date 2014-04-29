#include "cache_line_info.h"
#include "log.h"

#define NUM_TILES 66

namespace PrL1ShL2MSI
{

CacheLineInfo* createCacheLineInfo(SInt32 cache_level)
{
   switch (cache_level)
   {
   case L1:
      //LOG_PRINT("***** case L1");
      return new PrL1CacheLineInfo();
   case L2:
      //LOG_PRINT("***** case L2");
      return new ShL2CacheLineInfo();
   default:
      LOG_PRINT_ERROR("Unrecognized Cache Level(%u)", cache_level);
      return (CacheLineInfo*) NULL;
   }
}

// ShL2 CacheLineInfo

ShL2CacheLineInfo::ShL2CacheLineInfo(IntPtr tag, DirectoryEntry* directory_entry)
   : CacheLineInfo(tag, CacheState::INVALID)
   , _directory_entry(directory_entry)
   , _caching_component(MemComponent::INVALID)
{
   _sharer_type_vector.resize(NUM_TILES);
   _remote_util_vector.resize(NUM_TILES);
   _lat_vector.resize(NUM_TILES);
   for(UInt32 i=0; i<NUM_TILES; i++)
   {
      _sharer_type_vector[i] = ShL2CacheLineInfo::PRIVATE_SHARER;
      _remote_util_vector[i] = 0;
      _lat_vector[i] = 0;
   }
   _is_lock_variable = false;
}

ShL2CacheLineInfo::~ShL2CacheLineInfo()
{}

void
ShL2CacheLineInfo::assign(CacheLineInfo* cache_line_info)
{
   LOG_PRINT("L2 assigning");
   CacheLineInfo::assign(cache_line_info);
   ShL2CacheLineInfo* L2_cache_line_info = dynamic_cast<ShL2CacheLineInfo*>(cache_line_info);
   _directory_entry = L2_cache_line_info->getDirectoryEntry();
   _caching_component = L2_cache_line_info->getCachingComponent();
   L2_cache_line_info->getSharerTypeList(_sharer_type_vector);
   L2_cache_line_info->getRemoteUtilList(_remote_util_vector);
   L2_cache_line_info->getLatList(_lat_vector);
  // _sharer_type_vector = L2_cache_line_info->getSharerTypeVector();
  // _remote_util_vector = L2_cache_line_info->getRemoteUtilVector();
  // _lat_vector = L2_cache_line_info->getLatVector();
   LOG_PRINT("end L2 assigning");
}

bool
ShL2CacheLineInfo::getSharerTypeList(vector<Type>& sharer_type_vector)
{
   for (SInt32 i = 0; i < NUM_TILES; i++)
      sharer_type_vector[i] = _sharer_type_vector[i];
      //sharer_type_vector.push_back((Type) _sharer_type_vector[i]);
   return true;
}

bool
ShL2CacheLineInfo::getRemoteUtilList(vector<UInt32>& remote_util_vector)
{
   for (UInt32 i = 0; i < NUM_TILES; i++)
      remote_util_vector[i] = _remote_util_vector[i];
      //remote_util_vector.push_back((UInt32) _remote_util_vector[i]);
   return true;
}

bool
ShL2CacheLineInfo::getLatList(vector<UInt64>& lat_vector)
{
   for (SInt32 i = 0; i < NUM_TILES; i++)
      lat_vector[i] = _lat_vector[i];
      //lat_vector.push_back((Type) _lat_vector[i]);
   return true;
}

}
