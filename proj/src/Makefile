# name of the program (Minix service)
PROG=proj

# Directories with the files to be compiled
.PATH: ${.CURDIR}/controller/
.PATH: ${.CURDIR}/controller/keyboard_mouse
.PATH: ${.CURDIR}/controller/timer
.PATH: ${.CURDIR}/controller/video
.PATH: ${.CURDIR}/controller/rtc
.PATH: ${.CURDIR}/controller/driver
.PATH: ${.CURDIR}/model/
.PATH: ${.CURDIR}/view/
.PATH: ${.CURDIR}/game/

# source code files to be compiled
SRCS = proj.c timer.c utils.c graphics.c KBC.c keyboard.c mouse.c rtc.c model.c view.c sprite.c game.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ -O2

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
