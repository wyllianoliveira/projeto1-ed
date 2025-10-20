# Nome do executável
PROJ_NAME=ted

# Compilador
CC=gcc

# Flags exigidas pelo projeto
CFLAGS=-std=c99 -fstack-protector-all -Wall -Wextra

# Diretório dos fontes
SRC=src

# Lista de objetos
OBJETOS=$(SRC)/main.o \
         $(SRC)/forma.o \
         $(SRC)/fila.o \
         $(SRC)/pilha.o \
         $(SRC)/disparador.o \
         $(SRC)/qry.o \
         $(SRC)/svg.o \
         $(SRC)/txt.o \
		 $(SRC)/chao.o \
		 $(SRC)/lista.o \
		 $(SRC)/geo.o

# Regra principal: gera o executável
$(PROJ_NAME): $(OBJETOS)
	$(CC) $(CFLAGS) -o $(SRC)/$(PROJ_NAME) $(OBJETOS)

# Regra para compilar cada .c em .o
$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(SRC)/*.o $(SRC)/$(PROJ_NAME)