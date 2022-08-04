#
/*
*/

/*
 * Structure of the coremap and swapmap
 * arrays. Consists of non-zero count
 * and base address of that many
 * contiguous units.
 * (The coremap unit is 64 bytes,
 * the swapmap unit is 512 bytes)
 * The addresses are increasing and
 * the list is terminated with the
 * first zero count.
*/
struct map
{
    char *m_size;
    char *m_addr;
}
/* ---------------------------------------- */

/*
 * Allocate size units from the given
 * map. Return the base of the allocated
 * space.
 * Algorithm is first fit.
*/
malloc(mp, size)
struct map *mp;
{
    register int a;
    register struct map *bp;

    /* remember that there is a sentinel node
     * in the list with size zero, so the second
     * argument of the for loop will be evaluted
     * to NULL when the sentinel node is reached
     * causing the for loop to quit out.
    */ 
    for (bp = mp; bp->m_size > 0; bp++) {
        if (bp->m_size >= size) {
            a = bp->m_addr;
            bp->m_addr =+ size;
            /* notice that the below statement will
             * never be evaluated to a value less
             * than zero (ie. only checks to see if
             * the block was a perfect fit).
            */
            if ((bp->m_size =- size) == 0)
                /* the below code basically iterates
                 * through the list, "shifting" each of
                 * the elements backwards until we hit
                 * the sentinel node.
                */
                do {
                    bp++;
                    (bp-1)->m_addr = bp->m_addr;
                } while ((bp-1)->m_size = bp->m_size);
            return (a);
        }
    }
    return (0);
}
/* ------------------------------------------- */

/*
 * Free the previously allocated space aa
 * of size units into the specified map.
 * Sort aa into map and combine on one or both ends
 * if possible.
*/ 
mfree(mp, size, aa)
struct map *mp;
{
    register struct map *bp;
    register int t;
    register int a;

    a = aa;
    /* Keep iterating through the list as long as the address
     * of the current element is smaller than the address
     * we are trying to return and we have not yet hit the
     * sentinel node.
    */  
    for (bp = mp; bp->m_addr <= a && bp->m_size != 0; bp++)
        ;
    
    /* We have now located the element in front of which we
     * should insert back the freed space. First check to see
     * if we are trying to insert at the beginning of the list.
     * Control moves to else case if we are.
    */
   if (bp > mp) {
    // Does previous element abut the space we are trying to add?
        if ((bp-1)->m_addr+(bp-1)->m_size == a) {
            (bp-1)->m_size =+ size;
            /* Does inserting the freed space abut the next element?
             * If execution continues into here this means we are reducing
             * the list in size by one.
            */ 
            if (a+size == bp->m_addr) {
                (bp-1)->m_size  =+ bp->m_size;
                // shift all elements backwards due to amalgamation
                while (bp->m_size > 0) {
                    bp++;
                    (bp-1)->m_addr = bp->m_addr;
                    (bp-1)->m_size = bp->m_size;
                }
            }
        }
   } else {
        /* Newly freed space cannot be amalgamated with previous element
         * but can it be amalgamated with the next element?
        */
        if (a+size == bp->m_addr && bp->m_size > 0) {
            bp->m_addr =- size;
            bp->m_size =+ size;
            /* For some reason *now* we ensure we are not returning
             * a non-zero space, and if so then insert the new element
             * and shift all the elements down one.
            */
        } else if (size) do {
            // save the address of the old base pointer of the list
            t = bp->m_addr;
            // point base pointer to address of newly freed space
            bp->m_addr = a;
            // assign a to old base pointer address
            a = t;
            // save the size of the old base pointer list element
            t = bp->m_size;
            // update the base pointer to have the size of the newly freed space
            bp->m_size = size;
            bp++;
        } while (size = t);
   }
}
/* ------------------------------------------------------ */