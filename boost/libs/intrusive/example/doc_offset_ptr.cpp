/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//[doc_offset_ptr_0
#include <boost/intrusive/list.hpp>
#include <boost/interprocess/offset_ptr.hpp>

class shared_memory_data
{
   int data_id_;
   public:

   int get() const   {  return data_id_;  }
   void set(int id)  {  data_id_ = id;    }

   //Declare the hook with an offset_ptr from Boost.Interprocess
   //to make this class compatible with shared memory
   typedef boost::intrusive::list_member_hook
         < boost::intrusive::safe_link
         , boost::interprocess::offset_ptr<void> >  member_hook_t;
   member_hook_t list_hook_;
};
//]

//[doc_offset_ptr_1
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

//Definition of the shared memory friendly intrusive list
typedef boost::intrusive::list< shared_memory_data::member_hook_t::
   value_traits<shared_memory_data, &shared_memory_data::list_hook_> > shm_list_t;

int main()
{
   //Now create an intrusive list in shared memory:
   //nodes and the container itself must be created in shared memory
   const int MaxElem    = 100;
   const int ShmSize    = 50000;
   const char *ShmName  = "SharedMemoryName";

   using namespace boost::interprocess;

   //Erase all old shared memory 
   shared_memory_object::remove(ShmName);
   managed_shared_memory shm(create_only, ShmName, ShmSize);

   //Create all nodes in shared memory using a shared memory vector
   //See Boost.Interprocess documentation for more information on this
   typedef allocator< shared_memory_data
                    , managed_shared_memory::segment_manager> shm_allocator_t;
   typedef vector<shared_memory_data, shm_allocator_t> shm_vector_t;
   shm_allocator_t shm_alloc(shm.get_segment_manager());
   shm_vector_t *pshm_vect = shm.construct<shm_vector_t>(anonymous_instance)(shm_alloc);
   pshm_vect->resize(MaxElem);

   //Initialize all the nodes
   for(int i = 0; i < MaxElem; ++i){
      (*pshm_vect)[i].set(i);
   }

   //Now create the shared memory intrusive list
   shm_list_t *plist = shm.construct<shm_list_t>(anonymous_instance)();
   plist->insert(plist->end(), pshm_vect->begin(), pshm_vect->end());

   //Check all the inserted nodes
   int checker = 0;
   for( shm_list_t::const_iterator it = plist->begin(), itend(plist->end())
      ; it != itend
      ; ++it, ++checker){
      if(it->get() != checker){
         return false;
      }
   }

   //Now delete the list and after that, the nodes
   shm.destroy_ptr(plist);
   shm.destroy_ptr(pshm_vect);
   return 0;
}
//]
