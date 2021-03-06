program_NAME := creditCard.out
program_C_SRCS := $(wildcard *.c)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_OBJS := $(program_C_OBJS)
program_INCLUDE_DIRS := .
program_LIBRARY_DIRS := .
program_LIBRARIES := .

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-L$(library))

.PHONY: all clean distclean $(SUBDIRS)

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	gcc -g $(program_OBJS) -o $(program_NAME)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)
	@- for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f makefile $@; \
		done
distclean: clean
