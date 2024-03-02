NAME = endgame
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INC_DIR)/*.h)


CC = clang
AR = ar
AFLAGS = rcs
MKDIR = mkdir -p
RM = rm -rf


CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic) -g \

SDL = -F resources/frameworks -I resources/frameworks/SDL2.framework/SDL2 -I resources/frameworks/SDL2_image.framework/SDL2_image

SDL_FLAGS = -rpath resources/frameworks -framework SDL2 \
		-framework SDL2_image \
		-I resources/frameworks/SDL2_image.framework/Headers \
		-framework SDL2_mixer \
		-I resources/frameworks/SDL2_mixer.framework/Headers \
		-framework SDL2_ttf \
		-I resources/frameworks/SDL2_ttf.framework/Headers \


all: intro $(NAME)

intro:
	@printf "\033[36;1mThis is \033[0m \033[36;1mMacOS Make tool\033[0m\n"

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(SDL_FLAGS) $(SDL)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(SDL)
	@printf "\r\33[2K$(NAME)\033[33;1m\t compile \033[0m$(<:$(SRC_DIR)/%.c=%)\r"

$(OBJ_DIR):
	@$(MKDIR) $@


clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall $(NAME)

open:
	@printf "\r\33[2K$(NAME) \033[34;1m running\033[0m\n"
	@./$(NAME)
	@printf "\r\33[2K$(NAME) \033[35;1m closed\033[0m\n"

andopen: reinstall open


.PHONY: all uninstall clean reinstall andopen
