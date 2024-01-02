OBJS := main.o vector.o operation.o
OBJDIR := build
OBJS := $(foreach obj,$(OBJS),$(OBJDIR)/$(obj))

CFLAGS := -Wall

ifdef OPTIMIZATION_LEVEL
CFLAGS += -O$(OPTIMIZATION_LEVEL)
endif

ifdef OPSTR
CFLAGS += -DOPSTR=$(OPSTR)
endif

ifdef DATA_T
CFLAGS += -DDATA_T=$(DATA_T)
endif

$(OBJDIR)/main:$(OBJS)
	@echo "$@"
	@$(CC) $(OBJS) -o $@

$(OBJS):$(OBJDIR)/%.o:%.c
	@echo "$@"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm $(OBJDIR)/*.o $(OBJDIR)/main

OUTDIR := output
ifndef OUTFILE
OUTFILE := $(shell date +%Y%m%d%H%M%S).txt
endif

run: $(OBJDIR)/main
	@./$(OBJDIR)/main $(OUTDIR)/$(OUTFILE)
