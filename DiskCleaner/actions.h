#ifndef ACTIONS_H_
# define ACTIONS_H_

	void setLogPath(char *opts, char (*params)[100], char (*messages)[100]);
	void setPath(char *opts, char (*params)[100], char (*messages)[100]);
	BOOL InstallMyService();
	BOOL DeleteMyService();

#endif /* !ACTIONS_H_ */
