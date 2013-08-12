all: srv cli

srv: server.c
	gcc server.c -lpthread -o $@

cli: client.c
	gcc client.c -lpthread -o $@

clean:
	rm -rf cli srv
