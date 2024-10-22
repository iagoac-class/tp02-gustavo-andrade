
# Nome do projeto
PROJ_NAME=arvores

# Arquivos .c
C_SOURCE=$(wildcard *.c)

# Arquivos .h
H_SOURCE=$(wildcard *.h)

# Arquivos objeto
OBJ=$(C_SOURCE:.c=.o)

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c         \
         -Wall      \
		 -g         \
         -pedantic

#Comando utilizado com target para clean
RM=rm -rf         

#########################
# Compilação e linkagem #
#########################
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Construindo o binário usando o linker GCC: $@'
	$(CC) -o $@ $^
	@ echo 'Binário pronto!: $@'
	@ echo ' '
%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~