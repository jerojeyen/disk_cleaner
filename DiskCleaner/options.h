#ifndef OPTIONS_H_
# define OPTIONS_H_

char getOpts(int argc, char **argv, char *active_opts, char (*path)[260]);

char matchOpts(char *arg, int argc, char **argv, int *argv_index,
    int *active_opts_index, char *active_options, char (*path)[260]);

int isActiveOpt(char opt, char *opts);

int isValidOpt(char opt);

#endif /* !OPTIONS_H_  */
