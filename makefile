# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Nome do executável final
TARGET = out.exe

# Diretório de origem
SRC_DIR = src

# Lista de arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto correspondentes
OBJS = $(SRCS:.c=.o)

# Regra padrão (default)
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar e executar o programa
run: all
	./$(TARGET)

# Limpeza dos arquivos compilados
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

# PHONY targets
.PHONY: all clean run
