#ifndef PROCESS_H_
# define PROCESS_H_

        INT runProcess();

        INT cleanDir(LPTSTR path);

        INT cleanRecursive(LPTSTR path, INT temp_flag, INT *ok_cnt, INT *ko_cnt);

        LPTSTR getExtension(LPTSTR file_name);

        INT isTemp(WIN32_FIND_DATA data);

#endif /* !PROCESS_H_ */
