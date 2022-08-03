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
}