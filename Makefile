all:
	@make -C ./libft
	@make -C ./nm
	@make -C ./otool

clean:
	@make clean -C ./libft
	@make clean -C ./nm
	@make clean -C ./otool

fclean:
	@make fclean -C ./libft
	@make fclean -C ./nm
	@make fclean -C ./otool

re:
	@make re -C ./libft
	@make re -C ./nm
	@make re -C ./otool
