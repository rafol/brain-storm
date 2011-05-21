#Criação de variáveis que, ao serem chamadas no modo $(CC), $(CCOPTS), $(NOME), executarão o comando definido aqui

CC = gcc

C++ = g++

CCOPTS = -w -g -O3

LIBS = -lfann

prog = brian

prog2 = storm

numEpoch = 500

#prog é o nome do programa, deve ser alterado conforme o caso. Aqui, o arquivo fonte é prog.c
#All chama todos os programas listados após os dois pontos
All: $(prog) $(prog2)

#Chamada para gerar o executável prog a partir do prog.o
$(prog):$(prog).cpp
	$(C++) $(CCOPTS) $(LIBS) -o $@ $^

$(prog2):$(prog2).cpp
	$(C++) $(CCOPTS) $(LIBS) -o $@ $^

R2000: $(prog)
	cp 2000/dataPixTrain.txt .
	./$(prog) $(numEpoch) 1 1 0.0002 1508 < 2000/dataPixValid.txt > 2000/log2000_2.txt

R1000: $(prog)
	cp 1000/dataPixTrain.txt .
	./$(prog) $(numEpoch) 1 1 0.0002 2508 < 1000/dataPixValid.txt > 1000/log1000_2.txt

R500: $(prog)
	cp 500/dataPixTrain.txt .
	./$(prog) $(numEpoch) 1 1 0.0002 3008 < 500/dataPixValid.txt > 500/log500_2.txt
