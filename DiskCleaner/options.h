char get_options(int ac, char **av, char *options, char (*message)[100]);
char catch_options(char *param, int ac, char **av, int *k, int *index, char *options, char (*message)[100]);
int has_option(char option, char *options);
int is_valid_option(char option);