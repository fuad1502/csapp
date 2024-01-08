OBJS := main.o
OBJDIR := build
OBJS := $(foreach obj,$(OBJS),$(OBJDIR)/$(obj))
CFLAGS := -O1

$(OBJDIR)/main: $(OBJS)
	@echo $@
	@$(CC) $< -o $@

$(OBJS):$(OBJDIR)/%.o: %.c
	@echo $@
	@$(CC) $(CFLAGS) -c $< -o $@

OUTDIR := output
ifndef OUTFILE
	OUTFILE := benchmark.txt
endif

run: $(OBJDIR)/main
	@./$(OBJDIR)/main $(OUTDIR)/$(OUTFILE)

clean:
	@rm -rf $(OBJDIR)/*.o $(OBJDIR)/main
