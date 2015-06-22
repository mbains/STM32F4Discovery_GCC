
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "usart.h"
// defined in linker script
extern caddr_t _end, _stackend;

caddr_t _sbrk(int nbytes) {
    static caddr_t heap_ptr = NULL;
    caddr_t base;
    if (heap_ptr == NULL) {
        heap_ptr = (caddr_t) & _end;
    }
    if ((caddr_t) & _stackend > heap_ptr + nbytes) {
        base = heap_ptr;
        heap_ptr += nbytes;
        return (base);
    } else {
        errno = ENOMEM;
        return ((caddr_t) - 1);
    }
}

int _close(int file) {
    errno = ENOTSUP;
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR; // character device
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _link(char *old, char *new) {
    errno = EMLINK;
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    errno = ENOTSUP;
    return -1;
}

int _open(const char *name, int flags, int mode) {
    errno = ENOTSUP;
    return -1;
}

int _read(int file, char *ptr, int len) {
    if (len) {
        len = usart_read_arr(ptr, len);
        return len;
    }
    return 0;
}

int _unlink(char *name) {
    errno = ENOENT;
    return -1;
}

int _write(int file, char *ptr, int len) {
    if (len) {
        len = usart_write_arr(ptr, len);
        return len;
    }
    return 0;
}