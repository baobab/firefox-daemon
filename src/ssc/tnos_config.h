#ifndef TNOS_CONFIG_H

#   define TNOS_CONFIG_H

    // use debugging
#   define TNMEM_DEBUG
#   define TNMEM_CORE_ON_ERROR

    // add some paranoia checking, 
    // TNList::remove() calls find on the node before doing delete to make
    // sure the node is in the list
#   define TNPARANOID

#   define PNGRD

#endif

