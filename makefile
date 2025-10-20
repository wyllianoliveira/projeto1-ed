PROJ_NAME=ted

ALUNO=WyllianOliveira

CC=gcc
CFLAGS=-std=c99 -fstack-protector-all -Wall -Wextra
SRC=src
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


$(PROJ_NAME): $(OBJETOS)
	$(CC) $(CFLAGS) -o $(SRC)/$(PROJ_NAME) $(OBJETOS)


$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(SRC)/*.o $(SRC)/$(PROJ_NAME)