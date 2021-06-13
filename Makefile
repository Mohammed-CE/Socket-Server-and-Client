All: 
	gcc server.c -o ./Storage/server -lpthread
	gcc client.c -o client 

clean: 
	$(RM) ./Storage/server
	$(RM)  client