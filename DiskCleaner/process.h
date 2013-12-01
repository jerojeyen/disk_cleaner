INT main_process();
INT clean_path(LPTSTR path);
INT read_directory(LPTSTR path, INT *num_done, INT *num_failed, INT wide_mode);
LPTSTR get_filename_ext(LPTSTR filename);
INT has_to_be_cleaned_up(WIN32_FIND_DATA filedata);