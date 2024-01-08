OBJS := main.o
OBJDIR := build
OBJS := $(foreach obj,$(OBJS),$(OBJDIR)/$(obj))

$(OBJDIR)/main: $(OBJS)
	@echo $@
	@$(CC) $< -o $@

$(OBJS):$(OBJDIR)/%.o: %.c
	@echo $@
	@$(CC) $(CFLAGS) -c $< -o $@

OUTDIR := output
ifndef OUTFILE
	OUTFILE := $(shell date +%Y%m%d%H%M%S).txt
endif

run: main
	@./$(OBJDIR)/main $(OUTDIR)/$(OUTFILE)

clean:
	@rm -rf $(OBJDIR)/*.o $(OBJDIR)/main
