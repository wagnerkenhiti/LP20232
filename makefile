all: mercadinhoTeste

# compilação do executavel
mercadinhoTeste:  produtos.o apresentacao.o tempo.o cliente.o vendas.o main.o
# Compilador faz a ligação entre os dois arquivos obj 
# 	e gera o executável
	gcc -o mercadoPrototipo main.o produtos.o apresentacao.o tempo.o cliente.o vendas.o -ggdb

cliente.o: cliente.c
	gcc -o cliente.o -c cliente.c -Wall -ggdb

tempo.o: tempo.c
#compila o arquivo atual
	gcc -o tempo.o -c tempo.c -Wall -ggdb

apresentacao.o: apresentacao.c
# compila o arquivo atual
	gcc -o apresentacao.o -c apresentacao.c -Wall -ggdb

produtos.o : produtos.c 
# compila o arquivo atual
	gcc -o produtos.o -c produtos.c -Wall -ggdb

vendas.o : vendas.c
	gcc -o vendas.o -c vendas.c -Wall -ggdb

main.o : main.c produtos.h
	gcc -o main.o -c main.c -Wall -ggdb

clean:
	rm -rf *.o

mrproper: clean
	rm -rf mercadoPrototipo
