APP_NAME = geometry
LIB_NAME = libgeometry

CC = gcc
CFLAGS = -Wall -Werror -I src
DEPSFLAGS = -MMD

OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

APP_SOURCE = $(wildcard $(SRC_DIR)/$(APP_NAME)/*.c)
APP_OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(APP_SOURCE))

LIB_SOURCE = $(wildcard $(SRC_DIR)/$(LIB_NAME)/*.c)
LIB_OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(LIB_SOURCE))

DEPS = $(patsubst %.o, $(OBJ_DIR)%.d, $(APP_OBJ)) $(patsubst %.o, $(OBJ_DIR)%.d, $(LIB_OBJ))

.PHONY: all clean