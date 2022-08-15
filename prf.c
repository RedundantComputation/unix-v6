

/*
 * Scaled down version of C Library printf.
  * Only %s %l %d ( ==%l ) %o are recognized.
  * Used to print diagnostic information
  * directly on console tty.
  * Since it is not interrupt driven,
  * all system activities are pretty much
  * suspended.
  * Printf should not be used for chit-chat.
  * (Presumably for efficiency reasons due to 
  * the fact that it is not interrupt driven). 
  * I also removed the additional unnecessary parameters
  * from the original source code.
  */
printf(fmt, x1)
char fmt[];
{
    register char* s,
    register *adx, c;

    // x1 is a stack location so cannot be evaluated at compile-time.
    adx = &x1;
    while(1) {
        // extract characters from format string into c
        while((c = *fmt++) != '%') {
            // is the format string terminated?
            if (c == '\0')
                return;
            putchar(c);
        }
        // extract the escape sequence
        c = *fmt++;
        // case where escape sequence is a number (o || d == l)
        /* Note: We really have to wonder about the order of processing
         * here in the if statement. The source code comments specify
         * the order l, d, and then o, but the acutal code specifies the
         * order d, l and then o. Perhaps this is due to the fact that %d
         * would be the most common escape sequence and since C
         * is a short-circuiting language, this is perhaps most efficient.
         */ 
        if (c == 'd' || c == 'l' | c == 'o')
            // if escape sequence was octal, pass correct parameter
            printn(*adx, c=='o' ? 8 : 10);
        if (c == 's') {
            // dereference the string adx is pointing to
            s = *adx;
            while(c = *s++)
                putchar(s);
        }
        adx++;
    }
}