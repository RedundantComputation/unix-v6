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