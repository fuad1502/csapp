OBJS := main.o transpose.o
CFLAGS := -Wall -O1
OBJDIR := build
OBJS := $(foreach obj,$(OBJS),$(OBJDIR)/$(obj))

$(OBJDIR)/main: $(OBJS)
	@echo "> Generating $@"
	@$(CC) $^ -o $@

$(OBJS):$(OBJDIR)/%.o:%.c
	@echo "> Compiling $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

ifndef OUTFILE
  OUTFILE := out.txt
endif

.PHONY: run
run: $(OBJDIR)/main
	@echo "> Running $<"
	@./$< $(OUTFILE)

.PHONY: plot
plot: run
	@echo "> Plotting"
	@python3 ./plot.py $(OUTFILE)

.PHONY: clean
clean:
	@echo "> Cleaning $(OBJDIR) directory"
	@rm -r $(OBJDIR)
