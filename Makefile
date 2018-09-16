PROG =	sigreset
MAN =

WARNS =	6
# This is a workaround for the broken glibc
CPPFLAGS+=	-D_POSIX_C_SOURCE
COPTS+=		-std=iso9899:1999

.include <bsd.prog.mk>
