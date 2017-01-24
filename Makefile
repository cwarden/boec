ASTYLE := $(shell command -v astyle 2> /dev/null)

all:
	g++ -o boec main.cpp

release: format all

install: boec
	install -m 0755 boec /usr/local/bin

format:
ifndef ASTYLE
	$(error "Could not run formatting. Install astyle first.");
else
	@astyle --style=linux --recursive "*cpp"
endif
